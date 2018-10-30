#include <stdio.h>
#include <math.h>
#include "control.h"
#include "fifo.h"
#include "graph.h"

void *bfs(struct node *g)
{
    struct fifo *f = fifo_init();
    fifo_enqueue(f, g);
    while (!fifo_empty(f))
    {
        g = fifo_dequeue(f);
        if (g->marked == 1)
            continue;
        g-> marked = 1;
        for (size_t i = 0; i < g->len_neighbors; i++)
        {
            if (g->distance + g->neighbors[i]->weight <= g->neighbors[i]->next
        }
    }
}

enum move update(struct car *car)
{
    float speed = sqrtf(powf(car->speed.x, 2.0f) + powf(car->speed.y, 2.0f));
    printf("position x: %f\n", car->position.x);
    printf("position y: %f\n", car->position.y);
    puts("");
    printf("direction x: %f\n", car->direction.x);
    printf("direction y: %f\n", car->direction.y);
    puts("");
    printf("speed : %f\n", speed);
    if (car->direction.x > -1.0f)
        return TURN_RIGHT;
    if (speed < 0.05f)
        return ACCELERATE;
    return DO_NOTHING;
}
