NDK=/Users/chikuilee/Library/Android/sdk/ndk-bundle
PLATFORM=$NDK/platforms/android-24/arch-arm64
PERBUILT=$NDK/toolchains/aarch64-linux-android-4.9/prebuilt
CC=$PERBUILT/darwin-x86_64/bin/aarch64-linux-android-gcc
./configure  --prefix=/Users/chikuilee/Downloads/jpeg-6b  --host=arm CC="$CC --sysroot=$PLATFORM"