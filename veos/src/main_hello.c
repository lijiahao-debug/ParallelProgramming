#include <stdio.h>
#include <stdlib.h>
#include <ve_offload.h>

void static_offload();
void dynamic_offload();
void openmp_offload();

int main() {
    static_offload();
    dynamic_offload();
    openmp_offload();
    return 0;
}

void static_offload() {
    /* 使用静态链接库调用运行在VE上的代码 必须要定义的一系列参数*/
    char *static_lib = "/home/gp.sc.cc.tohoku.ac.jp/lijiahao/workspace/ParallelProgramming/build/lib/veos/libvehello.a";
    struct veo_proc_handle *proc = veo_proc_create_static(0, static_lib); //指定VE和可执行文件
    uint64_t handle = NULL;
    struct veo_thr_ctxt *ctx = veo_context_open(proc);
    struct veo_args *argp = veo_args_alloc();

    //调用无参方法
    uint64_t id = veo_call_async_by_name(ctx, handle, "hello", argp);
    uint64_t retval;
    veo_call_wait_result(ctx, id, &retval); //接收结果
    printf("static hello() id = %d retval = %d\n", id, retval);

    //传递基本类型参数
    veo_args_set_i64(argp, 0, 10); // 参数从0开始
    veo_args_set_i64(argp, 1, 20);
    id = veo_call_async_by_name(ctx, handle, "static_hello", argp);
    veo_call_wait_result(ctx, id, &retval);
    veo_args_clear(argp); //清空参数
    printf("static basic arguments hello() id = %d retval = %d\n", id, retval);

    /* 结束后需要释放一系列资源 */
    veo_args_free(argp);
    veo_context_close(ctx);
    veo_proc_destroy(proc);
}
void dynamic_offload() {

    /* 使用动态链接库 */
    char *dynamic_lib = "/home/gp.sc.cc.tohoku.ac.jp/lijiahao/workspace/ParallelProgramming/build/lib/veos/libvehello.so";
    struct veo_proc_handle *proc = veo_proc_create(0);
    uint64_t handle = veo_load_library(proc, dynamic_lib);
    struct veo_thr_ctxt *ctx = veo_context_open(proc);
    struct veo_args *argp = veo_args_alloc();

    uint64_t id = veo_call_async_by_name(ctx, handle, "hello", argp);
    uint64_t retval;
    veo_call_wait_result(ctx, id, &retval);
    printf("dynamic hello() id = %d retval = %d\n", id, retval);

    // 使用stack传递引用类型参数
    char c[] = "stack arguments";
    veo_args_set_stack(argp, VEO_INTENT_IN, 0, c, sizeof(c));
    char *ret = (char *)malloc(sizeof(char) * 100);
    veo_args_set_stack(argp, VEO_INTENT_OUT, 1, ret, 100); //接收返回值
    id = veo_call_async_by_name(ctx, handle, "dynamic_hello", argp);
    veo_call_wait_result(ctx, id, &retval);
    printf("dynamic reference arguments hello() id = %d retval = %d ret=%s\n", id, retval, ret);

    free(ret);
    /* 结束后需要释放一系列资源 */
    veo_args_free(argp);
    veo_context_close(ctx);
    veo_proc_destroy(proc);
}
void openmp_offload() {
    /* 使用静态链接库调用运行在VE上的代码 必须要定义的一系列参数*/
    char *static_lib = "/home/gp.sc.cc.tohoku.ac.jp/lijiahao/workspace/ParallelProgramming/build/lib/veos/libopenmp.a";
    struct veo_proc_handle *proc = veo_proc_create_static(0, static_lib); //指定VE和可执行文件
    uint64_t handle = NULL;
    struct veo_thr_ctxt *ctx = veo_context_open(proc);
    struct veo_args *argp = veo_args_alloc();

    //调用无参方法
    uint64_t id = veo_call_async_by_name(ctx, handle, "omp_hello", argp);
    uint64_t retval;
    veo_call_wait_result(ctx, id, &retval); //接收结果
    printf("openmp static hello() id = %d retval = %d\n", id, retval);

    /* 结束后需要释放一系列资源 */
    veo_args_free(argp);
    veo_context_close(ctx);
    veo_proc_destroy(proc);
}