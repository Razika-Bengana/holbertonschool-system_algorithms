#include "pathfinding.h"

/**
 * backtracking_array - Finds a path from a starting point to a target point
 * using backtracking on a 2D map.
 * @map: The 2D character map with 1s representing blocked paths and 0s as
 * walkable.
 * @rows: The number of rows in the map.
 * @cols: The number of columns in the map.
 * @start: The starting point (x, y) for the path.
 * @target: The target point (x, y) to reach.
 * Return: A queue containing the path of points, or NULL if no path is found.
 */

queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target)
{
	queue_t *path = queue_create();
	char **mymap;

	if (!path)
		return (NULL);

	mymap = create_copy_of_map(map, rows, cols);
	if (!mymap)
	{
		queue_delete(path);
		return (NULL);
	}

	if (find_path(mymap, rows, cols, target, start, path))
	{
		return (path);
	}
	else
	{
		queue_delete(path);
		return (NULL);
	}
}

/**
 * create_copy_of_map - Creates a deep copy of a 2D character map.
 * @map: The original 2D character map.
 * @rows: The number of rows in the map.
 * @cols: The number of columns in the map.
 * Return: A copy of the map, or NULL if memory allocation fails.
 */

char **create_copy_of_map(char **map, int rows, int cols)
{
	char **mymap = malloc(rows * sizeof(char *));
	int i;

	if (!mymap)
		exit(1);

	for (i = 0; i < rows; i++)
	{
		mymap[i] = malloc(cols + 1);
		if (!mymap[i])
			exit(1);
		strcpy(mymap[i], map[i]);
	}

	return (mymap);
}

/**
 * find_path - Recursively finds a path from the starting point to the target
 * point using backtracking on a map.
 * @map: The map character grid.
 * @rows: The number of rows in the map.
 * @cols: The number of columns in the map.
 * @target: The target point (x, y) to reach.
 * @start: The starting point (x, y) for the path.
 * @path: The current path queue.
 * Return: 1 if the target is reached, 0 otherwise.
 */

int find_path(char **map, int rows, int cols, point_t const *target,
	      point_t const *start, queue_t *path)
{
	point_t *point;
	int x = start->x;
	int y = start->y;

	if (x < 0 || x >= cols || y < 0 || y >= rows || map[y][x] != '0')
		return (0);

	map[y][x] = '1';

	point = create_point(x, y);
	queue_push_front(path, point);
	printf("Checking coordinates [%d, %d]\n", x, y);

	if (x == target->x && y == target->y)
	{
		reverse_queue(path);
		return (1);
	}

	if (find_path(map, rows, cols, target, create_point(x + 1, y), path) ||
	    find_path(map, rows, cols, target, create_point(x, y + 1), path) ||
	    find_path(map, rows, cols, target, create_point(x - 1, y), path) ||
	    find_path(map, rows, cols, target, create_point(x, y - 1), path))
		return (1);

	free(dequeue(path));

	return (0);
}

/**
 * reverse_queue - Reverses the order of elements in a queue.
 * @queue: The queue to be reversed.
 */

void reverse_queue(queue_t *queue)
{
	queue_node_t *current = queue->front;
	queue_node_t *prev = NULL;
	queue_node_t *next = NULL;

	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}

	queue->front = prev;
}

/**
 * create_point - Creates a point with given x and y coordinates.
 * @x: The x-coordinate of the point.
 * @y: The y-coordinate of the point.
 * Return: A pointer to the created point structure.
 */

point_t *create_point(int x, int y)
{
	point_t *point = malloc(sizeof(point_t));

	if (!point)
		exit(1);
	point->x = x;
	point->y = y;
	return (point);
}

/**
 * is_invalid - Checks if a point is outside the map boundaries.
 * @rows: The number of rows in the map.
 * @cols: The number of columns in the map.
 * @point: The point to check.
 * Return: 1 if the point is invalid (out of bounds), 0 otherwise.
 */

int is_invalid(int rows, int cols, point_t const *point)
{
	return (point->x < 0 || point->x >= cols || point->y < 0 || point->y >= rows);
}

/**
 * points_equal - Checks if two points have the same coordinates.
 * @p1: The first point.
 * @p2: The second point.
 * Return: 1 if the points are equal, 0 otherwise.
 */

int points_equal(point_t const *p1, point_t const *p2)
{
	return (p1->x == p2->x && p1->y == p2->y);
}
