//
// Created by chikuilee on 2016/12/23.
//
#include <jni.h>
#include "cstdio"
#include "cstdlib"
#include "csetjmp"
#include "android/log.h"
#include "./jpeg/jpeglib.h"

#define LOG_I(...) ((void)__android_log_print(ANDROID_LOG_INFO,"native-lib",__VA_ARGS__))

struct my_error_mgr {
    struct jpeg_error_mgr pub;
    /* "public" fields */

    jmp_buf setjmp_buffer;    /* for return to caller */
};
typedef struct my_error_mgr *my_error_ptr;

void my_error_exit(j_common_ptr cinfo) {
    my_error_ptr myerr = (my_error_ptr) cinfo->err;

    (*cinfo->err->output_message)(cinfo);

    longjmp(myerr->setjmp_buffer, 1);
}

// 读取JPG图片数据，并解压到内存中，*rgb_buffer需要自行释放
int read_jpeg_file(const char *jpeg_file, unsigned char **rgb_buffer, int *size, int *width,
                   int *height) {
    struct jpeg_decompress_struct cinfo;
    struct my_error_mgr jerr;
    FILE *fp;

    JSAMPARRAY buffer;
    int row_stride = 0;
    unsigned char *tmp_buffer = NULL;
    int rgb_size;

    fp = fopen(jpeg_file, "rb");
    if (fp == NULL) {
        LOG_I("open file %s failed.\n", jpeg_file);
        return -1;
    } else {
        LOG_I("open file succeed");
    }

    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;

    if (setjmp(jerr.setjmp_buffer)) {
        jpeg_destroy_decompress(&cinfo);
        fclose(fp);
        return -1;
    }

    jpeg_create_decompress(&cinfo);

    jpeg_stdio_src(&cinfo, fp);

    jpeg_read_header(&cinfo, TRUE);

    cinfo.out_color_space = JCS_RGB; //JCS_YCbCr;  // 设置输出格式

    jpeg_start_decompress(&cinfo);

    row_stride = cinfo.output_width * cinfo.output_components;
    *width = cinfo.output_width;
    *height = cinfo.output_height;

    rgb_size = row_stride * cinfo.output_height; // 总大小
    LOG_I("rgb size %d", rgb_size);
    *size = rgb_size;

    buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

    *rgb_buffer = (unsigned char *) malloc(sizeof(char) * rgb_size);    // 分配总内存

    LOG_I("debug--:\nrgb_size: %d, size: %d w: %d h: %d row_stride: %d \n", rgb_size,
          cinfo.image_width * cinfo.image_height * 3,
          cinfo.image_width,
          cinfo.image_height,
          row_stride);
    tmp_buffer = *rgb_buffer;
    while (cinfo.output_scanline < cinfo.output_height) // 解压每一行
    {
        jpeg_read_scanlines(&cinfo, buffer, 1);
        // 复制到内存
        memcpy(tmp_buffer, buffer[0], row_stride);
        tmp_buffer += row_stride;
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    fclose(fp);

    return 0;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_chikuilee_nativejpeg_MainActivity_release(JNIEnv *env, jobject instance,
                                                           jobject byteBuffer) {

    // TODO
    free(env->GetDirectBufferAddress(byteBuffer));
    LOG_I("回收内存成功");
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_chikuilee_nativejpeg_MainActivity_getImage(JNIEnv *env, jobject instance,
                                                            jstring fileName_) {
    const char *fileName = env->GetStringUTFChars(fileName_, 0);
    LOG_I("文件路径 %s", fileName);
    // TODO
    unsigned char *data;
    int size = 0;
    int width = 0;
    int height = 0;
    int result = read_jpeg_file(fileName, &data, &size, &width, &height);
    LOG_I("result %d size %d width %d height %d ", result, size, width, height);
    return env->NewDirectByteBuffer(data, size);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_chikuilee_nativejpeg_MainActivity_getName(JNIEnv *env, jobject instance) {

    // TODO
    LOG_I("getName");
    return env->NewStringUTF("Hello Native");
}


