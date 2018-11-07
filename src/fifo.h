#ifndef FIFO_H_
#define FIFO_H_
#include <stdlib.h>
#include "graph.h"

struct elt
{
    struct node_t *node;
    struct elt *next;
};

struct fifo
{
    size_t size;
    struct elt *head;
};

struct fifo *fifo_init(void);
void fifo_enqueue(struct fifo *f, struct node_t *node);
struct node_t *fifo_dequeue(struct fifo *f);
size_t fifo_empty(struct fifo *f);
//void bfs(struct node_t *node, struct graph_t *g);

#endif /* ! FIFO_H_ */
