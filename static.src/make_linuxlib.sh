ar -x ./lib.linux/libstarlib.a
gcc -c stargo_ftbl.cpp -I./include -fPIC -DENV_LINUX -DENV_M64
gcc -c vsopenapi_c_stub.c -I./include -fPIC -DENV_LINUX -DENV_M64
ar rcs ../stargo/linux.static/libvsopenapi_c_stub.a stargo_ftbl.o vsopenapi_c_stub.o vs_shell.o vs_uuid.o srplib_main.o md5proc.o md5proc_c.o
rm *.o

