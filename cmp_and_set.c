#include <stdio.h>
#include <pthread.h>

int d = 0;

int cmp_and_set(int *v, int *old, int new)
{
    char res;

    __asm__ volatile (
    "lock;"
    "cmpxchgl %3, %4;" 
    "movl %%eax, %1;"
    "sete %0;"
    :"=a" (res), "=m"(*old)
    : "a"(*old), "r"(new), "m"(*v)
    :"cc", "memory"
    );

    return res;
}

void incr(int *v)
{
    int old = *v;
    while(!cmp_and_set(v, &old, old + 1));
}

void run()
{
    for(int i = 0; i < 6000000; i++) {
        incr(&d);
    }
}

int main()
{
    pthread_t p;
    pthread_t p1;
    pthread_create(&p, 0, (void * (*)(void *))run, 0);
    pthread_create(&p1, 0, (void * (*)(void *))run, 0);
    pthread_join(p, 0);
    pthread_join(p1, 0);
    run();
    printf("%d\n", d);
    return 0;
}
