#include "graphs.h"
#include <stdlib.h>

/**
 * graph_delete - program that deletes a graph by freeing
 * all its vertices and edges
 *
 * @graph: the graph to be deleted
 *
 * Return: nothing (void)
 */

void graph_delete(graph_t *graph)
{
	if (!graph)
		return;

	vertex_t *current_vertex = graph->vertices;

	while (current_vertex)
	{
		edge_t *current_edge = current_vertex->edges;

		while (current_edge)
		{
			edge_t *next_edge = current_edge->next;

			free(current_edge);
			current_edge = next_edge;
		}

		vertex_t *next_vertex = current_vertex->next;

		free(current_vertex->content);
		free(current_vertex);
		current_vertex = next_vertex;
	}

	free(graph);
}
