#include "graphs.h"

/**
 * freeQueue - program that frees all the memory allocated for the queue and its nodes
 *
 * this function iterates through each node in the queue, freeing them individually,
 * and finally frees the queue itself;
 * it ensures that all the memory allocated for queue management is properly released
 *
 * @queue: a pointer to the 'GraphQueue' structure to be freed
 *
 * Return: nothing (void)
 */

void freeQueue(GraphQueue *queue)
{
	GraphQueueNode *currentNode, *tempNode;

	currentNode = queue->head;
	while (currentNode)
	{
		tempNode = currentNode;
		currentNode = currentNode->next;
		free(tempNode);
	}
	free(queue);
}



/**
 * pushToQueue - program that adds a new vertex to the queue
 *
 * this function creates a new 'GraphQueueNode', assigns the provided vertex and depth to it,
 * and adds it to the end of the queue;
 * it handles memory allocation for the new node and updates the queue's tail;
 * in case of memory allocation failure, it ensures that the queue is properly freed
 *
 * @queue: a pointer to the GraphQueue where the vertex will be added
 * @vertex: a pointer to the vertex to be added to the queue
 * @depth: the depth level of the vertex in the graph traversal
 *
 * Return: 1 if the vertex is successfully added, 0 if an error occurs
 */

int pushToQueue(GraphQueue *queue, vertex_t *vertex, size_t depth)
{
	GraphQueueNode *newNode;

	newNode = calloc(1, sizeof(GraphQueueNode));
	if (!newNode)
	{
		freeQueue(queue);
		return (0);
	}
	newNode->vertex = vertex;
	newNode->depth = depth;
	if (!queue->tail)
	{
		queue->tail = queue->head = newNode;
	}
	else
	{
		queue->tail->next = newNode;
		queue->tail = newNode;
	}
	queue->size++;
	return (1);
}



/**
 * popFromQueue - program that removes and retrieves a vertex from the front of the queue
 *
 * this function removes the node at the front of the queue, retrieves the vertex and its depth,
 * and then frees the memory of the node;
 * it adjusts the head of the queue and ensures the correct management of the queue's size
 *
 * @queue: a pointer to the 'GraphQueue' from which the vertex will be removed
 * @vertex: a pointer to store the removed vertex
 * @depth: a pointer to store the depth of the removed vertex
 *
 * Return: 1 if the vertex is successfully removed, 0 if the queue is empty
 */

int popFromQueue(GraphQueue *queue, vertex_t **vertex, size_t *depth)
{
	GraphQueueNode *frontNode;

	if (!queue || !queue->head)
		return (0);

	frontNode = queue->head;
	queue->head = queue->head->next;

	if (!queue->head)
		queue->tail = NULL;

	*vertex = frontNode->vertex;
	*depth = frontNode->depth;
	queue->size--;
	free(frontNode);

	return (1);
}



/**
 * breadth_first_traverse - program that performs a breadth-first search (BFS) traversal of a graph
 *
 * this function implements the BFS algorithm for graph traversal;
 * it initializes a queue to manage the vertices to be visited and an array to track visited vertices;
 * it iteratively visits vertices in a breadth-first manner, applying the provided action function to each
 * vertex and tracking the maximum depth reached;
 * the function handles memory allocation for traversal management and ensures cleanup
 *
 * @graph: Pointer to the graph structure to be traversed
 * @action: Function pointer to the action to be performed on each visited vertex
 *
 * Return: the maximum depth reached in the traversal, or 0 on failure
 */


size_t breadth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth))
{
	GraphQueue *queue;
	vertex_t *currentVertex;
	edge_t *currentEdge;
	size_t maxDepth = 0, currentDepth, i, queueSize;
	size_t *visited;

	if (!graph || !action || !graph->nb_vertices)
		return (0);

	visited = calloc(graph->nb_vertices, sizeof(size_t));
	if (!visited)
		return (0);

	queue = calloc(1, sizeof(GraphQueue));

	if (!queue)
	{
		free(visited);
		return (0);
	}

	visited[graph->vertices->index] = 1;
	pushToQueue(queue, graph->vertices, 0);

	while (queue->size)
	{
		queueSize = queue->size;
		for (i = 0; i < queueSize; i++)
		{
			popFromQueue(queue, &currentVertex, &currentDepth);
			action(currentVertex, currentDepth);
			maxDepth = (maxDepth > currentDepth) ? maxDepth : currentDepth;

			for (currentEdge = currentVertex->edges; currentEdge; currentEdge = currentEdge->next)
			{
				if (!visited[currentEdge->dest->index])
				{
					visited[currentEdge->dest->index] = 1;
					pushToQueue(queue, currentEdge->dest, currentDepth + 1);
				}
			}
		}
	}

	free(visited);
	freeQueue(queue);
	return (maxDepth);
}
