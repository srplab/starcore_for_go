export ANDROID_NDK="/home/lihm/Android/android-ndk-r12b"
export PATH="$ANDROID_NDK/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/:$ANDROID_NDK:$ANDROID_NDK/tools:/usr/local/bin:/usr/bin:/bin:$PATH"

aarch64-linux-android-ar -x ./lib.android/arm64/libstarlib.a
aarch64-linux-android-g++ --sysroot=$ANDROID_NDK/platforms/android-21/arch-arm64 -c stargo_ftbl.cpp -I./include -fPIC -DENV_ANDROID -DENV_M64
aarch64-linux-android-gcc --sysroot=$ANDROID_NDK/platforms/android-21/arch-arm64 -c vsopenapi_c_stub.c -I./include -fPIC -DENV_ANDROID -DENV_M64
aarch64-linux-android-ar rcs ../stargo/android.static/arm64/libvsopenapi_c_stub.a stargo_ftbl.o vsopenapi_c_stub.o vs_shell.o vs_uuid.o srplib_main.o md5proc.o md5proc_c.o
rm *.o

