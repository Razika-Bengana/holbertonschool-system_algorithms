#include "graphs.h"

/**
 * breadth_first_traverse - program that traverses a graph using
 * the breadth-first algorithm
 *
 * @graph: a pointer to the graph to traverse
 * @action: a pointer to a function that acts on each traversed vertex
 *
 * Return: the maximum depth reached during traversal
 */

size_t breadth_first_traverse(const graph_t *graph, void (*action)
			      (const vertex_t *v, size_t depth))
{
	size_t current_depth, current_round_size, next_round_size;
	vertex_t **current_vertices;
	char *visited;
	edge_t *edge;
	size_t current_index, current_vertex_index, next_vertex_index;

	if (!graph || !action || graph->nb_vertices == 0)
		return (0);

	visited = calloc(graph->nb_vertices, sizeof(char));
	current_vertices = calloc(graph->nb_vertices + 1, sizeof(vertex_t *));
	current_vertices[0] = graph->vertices;
	visited[0] = 1, current_depth = 0, current_vertex_index = 1,
		next_vertex_index = 0, current_round_size = 1,
		next_round_size = 0;
	for (current_index = 0; current_vertices[current_index];
	     current_index++)
	{
		action(current_vertices[current_index], current_depth);
		for (edge = current_vertices[current_index]->edges; edge;
		     edge = edge->next)
		{
			if (visited[edge->dest->index] == 0)
			{
				current_vertices[current_vertex_index++] =
					edge->dest;
				visited[edge->dest->index] = 1;
				next_round_size += 1;
			}
		}
		if (--current_round_size == 0)
		{
			current_depth++;
			current_round_size = next_round_size;
			next_round_size = 0;
		}
	}
	free(visited);
	free(current_vertices);
	return (current_depth - 1);
}
