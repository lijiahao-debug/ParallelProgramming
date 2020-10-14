# include config files
OBJ_DIR=/home/gp.sc.cc.tohoku.ac.jp/lijiahao/workspace/ParallelProgramming/build/obj/veos/
LDFLAGS=-L/opt/nec/ve/veos/lib64 -Wl,-rpath=/opt/nec/ve/veos/lib64 -lveo
VE_I_DIR=/opt/nec/ve/veos/include
VE_LIB_DIR=/home/gp.sc.cc.tohoku.ac.jp/lijiahao/workspace/ParallelProgramming/build/lib/veos/
CFLAGS=-c -I $(VE_I_DIR)
CC=gcc
VE_BIN_DIR=bin/
VPATH=src
OBJS=$(OBJ_DIR)main_hello.o
EXECUTABLE=$(VE_BIN_DIR)hello.exe
STATIC_SOURCE=$(OBJ_DIR)lib_hello.o
STATIC_LIB=$(VE_LIB_DIR)libvehello.a
DYNAMIC_LIB=$(VE_LIB_DIR)libvehello.so
NCC=ncc
$(EXECUTABLE):$(OBJS) $(STATIC_SOURCE) $(STATIC_LIB) $(DYNAMIC_LIB)
	$(CC) -o $(EXECUTABLE) $(OBJS) $(LDFLAGS)
$(OBJS):main_hello.c
	$(CC) $(CFLAGS) -o $(OBJS) $^
$(STATIC_LIB):$(STATIC_SOURCE)
	mk_veorun_static -o $(STATIC_LIB) $^
$(STATIC_SOURCE):lib_hello.c
	$(NCC) -c -o $(STATIC_SOURCE) $^
$(DYNAMIC_LIB):lib_hello.c
	$(NCC) -fpic -shared -o $(DYNAMIC_LIB) $^
.PHONY:clean
clean:
	$(RM) $(OBJ_DIR)*.o $(EXECUTABLE)