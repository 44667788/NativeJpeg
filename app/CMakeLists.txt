# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds it for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             src/main/cpp/native-lib.cpp )

#jpeg lib

add_library(
           jpeg
           SHARED
           src/main/cpp/jpeg/jaricom.c src/main/cpp/jpeg/jcapimin.c src/main/cpp/jpeg/jcapistd.c src/main/cpp/jpeg/jcarith.c src/main/cpp/jpeg/jccoefct.c src/main/cpp/jpeg/jccolor.c
                         src/main/cpp/jpeg/jcdctmgr.c src/main/cpp/jpeg/jchuff.c src/main/cpp/jpeg/jcinit.c src/main/cpp/jpeg/jcmainct.c src/main/cpp/jpeg/jcmarker.c src/main/cpp/jpeg/jcmaster.c
                         src/main/cpp/jpeg/jcomapi.c src/main/cpp/jpeg/jcparam.c src/main/cpp/jpeg/jcprepct.c src/main/cpp/jpeg/jcsample.c src/main/cpp/jpeg/jctrans.c src/main/cpp/jpeg/jdapimin.c
                         src/main/cpp/jpeg/jdapistd.c src/main/cpp/jpeg/jdarith.c src/main/cpp/jpeg/jdatadst.c src/main/cpp/jpeg/jdatasrc.c src/main/cpp/jpeg/jdcoefct.c src/main/cpp/jpeg/jdcolor.c
                         src/main/cpp/jpeg/jddctmgr.c src/main/cpp/jpeg/jdhuff.c src/main/cpp/jpeg/jdinput.c src/main/cpp/jpeg/jdmainct.c src/main/cpp/jpeg/jdmarker.c src/main/cpp/jpeg/jdmaster.c
                         src/main/cpp/jpeg/jdmerge.c src/main/cpp/jpeg/jdpostct.c src/main/cpp/jpeg/jdsample.c src/main/cpp/jpeg/jdtrans.c src/main/cpp/jpeg/jerror.c src/main/cpp/jpeg/jfdctflt.c
                         src/main/cpp/jpeg/jfdctfst.c src/main/cpp/jpeg/jfdctint.c src/main/cpp/jpeg/jidctflt.c src/main/cpp/jpeg/jidctfst.c src/main/cpp/jpeg/jidctint.c src/main/cpp/jpeg/jquant1.c
                         src/main/cpp/jpeg/jquant2.c src/main/cpp/jpeg/jutils.c src/main/cpp/jpeg/jmemmgr.c src/main/cpp/jpeg/jmemnobs.c)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because system libraries are included in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} jpeg)