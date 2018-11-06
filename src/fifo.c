#include <stdio.h> //TODO remove
#include <math.h>
#include "fifo.h"

static struct coord2_t neighbors[8] =
{
    {-1, -1},
    {0, -1},
    {1, -1},
    {-1, 0},
    {1, 0},
    {-1, 1},
    {0, 1},
    {1, 1}
};

struct fifo *fifo_init(void)
{
    struct fifo *f = malloc(sizeof(struct fifo));
    if (f == NULL)
        return NULL;
    f->head = NULL;
    f->size = 0;
    return f;
}

void fifo_enqueue(struct fifo *f, struct node_t *node)
{
    if (f == NULL)
        return;
    if (f->head != NULL)
    {
        f->size += 1;
        struct elt *cur = f->head;
        while (cur->next != NULL)
            cur = cur->next;
        cur->node = node;
    }
    else
    {
        f->head = malloc(sizeof(struct elt));
        f->head->node = node;
        f->head->next = NULL;
        f->size++;
    }
}

struct node_t *fifo_dequeue(struct fifo *f)
{
    if (f == NULL)
        return NULL;
    if (f->head != NULL)
    {
        struct node_t *node = f->head->node;
        f->head = f->head->next;
        f->size--;
        return node;
    }
    return NULL;
}

size_t fifo_empty(struct fifo *f)
{
    if (f == NULL || f->head == NULL)
        return 0;
    return f->size;
}

void bfs(struct node_t *node, struct graph_t *g)
{
    struct fifo *f = fifo_init();
    fifo_enqueue(f, node);
    node->state = DONE;
    int x_node;
    int y_node;
    int x_nb;
    int y_nb;
    struct node_t *nb;
    while(!fifo_empty(f))
    {
        node = fifo_dequeue(f);
        if (node->state == DONE)
            continue;
        node->state = DONE;
        x_node = node->coord.x;
        y_node = node->coord.y;
        printf("node x: %d\nnode y: %d\n", x_node, y_node);
        for (int i = 0; i < 7; i++)
        {
            if (node->weights[i] == INFINITY)
                continue;
            else
            {
                x_nb = x_node + neighbors[i].x;
                y_nb = y_node + neighbors[i].y;
                nb = g->nodes + (y_nb * g->width + x_nb);
                fifo_enqueue(f, nb);
                nb->state = DONE;
            }
        }
    }
}
