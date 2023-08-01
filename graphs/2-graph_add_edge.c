#include "graphs.h"

/**
 * find_vertex_by_content - program that find a vertex in the graph
 * by its content
 *
 * @graph: a pointer to the graph to search in
 * @content: the content of the vertex to find
 *
 * Return: a pointer to the vertex if found, or NULL if not found
 */

static vertex_t *find_vertex_by_content(graph_t *graph, const char *content)
{
	vertex_t *current_vertex = graph->vertices;

	while (current_vertex != NULL)
	{
		if (strcmp(current_vertex->content, content) == 0)
		{
			return (current_vertex);
		}
		current_vertex = current_vertex->next;
	}
	return (NULL); /* Vertex not found */
}

/**
 * create_edge - program that creates a new edge from src to dest
 *
 * @src_vertex: a pointer to the source vertex
 * @dest_vertex: a pointer to the destination vertex
 *
 * Return: a pointer to the newly created edge if successful,
 * or NULL if memory allocation fails
 */

static edge_t *create_edge(vertex_t *src_vertex, vertex_t *dest_vertex)
{
	edge_t *new_edge = (edge_t *)malloc(sizeof(edge_t));

	if (new_edge == NULL)
		return (NULL);
	new_edge->dest = dest_vertex;
	new_edge->next = NULL;
	return (new_edge);
}

/**
 * add_edge_to_vertex - program that add a new edge to the linked list
 * of edges for a vertex
 *
 * @vertex: a pointer to the vertex to which the edge will be added
 * @new_edge: a pointer to the new edge to be added
 *
 * Return: 1 on success, 0 on failure
 */

static int add_edge_to_vertex(vertex_t *vertex, edge_t *new_edge)
{
	if (vertex->edges == NULL)
	{
		vertex->edges = new_edge;
	}
	else
	{
		edge_t *current_edge = vertex->edges;

		while (current_edge->next != NULL)
		{
			current_edge = current_edge->next;
		}
		current_edge->next = new_edge;
	}
	vertex->nb_edges++;
	return (1); /* Success */
}

/**
 * graph_add_edge - program that adds an edge between two vertices
 * to an existing graph
 *
 * @graph: a pointer to the graph to add the edge to
 * @src: the string identifying the vertex to make the connection from
 * @dest: the string identifying the vertex to connect to
 * @type: the type of edge (UNIDIRECTIONAL or BIDIRECTIONAL)
 *
 * Return: 1 on success, or 0 on failure;
 * on failure, no edge must have be created, and there must be no memory leak;
 * if either src or dest are not found in any vertex of the graph,
 * the function must fail, and there must be no leak.
 */

int graph_add_edge(graph_t *graph, const char *src, const char *dest,
		   edge_type_t type)
{
	if (graph == NULL || src == NULL || dest == NULL)
		return (0);
	vertex_t *src_vertex = find_vertex_by_content(graph, src);
	vertex_t *dest_vertex = find_vertex_by_content(graph, dest);

	if (src_vertex == NULL || dest_vertex == NULL)
		return (0);

	edge_t *new_edge_src_to_dest = create_edge(src_vertex, dest_vertex);

	if (new_edge_src_to_dest == NULL)
		return (0);

	if (!add_edge_to_vertex(src_vertex, new_edge_src_to_dest))
	{
		free(new_edge_src_to_dest);
		return (0);
	}
/* If it's BIDIRECTIONAL, create the edge from destination to source */
	if (type == BIDIRECTIONAL)
	{
		edge_t *new_edge_dest_to_src = create_edge(dest_vertex, src_vertex);

		if (new_edge_dest_to_src == NULL)
		{
/* If allocation fails, undo the changes made earlier */
			src_vertex->edges = new_edge_src_to_dest->next;
			src_vertex->nb_edges--;
			free(new_edge_src_to_dest);
			return (0);
		}
/* Add the new edge to the destination vertex */
		if (!add_edge_to_vertex(dest_vertex, new_edge_dest_to_src))
		{
			free(new_edge_dest_to_src);
			free(new_edge_src_to_dest);
			return (0);
		}
	}
	return (1); /* Success */
}
