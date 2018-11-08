#include <stdlib.h>
#include <stdio.h> //TODO remove
#include <limits.h>
#include "control.h"
#include "graph.h"

static struct coord2_t neighbors[4] =
{
    {0, -1},
    {-1, 0},
    {1, 0},
    {0, 1},
};

float map_get_finish_x(struct map *map)
{
    float finish_x = 0;
    for (int x = 0; x < map->width; x++)
    {
        for (int y = 0; y < map->height; y++)
        {
            if (map_get_floor(map, x, y) == 3)
                finish_x = x;
        }
    }
    return finish_x + 0.5f;
}

float map_get_finish_y(struct map *map)
{
    float finish_y = 0;
    for (int x = 0; x < map->width; x++)
    {
        for (int y = 0; y < map->height; y++)
        {
            if (map_get_floor(map, x, y) == 3)
                finish_y = y;
        }
    }
    return finish_y + 0.5f;
}

unsigned find_unseen_start(struct node_t *start, struct graph_t g)
{
    int x_nb;
    int y_nb;
    unsigned unseen_start = 0;
    struct node_t *tmp = start;
    for (unsigned i = 0; i < 4; i++)
    {
        x_nb = tmp->coord.x + neighbors[i].x;
        y_nb = tmp->coord.y + neighbors[i].y;
        tmp->nb[i] = g.nodes + (y_nb * g.width + x_nb);
        if (tmp->nb[i]->state == UNSEEN)
            unseen_start++;
    }
    return unseen_start;
}

void update_node(struct node_t *cur, struct graph_t g, struct map *map,
    int *x_nb, int *y_nb)
{
    cur->state = DONE;
    for (int i = 0; i < 4; i++)
    {
        *x_nb = cur->coord.x + neighbors[i].x;
        *y_nb = cur->coord.y + neighbors[i].y;
        cur->nb[i] = g.nodes + (*y_nb * g.width + *x_nb);
        cur->nb[i]->coord.x = *x_nb;
        cur->nb[i]->coord.y = *y_nb;
        if (cur->weight + 1 < cur->nb[i]->weight
            && map_get_floor(map, *x_nb, *y_nb) != 2)
            cur->nb[i]->weight = cur->weight + 1;
    }
}

void update_finish(struct node_t *cur, struct graph_t g, int *x_nb, int *y_nb)
{
    cur->state = DONE;
    for (int i = 0; i < 4; i++)
    {
        *x_nb = cur->coord.x + neighbors[i].x;
        *y_nb = cur->coord.y + neighbors[i].y;
        cur->nb[i] = g.nodes + (*y_nb * g.width + *x_nb);
        cur->nb[i]->coord.x = *x_nb;
        cur->nb[i]->coord.y = *y_nb;
    }
}

int find_index_min(struct node_t *cur)
{
    int index = 0;
    float min = cur->nb[0]->weight;
    for (int k = 0; k < 4; k++)
    {
        if (cur->nb[k]->weight < min)
        {
            min = cur->nb[k]->weight;
            index = k;
        }
    }
    return index;
}

struct node_t *find_unseen(struct node_t *cur)
{
    if (cur->nb[0]->state == UNSEEN)
        cur = cur->nb[0];
    else if (cur->nb[1]->state == UNSEEN)
        cur = cur->nb[1];
    else if (cur->nb[2]->state == UNSEEN)
        cur = cur->nb[2];
    else if (cur->nb[3]->state == UNSEEN)
        cur = cur->nb[3];
    return cur;
}

struct coord2_t *find_path(struct map *map, int start_x, int start_y,
    int finish_x, int finish_y)
{
    struct coord2_t *path = malloc(map->height * map->width *
        sizeof(struct coord2_t));
    if (path == NULL)
        return NULL;
    struct graph_t g = graph_create(map);
    int x_nb;
    int y_nb;
    struct node_t *cur = g.nodes + (start_y * g.width + start_x);
    cur->coord.x = start_x;
    cur->coord.y = start_y;
    cur->weight = 0;
    struct node_t *start = cur;
    unsigned unseen_start = find_unseen_start(start, g);
    for (unsigned number = 0; number < unseen_start; number++)
    {
        while ((cur->coord.x != finish_x && cur->coord.y != finish_y)
            || (cur->coord.x != finish_x && cur->coord.y == finish_y)
            || (cur->coord.x == finish_x && cur->coord.y != finish_y))
        {
            update_node(cur, g, map, &x_nb, &y_nb);
            cur = find_unseen(cur);
        }
        if (number < unseen_start - 1)
            cur = start;
        if (number == unseen_start - 1)
            update_finish(cur, g, &x_nb, &y_nb);
    }
    int index_path = 0;
    while ((cur->coord.x != start_x && cur->coord.y != start_y)
        || (cur->coord.x != start_x && cur->coord.y == start_y)
        || (cur->coord.x == start_x && cur->coord.y != start_y))
    {
        path[index_path] = cur->coord;
        int index = find_index_min(cur);
        cur = cur->nb[index];
        index_path++;
    }
    path[index_path] = cur->coord;
    path[index_path + 1].x = INT_MAX;
    path[index_path + 1].y = INT_MAX;
    graph_destroy(&g);
    return path;
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
