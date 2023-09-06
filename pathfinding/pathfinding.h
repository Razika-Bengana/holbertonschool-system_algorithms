#ifndef PATHFINDING_H
#define PATHFINDING_H


#include "queues.h"
#include "graphs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * struct point_s - Structure storing coordinates
 *
 * @x: X coordinate
 * @y: Y coordinate
 */

typedef struct point_s
{
	int x;
	int y;
} point_t;


/* task 0 */
queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target);
char **create_copy_of_map(char **map, int rows, int cols);
int find_path(char **map, int rows, int cols, point_t const *target,
	      point_t const *start, queue_t *path);
point_t *create_point(int x, int y);
int is_invalid(int rows, int cols, point_t const *point);
int points_equal(point_t const *p1, point_t const *p2);
void reverse_queue(queue_t *queue);


#endif /* PATHFINDING_H */
