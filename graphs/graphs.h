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
 *
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
 * @nb_edges: Number of connections with other vertices in the graph
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
 *
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



/**
 * struct GraphQueueNode - Node structure for a queue in graph traversal
 *
 * This structure represents a single node in a queue used for graph traversal.
 * Each node holds a vertex from the graph, the depth of that vertex in the
 * traversal, and a pointer to the next node in the queue.
 *
 * @vertex: Pointer to the vertex associated with this node
 * @depth: The depth of the vertex in the traversal from the starting point
 * @next: Pointer to the next node in the queue
 */

typedef struct GraphQueueNode
{
    vertex_t *vertex;
    size_t depth;
    struct GraphQueueNode *next;
} GraphQueueNode;



/**
 * struct GraphQueue - Queue structure for managing nodes in graph traversal
 *
 * This structure represents a queue used for breadth-first traversal of a graph.
 * It keeps track of the front and rear of the queue (head and tail), as well as
 * the total number of nodes currently in the queue. This queue is used to
 * manage the order in which vertices are visited during the traversal.
 *
 * @head: Pointer to the first node in the queue
 * @tail: Pointer to the last node in the queue
 * @size: The number of nodes currently in the queue
 */

typedef struct GraphQueue
{
    GraphQueueNode *head;
    GraphQueueNode *tail;
    size_t size;
} GraphQueue;



void graph_display(const graph_t *graph);

/* task 0. Create graph */
graph_t *graph_create(void);

/* task 1. Add a vertex */
vertex_t *graph_add_vertex(graph_t *graph, const char *str);

/* task 2. Add an edge */
edge_t *graph_add_single_edge(vertex_t *src_vertex, vertex_t *dest_vertex);
int graph_add_edge(graph_t *graph, const char *src,
		   const char *dest, edge_type_t type);

/* task 3. Delete graph */
void graph_delete(graph_t *graph);

/* task 4. Depth-first traversal */
size_t traverseVerticesRecursively(vertex_t *vertex, char *visited_flags,
				   size_t current_depth, void (*vertex_action)
				   (const vertex_t *v, size_t depth));
size_t depth_first_traverse(const graph_t *graph, void (*action)
			    (const vertex_t *v, size_t depth));

/* task 5. Breadth-first traversal */
void freeQueue(GraphQueue *queue);
int pushToQueue(GraphQueue *queue, vertex_t *vertex, size_t depth);
int popFromQueue(GraphQueue *queue, vertex_t **vertex, size_t *depth);
void processEdges(GraphQueue *queue, const vertex_t *vertex, size_t currentDepth,
		  size_t *visited);
size_t breadth_first_traverse(const graph_t *graph, void (*action)
			      (const vertex_t *v, size_t depth));


#endif /* GRAPHS_H */
