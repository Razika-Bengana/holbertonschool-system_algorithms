#ifndef PATHFINDING_H
#define PATHFINDING_H


#include "queues.h"
#include "graphs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RIGHT {1, 0}
#define BOTTOM {0, 1}
#define LEFT {-1, 0}
#define TOP {0, -1}

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
int point_push(queue_t **queue, int x, int y);
int backtracker(queue_t **queue, int *saw, char **map, int rows,
		int cols, int x, int y, point_t const *target);


#endif /* PATHFINDING_H */
