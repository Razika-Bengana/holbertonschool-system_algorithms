#include "huffman.h"

/**
 * huffman_extract_and_insert - program that extracts two nodes with
 * the lowest frequencies from the given min heap priority queue,
 * calculates the sum of their frequencies, and inserts a new binary tree node
 * representing the combined frequency back into the priority queue
 *
 * this function is a crucial step in the Huffman coding algorithm;
 * tt performs the following steps:
 * 1. Extracts the two nodes with the lowest frequencies from the priority
 * queue
 * 2. Calculates the sum of the frequencies of the two extracted nodes
 * 3. Creates a new symbol with a dummy character value and the calculated
 * sum frequency
 * 4. Creates a new binary tree node with the created symbol
 * 5. Assigns the extracted nodes as the left and right children of the
 * new node
 * 6. Inserts the new node back into the priority queue
 *
 * @priority_queue: the min heap of character data and frequencies
 *
 * Return: 1 on success, 0 on failure
 */

int huffman_extract_and_insert(heap_t *priority_queue)
{
	void *ptr1, *ptr2;
	binary_tree_node_t *node, *node1, *node2;
	symbol_t *combined_symbol, *symbol1, *symbol2;

	ptr1 = heap_extract(priority_queue);
	ptr2 = heap_extract(priority_queue);
	if (ptr1 == NULL || ptr2 == NULL)
		return (0);

	node1 = (binary_tree_node_t *)ptr1;
	node2 = (binary_tree_node_t *)ptr2;
	symbol1 = (symbol_t *)node1->data;
	symbol2 = (symbol_t *)node2->data;
	combined_symbol = symbol_create(-1, symbol1->freq + symbol2->freq);
	if (combined_symbol == NULL)
		return (0);

	node = binary_tree_node(NULL, combined_symbol);
	if (node == NULL)
	{
		free(combined_symbol);
		return (0);
	}
	node->left = node1;
	node->right = node2;
	node1->parent = node;
	node2->parent = node;

	if (heap_insert(priority_queue, node) == NULL)
	{
		return (0);
	}

	return (1);
}
