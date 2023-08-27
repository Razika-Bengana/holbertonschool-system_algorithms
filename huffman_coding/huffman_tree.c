#include "huffman.h"

/**
 * huffman_tree - program that constructs a Huffman tree from given character
 * data and their frequencies
 *
 * @data: an array of characters
 * @freq: an array of frequencies associated with characters
 * @size: the size of the arrays
 *
 * Return: a pointer to the root node of the constructed Huffman tree
 */

binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	heap_t *heap;
	int extraction_success;

	if (data == NULL || freq == NULL || size <= 0)
		return (NULL);

	heap = huffman_priority_queue(data, freq, size);
	while (heap->root->right || heap->root->left)
	{
		extraction_success = huffman_extract_and_insert(heap);
		if (!extraction_success)
			return (NULL);
	}

	root = (binary_tree_node_t *)heap->root->data;
	heap->root = NULL;
	heap_delete(heap, NULL);

	return (root);
}
