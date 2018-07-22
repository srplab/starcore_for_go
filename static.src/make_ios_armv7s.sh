export PATH="/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/:/usr/local/bin:/usr/bin:/bin:$PATH"  
export CFLAGS="-DIOS -arch armv7s -miphoneos-version-min=6.0 -isysroot "$(xcrun -sdk iphoneos --show-sdk-path) 

clang++ $CFLAGS -c stargo_ftbl.cpp -I./include -fPIC -DENV_IOS -DENV_M32
clang $CFLAGS -c vsopenapi_c_stub.c -I./include -fPIC -DENV_IOS -DENV_M32
ar rcs ./libvsopenapi_c_stub.a stargo_ftbl.o vsopenapi_c_stub.o
rm *.o

