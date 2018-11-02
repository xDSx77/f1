#ifndef GRAPH_H
#define GRAPH_H
#include <stdlib.h>
#include <limits.h>

/*struct info
{
    int marked:1;
};*/

struct edge
{
    size_t weight;
    struct node *next;
};

struct node
{
    size_t distance;
    char *name;
    //struct info data;
    unsigned int marked;
    size_t len_neighbors;
    struct edge *neighbors[100];
    struct node *daddy;
};

#endif /* ! GRAPH_H */
