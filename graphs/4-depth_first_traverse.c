#include "graphs.h"

/**
 * dfs_helper - the helper function for depth-first traversal
 *
 * @current_vertex: the current vertex being visited
 * @depth: the depth of the current vertex
 * @visited: array to keep track of visited vertices
 * @action: pointer to the function to be called for each visited vertex
 * @max_depth: pointer to the maximum depth encountered during traversal
 *
 * Return:nothing (void)
 */

void dfs_helper(const vertex_t *current_vertex, size_t depth,
		       int *visited, void (*action)
		       (const vertex_t *v, size_t depth), size_t *max_depth)
{
	edge_t *current_edge = current_vertex->edges;

	visited[current_vertex->index] = 1;

	if (depth > *max_depth)
		*max_depth = depth;

	action(current_vertex, depth);

	while (current_edge)
	{
		if (!visited[current_edge->dest->index])
			dfs_helper(current_edge->dest, depth + 1, visited,
				   action, max_depth);

		current_edge = current_edge->next;
	}
}

/**
 * depth_first_traverse - program that traverses a graph using
 * depth-first algorithm
 *
 * @graph: a pointer to the graph to traverse
 * @action: a pointer to the function to be called for each visited vertex
 *
 * Return: the biggest vertex depth, or 0 on failure
 */

size_t depth_first_traverse(const graph_t *graph, void (*action)
			    (const vertex_t *v, size_t depth))
{
	size_t max_depth = 0;
	int *visited = calloc(graph->nb_vertices, sizeof(int));

	if (!graph || !action)
		return (0);

/* Visited array to keep track of visited vertices */

	if (!visited)
		return (0);

	dfs_helper(graph->vertices, 0, visited, action, &max_depth);

	free(visited);
	return (max_depth);
}
