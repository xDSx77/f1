#include <stdlib.h>
#include <math.h>
#include <stdio.h> //TODO remove
#include <limits.h>
#include "control.h"
#include "parse_map.h"
#include "graph.h"

static struct coord2_t neighbors[4] =
{
    {0, -1},
    {-1, 0},
    {1, 0},
    {0, 1},
};

void graph_init(struct graph_t *g, struct map *map)
{
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

struct coord2_t *graph_create(struct map *map)
{
    struct coord2_t *path = malloc(map->height * map->width);
    if (path == NULL)
        return NULL;

    struct graph_t g;
    g.width = map->width;
    g.height = map->height;
    g.nodes = malloc(map->width * map->height * sizeof(struct node_t));
    if (g.nodes == NULL)
        return NULL;

    int start_x = map_get_start_x(map);
    int start_y = map_get_start_y(map);
    int finish_x = map_get_finish_x(map);
    int finish_y = map_get_finish_y(map);
    int x_nb;
    int y_nb;
    int move;
    graph_init(&g, map);
    struct node_t *cur = g.nodes + (start_y * g.width + start_x);
    cur->coord.x = start_x;
    cur->coord.y = start_y;
    cur->weight = 0;
    while (cur->coord.x != finish_x && cur->coord.y != finish_y)
    {
        move = 0;
        cur->state = DONE;
        for (int i = 0; i < 4; i++)
        {
            x_nb = cur->coord.x + neighbors[i].x;
            y_nb = cur->coord.y + neighbors[i].y;
            cur->nb[i] = g.nodes + (y_nb * g.width + x_nb);
            cur->nb[i]->coord.x = x_nb;
            cur->nb[i]->coord.y = y_nb;
            if (cur->weight + 1 < cur->nb[i]->weight
                && cur->nb[i]->weight != INFINITY)
                cur->nb[i]->weight = cur->weight + 1;
        }

        /*for (int j = 0; j < 4; j++)
        {
            struct node_t *tmp = g.nodes + (start_y * g.width + start_x);
            if (tmp->nb[j]->state == UNSEEN)
            {
                cur = tmp->nb[j];
                move = 1;
                break;
            }
        }*/

        if (move == 1)
            continue;
        else if (map_get_floor(map, cur->coord.x, cur->coord.y - 1) != 2
            && cur->nb[0]->state == UNSEEN)
            cur = cur->nb[0];
        else if (map_get_floor(map, cur->coord.x - 1, cur->coord.y) != 2
            && cur->nb[1]->state == UNSEEN)
            cur = cur->nb[1];
        else if (map_get_floor(map, cur->coord.x + 1, cur->coord.y) != 2
            && cur->nb[2]->state == UNSEEN)
            cur = cur->nb[2];
        else if (map_get_floor(map, cur->coord.x, cur->coord.y + 1) != 2
            && cur->nb[3]->state == UNSEEN)
            cur = cur->nb[3];
    }
    int index_path = 0;
    while (cur->coord.x != start_x && cur->coord.y != start_y)
    {
        path[index_path] = cur->coord;
        float min = cur->nb[0]->weight;
        int index = 0;
        for (int k = 0; k < 4; k++)
        {
            if (cur->nb[k]->weight < min)
            {
                min = cur->nb[k]->weight;
                index = k;
            }
        }
        cur = cur->nb[index];
        index_path++;
    }
    path[index_path] = cur->coord;
    path[index_path + 1].x = INT_MAX;
    path[index_path + 1].y = INT_MAX;

    /*for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            cur->label = 0;
            cur->state = UNSEEN;
            cur->coord.x = x;
            cur->coord.y = y;
            for (int i = 0; i < 7; i++)
                cur->weights[i] = INFINITY;
            cur++;
        }
    }*/

    return path;
}

void graph_destroy(struct graph_t *g)
{
    free(g->nodes);
}

void print_path(struct coord2_t *path)
{
    int i = 0;
    while (path[i].x != INT_MAX && path[i].y != INT_MAX)
    {
        printf("tile %d x: %d\n", i, path[i].x);
        printf("tile %d y: %d\n", i, path[i].y);
        i++;
    }
}
/*
struct graph_t *graph_create2(struct graph_t *g, struct map *map)
{
    struct node_t *cur = g->nodes;
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
            cur++;
        }
    }
    return g;
}

struct graph_t *graph_create3(struct graph_t *g, struct map *map)
{
    struct node_t *cur = g->nodes;
    struct node_t *nb;
    int x_nb;
    int y_nb;
    enum floortype floor_nb;
    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            if (cur->label == 'r')
            {
                for (int i = 0; i < 7; i++)
                {
                    x_nb = x + neighbors[i].x;
                    y_nb = y + neighbors[i].y;
                    nb = g->nodes + (y_nb * g->width + x_nb);
                    floor_nb = map_get_floor(map, x_nb, y_nb);
                    if (floor_nb == 0)
                    {
                        nb->label = 'r';
                        cur->weights[i] = 1.0f;
                    }
                    else if (floor_nb == 1)
                    {
                        nb->label = 'g';
                        cur->weights[i] = 2.0f;
                    }
                    else if (floor_nb == 2)
                        nb->label = 'b';
                    else if (floor_nb == 3)
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
                    nb = g->nodes + (y_nb * g->width + x_nb);
                    floor_nb = map_get_floor(map, x_nb, y_nb);
                    if (floor_nb == 0)
                    {
                        nb->label = 'r';
                        cur->weights[j] = 1.0f;
                    }
                    else if (floor_nb == 1)
                    {
                        nb->label = 'g';
                        cur->weights[j] = 2.0f;
                    }
                    else if (floor_nb == 2)
                        nb->label = 'b';
                    else if (floor_nb == 3)
                    {
                        nb->label = 'f';
                        cur->weights[j] = 0.01f;
                    }
                }
            }
            cur++;
        }
    }
    return g;
}*/
