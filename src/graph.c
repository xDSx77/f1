#include <stdlib.h>
#include "control.h"
#include "parse_map.h"
#include "graph.h"

void graph_init(struct graph_t *g, struct map *map)
{
    g->width = map->width;
    g->height = map->height;
    g->nodes = malloc(map->width * map->height * sizeof(struct node_t));
    if (g->nodes == NULL)
        return;
    struct node_t *cur = g->nodes;
    for (int y = 0; y < g->height; y++)
    {
        for (int x = 0; x < g->width; x++)
        {
            cur = g->nodes + (y * g->width + x);
            cur->weight = INFINITY;
            cur->state = UNSEEN;
            if (map_get_floor(map, x, y) == 2)
                cur->state = DONE;
        }
    }
}

struct graph_t graph_create(struct map *map)
{
    struct graph_t g;
    graph_init(&g, map);
    return g;
}

void graph_destroy(struct graph_t *g)
{
    free(g->nodes);
}
