#include <stdio.h>
#include <stdlib.h>
#include <ve_offload.h>
int main() {

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

    /* 使用动态链接库 */
    char *dynamic_lib = "/home/gp.sc.cc.tohoku.ac.jp/lijiahao/workspace/ParallelProgramming/build/lib/veos/libvehello.so";
    struct veo_proc_handle *proc2 = veo_proc_create(0);
    uint64_t handle2 = veo_load_library(proc2, dynamic_lib);
    struct veo_thr_ctxt *ctx2 = veo_context_open(proc2);
    struct veo_args *argp2 = veo_args_alloc();

    id = veo_call_async_by_name(ctx2, handle2, "hello", argp2);
    veo_call_wait_result(ctx2, id, &retval);
    printf("dynamic hello() id = %d retval = %d\n", id, retval);

    // 使用stack传递引用类型参数
    char c[] = "stack arguments";
    veo_args_set_stack(argp2, VEO_INTENT_IN, 0, c, sizeof(c));
    char *ret = (char *)malloc(sizeof(char) * 100);
    veo_args_set_stack(argp2, VEO_INTENT_OUT, 1, ret, 100); //接收返回值
    id = veo_call_async_by_name(ctx2, handle2, "dynamic_hello", argp2);
    veo_call_wait_result(ctx2, id, &retval);
    printf("dynamic reference arguments hello() id = %d retval = %d ret=%s\n", id, retval, ret);

    free(ret);
    /* 结束后需要释放一系列资源 */
    veo_args_free(argp2);
    veo_context_close(ctx2);
    veo_proc_destroy(proc2);
    return 0;
}