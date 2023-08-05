#include "graphs.h"

/**
 * breadth_first_traverse - proogram that performs breadth-first traversal
 * on a graph
 *
 * @graph: a pointer to the graph to traverse
 * @vertex_action: a pointer to the function to be applied to each vertex
 *
 * Return: the depth of traversal
 **/

size_t breadth_first_traverse(const graph_t *graph, void (*vertex_action)
			      (const vertex_t *vertex, size_t depth))
{
	size_t depth, current_round_size, next_round_size;
	vertex_t **vertex_queue;
	char *visited_vertices;
	edge_t *edge;
	int queue_front, vertex_index;

	if (!graph || !vertex_action || graph->nb_vertices == 0)
		return (0);

	visited_vertices = calloc(graph->nb_vertices, sizeof(char));
	vertex_queue = calloc(graph->nb_vertices + 1, sizeof(vertex_t *));
	vertex_queue[0] = graph->vertices;
	visited_vertices[0] = 1;
	depth = 0;
	queue_front = 0;
	current_round_size = 1;
	next_round_size = 0;
	for (vertex_index = 0; vertex_queue[vertex_index]; vertex_index++)
	{
		vertex_action(vertex_queue[vertex_index], depth);
		for (edge = vertex_queue[vertex_index]->edges; edge; edge =
			     edge->next)
		{
			if (visited_vertices[edge->dest->index] == 0)
			{
				vertex_queue[queue_front++] = edge->dest;
				visited_vertices[edge->dest->index] = 1;
				next_round_size += 1;
			}
		}
		if (--current_round_size == 0)
		{
			depth++;
			current_round_size = next_round_size;
			next_round_size = 0;
		}
	}
	free(visited_vertices);
	free(vertex_queue);
	return (depth);
}
