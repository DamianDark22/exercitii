#include"list.h"
pthread_mutex_t lock;

List* allocate_cell(int el, print_func f)
{
    List* aux = (List*)calloc(1, sizeof(List));
    if(aux == NULL)
    {
        printf("Problema alocare!\n");
        return NULL;
    }

    aux->callback = f;
    aux->val = el;

    return aux;
}

int add(List** l, int el, print_func f)
{
    pthread_mutex_lock(&lock);

    if(*l == NULL)
    {
        *l = allocate_cell(el, f);
        if(*l == NULL)
        {
            printf("Problema adaugare element !\n");
            pthread_mutex_unlock(&lock);
            return 0;
        }
        pthread_mutex_unlock(&lock);
        return 1;
    }

    List* p = *l;
    for(;p->next != NULL; p = p->next);

    p->next = allocate_cell(el, f);
    if(p->next == NULL)
    {
        printf("Problema adaugare element !\n");
        pthread_mutex_unlock(&lock);
        return 0;
    }

    pthread_mutex_unlock(&lock);
    return 1;
}

void print_list(List* l)
{
    pthread_mutex_lock(&lock);
    printf("[ ");
    for(;l != NULL; l = l->next)
    {
        l->callback(l->val);
    }
    pthread_mutex_unlock(&lock);
    printf("]\n");
}

int delete(List** l, int el)
{
    pthread_mutex_lock(&lock);
    if(*l == NULL)
    {
        printf("Lista primita este vida !\n");
        pthread_mutex_unlock(&lock);
        return 0;
    }

    List* p = *l;
    List* ant = NULL;

    for(; p != NULL;)
    {
        if(p->val == el)
        {
            List* aux = p;
            if(ant == NULL)
                *l = (*l)->next;
            else
                ant->next = p->next;

            ant = p;
            p = p->next;
            free(aux);

            pthread_mutex_unlock(&lock);
            return 1;
        }
        else
        {
            ant = p;
            p = p->next;
        }
    }

    printf("Elementul %d nu a fost gasit !\n", el);
    pthread_mutex_unlock(&lock);
    return 0;
}

void flush_list(List** l)
{
    List* p;
    for(;*l != NULL;)
    {
       p = *l;
       *l = (*l)->next;
       free(p); 
    }
}

int ord_intr(List**l, int el, print_func f)
{
    if(*l == NULL)
    {
        *l = allocate_cell(el, f);
        if(*l == NULL)
        {
            printf("Problema adaugare ordonata element !\n");
            return 0;
        }
        return 1;
    }

    List* p = *l;
    List* ant = NULL;
    List* aux = allocate_cell(el, f);
    if(aux == NULL)
    {
        printf("Problema alocare intr_ord !\n");
        return 0;
    }

    for(;p != NULL; ant = p, p = p->next)
    {
        if(p->val > el)
        {
            if(ant == NULL)
            {
                aux->next = *l;
                *l = aux;
            }
            else
            {
                aux->next = p;
                ant->next = aux;
            }
            return 1;
        }
    }

    ant->next = aux;
    return 1;
}

void sort_list(List** l)
{
    pthread_mutex_lock(&lock);
    List* aux = NULL;

    List* p = *l;
    for(; p != NULL; p = p->next)
    {
        ord_intr(&aux, p->val, p->callback);
    }

    flush_list(l);

    *l = aux;
    pthread_mutex_unlock(&lock);
}