#include "fifo.h"

struct fifo *fifo_init(void)
{
    struct fifo *f = malloc(sizeof(struct fifo));
    if (f == NULL)
        return NULL;
    f->head = NULL;
    f->size = 0;
    return f;
}

void fifo_enqueue(struct fifo *f, struct node *g)
{
    if (f == NULL)
        return;
    if (f->head != NULL)
    {
        struct elt *cur = f->head;
        while (cur->next != NULL)
            cur = cur->next;
        cur->data = g;
    }
    else
    {
        f->head = malloc(sizeof(struct elt));
        f->head->data = g;
        f->head->next = NULL;
    }
}

struct node *fifo_dequeue(struct fifo *f)
{
    if (f == NULL)
        return NULL;
    if (f->head != NULL)
    {
        struct node *g = f->head->data;
        f->head = f->head->next;
        return g;
    }
    return NULL;
}

size_t fifo_empty(struct fifo *f)
{
    if (f == NULL)
        return 0;
    return f->size;
}
