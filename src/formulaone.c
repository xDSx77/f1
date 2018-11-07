#include <stdio.h> //TODO remove
#include <math.h>
#include <limits.h>
#include "control.h"
//#include "fifo.h"
#include "graph.h"
#include "parse_map.h"

enum move update(struct car *car)
{
    float speed = sqrtf(powf(car->speed.x, 2.0f) + powf(car->speed.y, 2.0f));
    float acceleration = sqrtf(powf(car->acceleration.x, 2.0f) +
        powf(car->acceleration.y, 2.0f));
    float start_x = map_get_start_x(car->map);
    float start_y = map_get_start_y(car->map);
    float finish_x = map_get_finish_x(car->map);
    float finish_y = map_get_finish_y(car->map);

    struct coord2_t *path = graph_create(car->map);
    /*int i = 0;
    while (path[i].x != INT_MAX && path[i].y != INT_MAX)
    {
        printf("%d x : %d\n", i, path[i].x);
        i++;
    }*/
    print_path(path);

    printf("start x: %f\n", start_x);
    printf("start y: %f\n\n", start_y);
    printf("position x: %f\n", car->position.x);
    printf("position y: %f\n\n", car->position.y);
    printf("direction x: %f\n", car->direction.x);
    printf("direction y: %f\n\n", car->direction.y);

    float SF_x = fabsf(finish_x - start_x); //abscisse start-finish
    float SF_y = fabsf(finish_y - start_y); //ordonnée start-finish
    float angle_trajectory;
    if (finish_y <= start_y)
        angle_trajectory = 180.0f - atanf(SF_y / SF_x) * (360.0f)/(2.0f * M_PI);
    else
        angle_trajectory = 180.0f + atanf(SF_y / SF_x) * (360.0f)/(2.0f * M_PI);
    //printf("angle trajectory: %f\n", angle_trajectory);

    float angle_rad;
    float angle_deg;
    if (car->direction.y >= 0)
        angle_rad = acosf(car->direction.x) + M_PI;
    else
        angle_rad = -acosf(car->direction.x) + M_PI;
    angle_deg = angle_rad * (360.0f) / (2.0f * M_PI);

    float angle_diff = angle_trajectory - angle_deg;

    printf("angle deg: %f\n", angle_deg);
    printf("angle diff: %f\n\n", angle_diff);
    printf("speed: %f\n\n", speed);
    printf("acceleration: %f\n\n", acceleration);

    enum floortype floor =
        map_get_floor(car->map, (int)car->position.x, (int)car->position.y);
    printf("floor: %x\n\n", floor);
    printf("finish x: %f\n", finish_x);
    printf("finish y: %f\n\n", finish_y);
    printf("-----------------\n\n");

    if (angle_diff > 0.4f)
        return TURN_RIGHT;
    if (angle_diff < -0.4f)
        return TURN_LEFT;

    return ACCELERATE;
    //return DO_NOTHING;
}
