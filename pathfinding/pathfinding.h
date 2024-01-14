#ifndef PATHFINDING_H
#define PATHFINDING_H


#include "graphs.h"
#include "queues.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


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


/* task 1 */
queue_node_t *graph_fill(queue_t *new_node, int *saw, const vertex_t *current,
			 char *target);
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
			    vertex_t const *target);


/* task 2 */

queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start, vertex_t const *target);
void print_visited_vertex(char *vertex_content);
void enqueue(queue_t *queue, void *ptr);
void *dequeue(queue_t *queue);
int is_empty(queue_t *queue);



#endif /* PATHFINDING_H */
