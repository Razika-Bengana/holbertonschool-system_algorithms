#include "heap.h"

/**
 * recursive_node_free - program that recursively frees the binary tree nodes
 * and their data
 *
 * @node: the current node to be freed
 * @free_data: a pointer to the function that frees the data
 *
 * Return: nothing (void)
 */

void recursive_node_free(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (node == NULL)
	{
		return;
	}

/* Recursively free the left and right subtrees */
	recursive_node_free(node->left, free_data);
	recursive_node_free(node->right, free_data);

/* Free the data stored in the node if free_data is provided */
	if (free_data != NULL)
	{
		free_data(node->data);
	}

/* Free the current node */
	free(node);
}

/**
 * heap_delete - program that deallocates a heap and its associated
 * binary tree nodes
 *
 * @heap: a pointer to the heap to be deallocated
 * @free_data: a pointer to the function that frees the data in nodes
 * (or NULL if not needed)
 *
 * Return: nothing (void)
 */

void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (heap == NULL)
	{
		return;
	}

/* Recursively free all nodes in the binary tree */
	recursive_node_free(heap->root, free_data);

/* Free the heap structure itself */
	free(heap);
}
