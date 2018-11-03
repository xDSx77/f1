#include <stdio.h>
#include <stdlib.h>
//#include "control.h"
#include "dijkstra.h"
#define INF 99999

struct coor **create_graph(struct map *map)
{
    struct coor **G = calloc(map->height, sizeof(struct coor*));
    if (G == NULL)
        return NULL;

    for (int i = 0; i < map->height; i++)
    {
        G[i] = calloc(map->width, sizeof(struct coor));
        if (G[i] == NULL)
        {
            free(G);
            return NULL;
        }
    }

    for (int i = 0; i < map->height; i++)
    {
        for (int j = 0; j < map->width; j++)
        {
            G[i][j].x = j;
            G[i][j].y = i;
        }
    }
    return G;
}

int **create_adj(struct coor **G, struct map *map)
{
    int n = map->height + map->width;
    int **adj = calloc(n, sizeof(int*));
    if (adj == NULL)
        return NULL;

    for (int i = 0; i < n; i++)
    {
        adj[i] = calloc(n, sizeof(int));
        if (adj[i] == NULL)
        {
            free(adj);
            return NULL;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (j == i)
                adj[i][j] = 0;
            
        }
    }
}
