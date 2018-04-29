export ANDROID_NDK="/home/lihm/Android/android-ndk-r12b"
export PATH="$ANDROID_NDK/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/:$ANDROID_NDK:$ANDROID_NDK/tools:/usr/local/bin:/usr/bin:/bin:$PATH"

arm-linux-androideabi-ar -x ./lib.android/armv7/libstarlib.a
arm-linux-androideabi-g++ --sysroot=$ANDROID_NDK/platforms/android-21/arch-arm -c stargo_ftbl.cpp -I./include -fPIC -DENV_ANDROID -DENV_M32
arm-linux-androideabi-gcc --sysroot=$ANDROID_NDK/platforms/android-21/arch-arm -c vsopenapi_c_stub.c -I./include -fPIC -DENV_ANDROID -DENV_M32
arm-linux-androideabi-ar rcs ../stargo/android.static/armv7/libvsopenapi_c_stub.a stargo_ftbl.o vsopenapi_c_stub.o vs_shell.o vs_uuid.o srplib_main.o md5proc.o md5proc_c.o

