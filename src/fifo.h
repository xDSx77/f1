#ifndef FIFO_H
#define FIFO_H
#include "graph.h"

struct elt
{
    struct node *data;
    struct elt *next;
};

struct fifo
{
    size_t size:16;
    struct elt *head;
};

struct fifo *fifo_init(void);
void fifo_enqueue(struct fifo *f, struct node *g);
struct node *fifo_dequeue(struct fifo *f);
size_t fifo_empty(struct fifo *f);

#endif /* ! FIFO_H */
