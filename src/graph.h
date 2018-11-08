#ifndef GRAPH_H_
#define GRAPH_H_
#include "control.h"

enum marked
{
    UNSEEN,
    DONE,
};

struct coord2_t
{
    int x;
    int y;
};

struct node_t
{
    struct coord2_t coord;
    float weight;
    struct node_t *nb[4];
    enum marked state;
};

struct graph_t
{
    struct node_t *nodes;
    int width;
    int height;
};

void graph_init(struct graph_t *g, struct map *map);
struct graph_t graph_create(struct map *map);
void graph_destroy(struct graph_t *g);

#endif /* ! GRAPH_H_ */
