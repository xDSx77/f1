#include "control.h"

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
