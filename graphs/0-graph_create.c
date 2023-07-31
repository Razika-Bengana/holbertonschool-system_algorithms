#include "graphs.h"

/**
 * graph_create - program that creates an empty graph_t structure
 *
 * Return: a pointer to the newly created graph_t structure on success,
 * or NULL if memory allocation fails
 */

graph_t *graph_create(void)
{
/* Allocate memory for the graph_t structure */
	graph_t *graph = (graph_t *)malloc(sizeof(graph_t));

/* Check if memory allocation was successful */
	if (graph)
	{
/* Initialize the graph fields */
/* Number of vertices is set to 0 as the graph is empty */
		graph->nb_vertices = 0;

/* The adjacency linked list starts empty, no vertices yet */
		graph->vertices = NULL;
	}

	return (graph);
}
