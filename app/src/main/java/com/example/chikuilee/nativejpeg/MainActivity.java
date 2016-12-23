package com.example.chikuilee.nativejpeg;

import android.graphics.Bitmap;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.File;
import java.nio.ByteBuffer;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView tv = (TextView) findViewById(R.id.tv);
        tv.setText(getName());
        ByteBuffer buffer = getImage(new File(Environment.getExternalStorageDirectory(), "test.jpg").getAbsolutePath());
        int rgb[] = new int[256 * 256];
        byte[] bytes = new byte[rgb.length * 3];
        buffer.get(bytes, 0, buffer.limit());
        for (int i = 0; i < rgb.length; ++i) {
            int p = i * 3;
            rgb[i] = 0xff << 24;
            rgb[i] += bytes[p] << 16;
            rgb[i] += bytes[p + 1] << 8;
            rgb[i] += bytes[p + 2];
        }
        release(buffer);
        Bitmap bitmap = Bitmap.createBitmap(rgb, 256, 256, Bitmap.Config.RGB_565);
        ImageView imageView = (ImageView) findViewById(R.id.iv_image);
        imageView.setImageBitmap(bitmap);

    }

    public native String getName();

    public native ByteBuffer getImage(String fileName);

    public native void release(ByteBuffer byteBuffer);
}
