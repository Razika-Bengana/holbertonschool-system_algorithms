#include "heap.h"

binary_tree_node_t *heap_insert_recursive(binary_tree_node_t *node, void *data,
					  int (*data_cmp)(void *, void *));
void heapify_up(binary_tree_node_t *node, int (*data_cmp)(void *, void *));

/**
 * heap_insert - program that inserts a value into a min binary Heap
 * while maintaining the min-heap property
 *
 * this function inserts a new value into the given min binary heap,
 * preserving the min-heap property;
 * the min-heap property ensures that each parent node's value is smaller than
 * or equal to the values of its children;
 *
 * @heap: a pointer to the heap in which the node has to be inserted
 * @data: a pointer containing the data to store in the new node
 *
 * Return: a pointer to the created node containing data, or NULL if it fails
 */

binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new_node;

	if (heap == NULL || data == NULL)
		return (NULL);

	new_node = binary_tree_node(NULL, data);

	if (new_node == NULL)
		return (NULL);

	heap->size++;

	if (heap->root == NULL)
	{
		heap->root = new_node;
		return (new_node);
	}

	heap->root = heap_insert_recursive(heap->root, data, heap->data_cmp);

	return (new_node);
}

/**
 * heap_insert_recursive - program that recursively inserts a value into
 * a min binary heap
 *
 * @node: the current node being evaluated
 * @data: a pointer containing the data to store in the new node
 * @data_cmp: the function to compare two nodes data
 *
 * Return: a pointer to the modified node
 */

binary_tree_node_t *heap_insert_recursive(binary_tree_node_t *node, void *data,
					  int (*data_cmp)(void *, void *))
{
	if (node == NULL)
	{
		return (binary_tree_node(NULL, data));
	}

	if (data_cmp(data, node->data) >= 0)
	{
		node->left = heap_insert_recursive(node->left, data, data_cmp);
		node->left->parent = node;
	}
	else
	{
		node->right = heap_insert_recursive(node->right, data,
						    data_cmp);
		node->right->parent = node;
	}

	heapify_up(node, data_cmp);

	return (node);
}

/**
 * heapify_up - progrma that performs heapify-up operation to maintain
 * min binary heap property
 *
 * @node: the node to start heapify-up from
 * @data_cmp: the function to compare two nodes data
 */

void heapify_up(binary_tree_node_t *node, int (*data_cmp)(void *, void *))
{
	void *temp;

	while (node->parent != NULL && data_cmp(node->data,
						node->parent->data) < 0)
	{
		temp = node->data;
		node->data = node->parent->data;
		node->parent->data = temp;
		node = node->parent;
	}
}
