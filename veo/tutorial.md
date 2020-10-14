### ve offloading 使用，
简单来说需要将执行在ve上的代码生成静态或者动态库，然后在代码中进行调用

`gcc -save-temps hello.c -o hello`  输出所有中间文件  

`gcc -E hello.c -o hello.i` 预编译过程，将头文件代码加入

`gcc -S hello.i -o hello.s` 生成汇编代码

`gcc -c hello.s -o hello.o` 汇编代码到机器码，生成object,不进行链接操作



### 静态库的制作
静态库会将用到的函数编译到可执行文件中去  

`ar -cr libtest.a test.o` 生成静态连接库

`gcc test.c -L<filepath> -ltest` 上一步生成的静态库的名字只能这样引用

### 动态库制作
动态库用到的时候才调用

`gcc -fPIC test.c -c`

`gcc -shared -o libtest.so test.o`

`export LD_LIBRARY_PATH=动态库路径`

### 如何查看一个程序是否使用动态库

`file file_name` 看文件类型

`ldd exe_file` 如果没有链接，not a dynamic executable

### static
统一目录，默认链接动态库，可以使用-static选择静态库


## VE Offloding

1.  `ncc -c -o libvehello.o libvehello.c` 生成object 文件
2. `mk_veorun_static -o vehello libvehello.o` 静态库
3. veo_header=`/opt/nec/ve/veos/include`
4. libveo, shared library ldd=` /opt/nec/ve/veos/lib64`
5. `gcc -o hello.ext hello.c -I$veo_header$ -L$ldd$ -Wl,-rpath=/opt/nec/ve/veos/lib64 -lveo`

gcc -o hello.exe hello.c -I/opt/nec/ve/veos/include -L/opt/nec/ve/veos/lib64 -Wl,-rpath=/opt/nec/ve/veos/lib64 -lveo

gcc -o dynamic_hello.exe dynamic_hello.c -I/opt/nec/ve/veos/include -L/opt/nec/ve/veos/lib64 -Wl,-rpath=/opt/nec/ve/veos/lib64 -lveo

-wl，-rpath 指定链接库位置

