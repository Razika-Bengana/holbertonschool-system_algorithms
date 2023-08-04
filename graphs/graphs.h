#ifndef GRAPHS_H
#define GRAPHS_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/**
 * enum edge_type_e - Enumerates the different types of
 * connection between two vertices
 *
 * @UNIDIRECTIONAL: The connection is made only in one way
 * @BIDIRECTIONAL: The connection is made in two ways
 */
typedef enum edge_type_e
{
	UNIDIRECTIONAL = 0,
	BIDIRECTIONAL
} edge_type_t;

/* Define the structure temporarily for usage in the edge_t */
typedef struct vertex_s vertex_t;

/**
 * struct edge_s - Node in the linked list of edges for a given vertex
 * A single vertex can have many edges
 *
 * @dest: Pointer to the connected vertex
 * @next: Pointer to the next edge
 */
typedef struct edge_s
{
	vertex_t    *dest;
	struct edge_s   *next;
} edge_t;


/**
 * struct vertex_s - Node in the linked list of vertices in the adjacency list
 *
 * @index: Index of the vertex in the adjacency list.
 * @content: Custom data stored in the vertex (here, a string)
 * @nb_edges: Number of conenctions with other vertices in the graph
 * @edges: Pointer to the head node of the linked list of edges
 * @next: Pointer to the next vertex in the adjacency linked list
 *   This pointer points to another vertex in the graph, but it
 *   doesn't stand for an edge between the two vertices
 */
struct vertex_s
{
	size_t      index;
	char        *content;
	size_t      nb_edges;
	edge_t      *edges;
	struct vertex_s *next;
};

/**
 * struct graph_s - Representation of a graph
 * We use an adjacency linked list to represent our graph
 *
 * @nb_vertices: Number of vertices in our graph
 * @vertices: Pointer to the head node of our adjacency linked list
 */
typedef struct graph_s
{
	size_t      nb_vertices;
	vertex_t    *vertices;
} graph_t;


/* task 0. Create graph */
graph_t *graph_create(void);

/* task 1. Add a vertex */
vertex_t *graph_add_vertex(graph_t *graph, const char *str);
void graph_display(const graph_t *graph);

/* task 2. Add an edge */
edge_t *graph_add_single_edge(vertex_t *src_vertex, vertex_t *dest_vertex);
int graph_add_edge(graph_t *graph, const char *src,
		   const char *dest, edge_type_t type);

/* task 3. Delete graph */
void graph_delete(graph_t *graph);

/* task 4. Depth-first traversal */
size_t depth_first_traverse(const graph_t *graph, void (*action)
			    (const vertex_t *v, size_t depth));
void dfs_helper(const vertex_t *current_vertex, size_t depth,
		       int *visited, void (*action)
		       (const vertex_t *v, size_t depth), size_t *max_depth);


#endif /* GRAPHS_H */
