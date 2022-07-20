#include<stdlib.h>
#include<stdio.h>
#include <pthread.h>

typedef void (*print_func)(int);

typedef struct list
{
    print_func callback;
    int val;
    struct list* next;
}List;

int add(List**, int, print_func);
void print_list(List*);
int delete(List**, int);
void flush_list(List**);
void sort_list(List**);
int ord_intr(List**, int, print_func);