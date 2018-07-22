rm -rf libvsopenapi_c_stub.a

rm -rf ios.x86
./make_ios_x86.sh
mkdir ios.x86
cp libvsopenapi_c_stub.a ios.x86
rm -rf libvsopenapi_c_stub.a

rm -rf ios.x86_64
./make_ios_x86_64.sh
mkdir ios.x86_64
cp libvsopenapi_c_stub.a ios.x86_64
rm -rf libvsopenapi_c_stub.a

rm -rf ios.armv7
./make_ios_armv7.sh
mkdir ios.armv7
cp libvsopenapi_c_stub.a ios.armv7
rm -rf libvsopenapi_c_stub.a

rm -rf ios.armv7s
./make_ios_armv7s.sh
mkdir ios.armv7s
cp libvsopenapi_c_stub.a ios.armv7s
rm -rf libvsopenapi_c_stub.a

rm -rf ios.arm64
./make_ios_arm64.sh
mkdir ios.arm64
cp libvsopenapi_c_stub.a ios.arm64
rm -rf libvsopenapi_c_stub.a

lipo -create ios.x86/libvsopenapi_c_stub.a ios.x86_64/libvsopenapi_c_stub.a ios.armv7/libvsopenapi_c_stub.a ios.armv7s/libvsopenapi_c_stub.a ios.arm64/libvsopenapi_c_stub.a -o libvsopenapi_c_stub.a

rm -rf ios.x86
rm -rf ios.x86_64
rm -rf ios.armv7
rm -rf ios.armv7s
rm -rf ios.arm64

cp libvsopenapi_c_stub.a ../stargo/ios.static
lipo -info ../stargo/ios.static/libvsopenapi_c_stub.a
rm -rf libvsopenapi_c_stub.a


 