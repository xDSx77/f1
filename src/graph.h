#ifndef GRAPH_H
#define GRAPH_H
#include <stdlib.h>

/*struct info
{
    int marked:1;
};*/

struct edge
{
    size_t weight:16;
    struct node *next;
};

struct node
{
    size_t distance:16;
    char *name;
    //struct info data;
    int marked:1;
    size_t len_neighbors:4;
    struct edge *neighbors[0];
    struct node *daddy;
};

#endif /* ! GRAPH_H */
