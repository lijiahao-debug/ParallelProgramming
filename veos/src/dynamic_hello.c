#include <ve_offload.h>

int main(){
    struct veo_proc_handle *proc = veo_proc_create(0); //specify the ve node number to create a ve process
    uint64_t handle = veo_load_library(proc, "./lib/libvehello.so"); //load ve shared library
    struct veo_thr_ctxt *ctx = veo_context_open(proc); //create a ve context

    struct veo_args *argp  = veo_args_alloc(); // can set arguments
    uint64_t id = veo_call_async_by_name(ctx, handle, "hello", argp);
    uint64_t retval;
    veo_call_wait_result(ctx, id, &retval);

    // pass arguments by using a stack
    char c[] = "stack arguments";
    veo_args_set_stack(argp, VEO_INTENT_IN, 0, c, sizeof(c));
    long ret;
    veo_args_set_stack(argp, VEO_INTENT_OUT, 1, &ret, sizeof(ret));
    id = veo_call_async_by_name(ctx, handle, "dynamic_hello", argp);
    veo_call_wait_result(ctx, id, &retval);

    veo_args_free(argp);
    veo_context_close(ctx);
    veo_proc_destroy(proc);
    return 0;
}