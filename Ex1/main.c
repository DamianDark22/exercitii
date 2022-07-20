#include"list.h"
extern pthread_mutex_t lock;

List* l = NULL;

void print_int(int el)
{
    printf("%d ", el);
}

void facy_print_int(int el)
{
    printf("%d/ ", el);
}

void* func_th1(void* arg)
{
    printf("add by Thread 1\n");
    add(&l, 2, print_int);

    printf("add by Thread 1\n");
    add(&l, 4, print_int);

    printf("add by Thread 1\n");
    add(&l, 10, print_int);

    printf("delete by Thread 1\n");
    delete(&l, 2);

    printf("sort by Thread 1\n");
    sort_list(&l);

    printf("delete by Thread 1\n");
    delete(&l, 10);

    printf("delete by Thread 1\n");
    delete(&l, 5);

    return NULL;
}

void* func_th2(void* arg)
{
    printf("add by Thread 2\n");
    add(&l, 11, print_int);

    printf("add by Thread 2\n");
    add(&l, 1, print_int);

    printf("delete by Thread 2\n");
    delete(&l, 11);

    printf("add by Thread 2\n");
    add(&l, 8, print_int);

    printf("print by Thread 2\n");
    print_list(l);

    return NULL;
}

void* func_th3(void* arg)
{
    printf("add by Thread 3\n");
    add(&l, 30, print_int);

    printf("add by Thread 3\n");
    add(&l, 25, print_int);

    printf("add by Thread 3\n");
    add(&l, 100, print_int);

    printf("sort by Thread 3\n");
    sort_list(&l);

    printf("print by Thread 3\n");
    print_list(l);

    printf("delete by Thread 3\n");
    delete(&l, 100);

    return NULL;
}


int main(int argc, char *argv[])
{
    int n = 3;
    pthread_t id[n];
    pthread_mutex_init(&lock, NULL);

    pthread_create(&id[0], NULL, func_th1, NULL);
    pthread_create(&id[1], NULL, func_th2, NULL);
    pthread_create(&id[2], NULL, func_th3, NULL);

    for(int i = 0; i < n; ++i)
    {
        pthread_join(id[i], NULL);
    }
    pthread_mutex_destroy(&lock);

    printf("Print final: ");
    print_list(l);
    flush_list(&l);

    return 0;
}