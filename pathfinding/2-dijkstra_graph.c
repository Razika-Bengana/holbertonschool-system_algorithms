#include "pathfinding.h"



queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start, vertex_t const *target)
{
	size_t num_vertices = graph->nb_vertices;
	size_t i, count, min_distance_index, v, neighbor_index, current_index;
	edge_t *edge;
	int min_distance, alt_distance;
	queue_t *path_queue;

	int *distances = (int *)malloc(num_vertices * sizeof(int));
	int *visited = (int *)malloc(num_vertices * sizeof(int));
	vertex_t **previous = (vertex_t **)malloc(num_vertices * sizeof(vertex_t *));

	for (i = 0; i < num_vertices; i++)
	{
		distances[i] = INT_MAX;
		visited[i] = 0;
		previous[i] = NULL;
	}

	distances[start->index] = 0;

	/* Dijkstra's algorithm */
	for (count = 0; count < num_vertices - 1; count++)
	{
		min_distance_index = -1;
		min_distance = INT_MAX;

		for (v = 0; v < num_vertices; v++)
		{
			if (!visited[v] && distances[v] < min_distance)
			{
				min_distance = distances[v];
				min_distance_index = v;
			}
		}

		visited[min_distance_index] = 1;

		edge = graph->vertices[min_distance_index].edges;

		while (edge != NULL)
		{
			neighbor_index = edge->dest->index;
			alt_distance = distances[min_distance_index] + edge->weight;

			if (alt_distance < distances[neighbor_index])
			{
				distances[neighbor_index] = alt_distance;
				previous[neighbor_index] = &(graph->vertices[min_distance_index]);
			}

			edge = edge->next;
		}
	}

	/* Build the path queue */
	path_queue = (queue_t *)malloc(sizeof(queue_t));
	path_queue->front = NULL;
	path_queue->back = NULL;

	current_index = target->index;
	while (previous[current_index] != NULL)
	{
		enqueue(path_queue, previous[current_index]->content);
		current_index = previous[current_index]->index;
	}

	enqueue(path_queue, start->content);

	free(distances);
	free(visited);
	free(previous);

	return (path_queue);
}

void print_visited_vertex(char *vertex_content)
{
	printf("Visited vertex: %s\n", vertex_content);
}

void enqueue(queue_t *queue, void *ptr)
{

	queue_node_t *new_node = (queue_node_t *)malloc(sizeof(queue_node_t));

	if (!new_node)
	{
		fprintf(stderr, "Memory allocation error in enqueue\n");
		exit(EXIT_FAILURE);
	}

	new_node->ptr = ptr;
	new_node->next = NULL;
	new_node->prev = NULL;

	if (is_empty(queue))
	{
		queue->front = new_node;
		queue->back = new_node;
	}
	else
	{
		queue->back->next = new_node;
		new_node->prev = queue->back;
		queue->back = new_node;
	}
}

void *dequeue(queue_t *queue)
{
	queue_node_t *front_node;

	if (is_empty(queue))
	{
		fprintf(stderr, "Cannot dequeue from an empty queue\n");
		exit(EXIT_FAILURE);
	}

	front_node = queue->front;

	queue->front = front_node->next;

	if (queue->front == NULL)
	{
		queue->back = NULL;
	}
	else
	{
		queue->front->prev = NULL;
	}

	void *data = front_node->ptr;

	free(front_node);

	return (data);
}

int is_empty(queue_t *queue)
{
	return queue->front == NULL;
}


