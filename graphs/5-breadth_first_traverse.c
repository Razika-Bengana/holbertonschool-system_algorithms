#include "graphs.h"

/**
 * breadth_first_traverse - program that traverses a graph using
 * breadth-first search
 *
 * @graph: the graph to traverse
 * @action: a function to perform an action on each vertex along with its depth
 *
 * Return: the maximum depth reached during traversal, or 0 on failure
 */

size_t breadth_first_traverse(const graph_t *graph,
			      void (*action)(const vertex_t *v, size_t depth))
{
	vertex_t *start_vertex = graph->vertices;
	char visited_flags[2048] = {0};
	edge_t *edge = current_vertex->edges;
	size_t max_depth = 0;
	/* Simulate a queue using an array (not thread-safe) */
	vertex_t *queue[2048];
	size_t front = 0, rear = 0;

	if (!graph || !action)
		return (0);

	if (!start_vertex)
		return (0);

	queue[rear++] = start_vertex;
	visited_flags[start_vertex->index] = 1;
	while (front < rear)
	{
		vertex_t *current_vertex = queue[front++];
		size_t current_depth = visited_flags[current_vertex->index];

		action(current_vertex, current_depth);

		if (current_depth > max_depth)
			max_depth = current_depth;

		while (edge)
		{
			if (visited_flags[edge->dest->index] == 0)
			{
				queue[rear++] = edge->dest;
				visited_flags[edge->dest->index] =
					current_depth + 1;
			}
			edge = edge->next;
		}
	}
	return (max_depth - 1);
}
