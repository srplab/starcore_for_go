ar -x ./lib.windows/libstarlib.a
gcc -c stargo_ftbl.cpp -I./include -fPIC
gcc -c vsopenapi_c_stub.c -I./include -fPIC
ar rcs ../stargo/windows.static/libvsopenapi_c_stub.a stargo_ftbl.o vsopenapi_c_stub.o vs_shell.o vs_uuid.o srplib_main.o md5proc.o md5proc_c.o
del *.o

