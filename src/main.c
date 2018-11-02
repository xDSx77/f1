#include <stdio.h>
#include "graph.h"
#include "fifo.h"

int main(void)
{
    struct fifo *f = fifo_init();
    if (f == NULL)
        return -1;
    struct elt *elt = malloc(sizeof(struct elt));
    if (elt == NULL)
    {
        free(f);
        return -1;
    }
    elt->data = NULL;
    elt->next = NULL;
    f->head = elt;
    printf("%ld\n", fifo_empty(f));
    struct node *g = malloc(sizeof(struct node));
    if (g == NULL)
    {
        free(f);
        free(elt);
        return -1;
    }
    g->distance = 0;
    g->name = "g";
    g->marked = 1;
    g->len_neighbors = 1;
    g->daddy = NULL;
    struct edge *e1 = malloc(sizeof(struct edge));
    if (e1 == NULL)
    {
        free(f);
        free(elt);
        free(g);
        return -1;
    }
    struct node *h = malloc(sizeof(struct node));
    if (h == NULL)
    {
        free(f);
        free(elt);
        free(g);
        free(e1);
        return -1;
    }
    h->distance = 0;
    h->name = "h";
    h->marked = 1;
    h->len_neighbors = 0;
    h->daddy = g;
    e1->weight = 7;
    e1->next = h;
    g->neighbors[0] = e1;
    f->size = 2;
    f->head->data = g;
    struct elt *elt2 = malloc(sizeof(struct elt));
    if (elt2 == NULL)
    {
        free(f);
        free(elt);
        free(g);
        free(e1);
        free(h);
        return -1;
    }
    elt2->data = NULL;
    elt2->next = NULL;
    f->head->next = elt2;
    f->head->next->data = h;
    free(f);
    free(elt);
    free(g);
    free(e1);
    free(h);
    return 0;
}
