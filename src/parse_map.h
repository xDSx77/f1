#ifndef PARSE_MAP_H_
#define PARSE_MAP_H_
#include "graph.h"
#include "control.h"

float map_get_finish_x(struct map *map);
float map_get_finish_y(struct map *map);
unsigned find_unseen_start(struct node_t *start, struct graph_t g);
void update_node(struct node_t *cur, struct graph_t g, struct map *map,
    int *x_nb, int *y_nb);
void update_finish(struct node_t *cur, struct graph_t g, int *x_nb, int *y_nb);
int find_index_min(struct node_t *cur);
struct node_t *find_unseen(struct node_t *cur);
struct coord2_t *find_path(struct map *map, int start_x, int start_y,
    int finish_x, int finish_y);
void print_path(struct coord2_t *path);

#endif /* ! PARSE_MAP_H_ */
