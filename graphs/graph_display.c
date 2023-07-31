#include "graphs.h"

/**
 * graph_display - program that displays the contents of a graph
 *
 * @graph: pointer to the graph to display
 *
 * this function prints the contents of a graph in the form of
 * an adjacency list;
 * tt prints each vertex's index, content, and its connected vertices (edges);
 * the format is as follows:
 * [vertex_index] vertex_content -> [connected_vertex_index]-> ...
 * [vertex_index] vertex_content -> [connected_vertex_index]-> ...
 *   ...
 *
 * @graph: Pointer to the graph to display.
 *
 * Return: Nothing (void)
 */

void graph_display(const graph_t *graph)
{
	vertex_t *current_vertex;

/* Check if the graph is NULL */
	if (!graph)
		return;

	printf("Number of vertices: %lu\n", graph->nb_vertices);

/* Traverse through each vertex in the graph */
	for (current_vertex = graph->vertices; current_vertex;
	     current_vertex = current_vertex->next)
	{
		edge_t *current_edge;

/* Print the vertex's index and content */
		printf("[%lu] %s", current_vertex->index,
		       current_vertex->content);

/* Check if the vertex has any connected vertices (edges) */
		if (current_vertex->edges)
			printf(" ->");

/* Traverse through each edge of the current vertex */
		for (current_edge = current_vertex->edges; current_edge;
		     current_edge = current_edge->next)
		{
			if (current_edge->dest)
				printf("%lu", current_edge->dest->index);
			else
				printf("nil");

			if (current_edge->next)
				printf("->");
		}

		printf("\n");
	}
}
