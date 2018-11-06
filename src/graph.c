#include <stdlib.h>
#include <math.h>
#include <stdio.h> //TODO remove
#include "graph.h"

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

struct graph_t graph_create(int width, int height)
{
    struct graph_t g;
    g.width = width;
    g.height = height;
    g.nodes = malloc(width * height * sizeof(struct node_t));
    if (g.nodes == NULL)
        return g;

    struct node_t *cur = g.nodes;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            cur->label = 0;
            cur->state = UNSEEN;
            cur->coord.x = x;
            cur->coord.y = y;
            for (int i = 0; i < 7; i++)
                cur->weights[i] = INFINITY;
            cur++;
        }
    }
    return g;
}

void graph_destroy(struct graph_t *g)
{
    free(g->nodes);
}

/*
void graph_print(struct graph_t *g, struct coord2_t pos)
{
    struct node_t *cur = g->nodes + (pos.y * g->width + pos.x);
    if (cur->state == DONE)
        return;

    cur->state = DONE;

    for (int i = 0; i < 7; i++)
    {
        if (cur->weights[i] == INFINITY)
            continue;
        printf("%f\n", cur->weights[i]);
        struct coord2_t neighbor = {pos.x + neighbors[i].x, pos.y + neighbors[i].y};
        graph_print(g, neighbor);
    };
}*/

struct graph_t *graph_create2(struct graph_t *g, struct map *map)
{
    struct node_t *cur;
    struct node_t *nb;
    int x_nb;
    int y_nb;
    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            cur = g->nodes + (y * g->width + x);
            if (map_get_floor(map, x, y) == 0)
                cur->label = 'r';
            else if (map_get_floor(map, x, y) == 1)
                cur->label = 'g';
            else if (map_get_floor(map, x, y) == 2)
                cur->label = 'b';
            else if (map_get_floor(map, x, y) == 3)
                cur->label = 'f';

            if (cur->label == 'r')
            {
                for (int i = 0; i < 7; i++)
                {
                    x_nb = x + neighbors[i].x;
                    y_nb = y + neighbors[i].y;
                    nb = g->nodes + (y_nb * g->width + x_nb);
                    if (map_get_floor(map, x_nb, y_nb) == 0)
                    {
                        nb->label = 'r';
                        cur->weights[i] = 1.0f;
                    }
                    else if (map_get_floor(map, x_nb, y_nb) == 1)
                    {
                        nb->label = 'g';
                        cur->weights[i] = 2.0f;
                    }
                    else if (map_get_floor(map, x_nb, y_nb) == 2)
                        nb->label = 'b';
                    else if (map_get_floor(map, x_nb, y_nb) == 3)
                    {
                        nb->label = 'f';
                        cur->weights[i] = 0.01f;
                    }
                }
            }
            if (cur->label == 'g')
            {
                for (int j = 0; j < 7; j++)
                {
                    x_nb = x + neighbors[j].x;
                    y_nb = y + neighbors[j].y;
                    nb = g->nodes + (y_nb * g->width + y_nb);
                    if (map_get_floor(map, x_nb, y_nb) == 0)
                    {
                        nb->label = 'r';
                        cur->weights[j] = 1.0f;
                    }
                    else if (map_get_floor(map, x_nb, y_nb) == 1)
                    {
                        nb->label = 'g';
                        cur->weights[j] = 2.0f;
                    }
                    else if (map_get_floor(map, x_nb, y_nb) == 2)
                        nb->label = 'b';
                    else if (map_get_floor(map, x_nb, y_nb) == 3)
                    {
                        nb->label = 'f';
                        cur->weights[j] = 0.01f;
                    }
                }
            }
        }
    }
    return g;
}
