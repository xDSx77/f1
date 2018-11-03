#include "control.h"
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

struct coor
{
    int x;
    int y;
};

struct coor **create_graph(struct map *map);
int **create_adj(struct coor **G, struct map *map);
struct vector2 get_start(float x, float y);
void dijkstra(struct vector2 **adj, int height, int width, struct vector2 start);

#endif /* ! DIJKSTRA_H */
