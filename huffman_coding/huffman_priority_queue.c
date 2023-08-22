#include "huffman.h"

/**
 * symbol_cmp - program that compares two symbol_t structures based on their
 * frequencies
 *
 * @p1: a pointer to the first symbol_t structure
 * @p2: a pointer to the second symbol_t structure
 *
 * Return: the difference in frequencies between the symbols
 */

int symbol_cmp(void *p1, void *p2)
{
	symbol_t *s1 = (symbol_t *)p1;
	symbol_t *s2 = (symbol_t *)p2;

	return (s1->freq - s2->freq);
}

/**
 * huffman_priority_queue - program that creates a priority queue
 * for Huffman coding
 *
 * @data: an array of characters
 * @freq: an array of frequencies associated with each character
 * @size: the size of the arrays
 *
 * Return: a pointer to the created min heap (priority queue),
 * or NULL if failed
 */

heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue;
	symbol_t *symbol;
	binary_tree_node_t *node;
	size_t i;

/* Create a priority queue (min heap) using symbol_cmp function to compare */
	priority_queue = heap_create(symbol_cmp);
	if (!priority_queue)
		return (NULL);

/* Build the priority queue using the given data and frequencies */
	for (i = 0; i < size; ++i)
	{
/* Create a symbol_t structure */
		symbol = symbol_create(data[i], freq[i]);
		if (!symbol)
		{
			heap_delete(priority_queue, free);
			return (NULL);
		}

/* Create a binary_tree_node_t for the symbol */
		node = binary_tree_node(NULL, symbol);
		if (!node)
		{
			free(symbol);
			heap_delete(priority_queue, free);
			return (NULL);
		}

/* Insert the node into the priority queue */
		if (!heap_insert(priority_queue, node))
		{
			free(symbol);
			free(node);
			heap_delete(priority_queue, free);
			return (NULL);
		}
	}
	return (priority_queue);
}
