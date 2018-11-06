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
    char label;
    struct coord2_t coord;
    float weights[8];
    enum marked state;
};

struct graph_t
{
    struct node_t *nodes;
    int width;
    int height;
};

struct graph_t graph_create(int width, int height);
void graph_destroy(struct graph_t *g);
//void graph_print(struct graph_t *g, struct coord2_t pos);
struct graph_t *graph_create2(struct graph_t *g, struct map *map);

#endif /* ! GRAPH_H_ */
