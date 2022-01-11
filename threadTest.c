#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct thread_args
{
    int a;
    double b;
};


struct thread_result
{
    long x;
    double y;
};

void *thread_func(void *args_void)
{
    struct thread_args *args = args_void;
    /* The thread cannot return a pointer to a local variable */
    struct thread_result *res = malloc(sizeof *res);
	args->a = 10;
	args->b = 20;
    res->x  = 10 + args->a;
    res->y = args->a * args->b;
    return args;
}

int main(int argc, char *argv[])
{
    pthread_t threadL;
    struct thread_args in = { .a = 10, .b = 3.141592653 };
    void *out_void;
    struct thread_args *out;

    pthread_create(&threadL, NULL, thread_func, &in);
    pthread_join(threadL, &out_void);
    out = out_void;
    printf("out -> x = %i\tout -> b = %f\n", out->a, out->b);
    free(out);

    return 0;
}
