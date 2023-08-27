#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdlib.h>
#include <stddef.h>
#include "heap.h"

/**
 * struct symbol_s - Stores a char and its associated frequency
 *
 * @data: The character
 * @freq: The associated frequency
 */
typedef struct symbol_s
{
	char data;
	size_t freq;
} symbol_t;


/* task 5 */
symbol_t *symbol_create(char data, size_t freq);


/* task 6 */
int compare_frequencies(void *p1, void *p2);
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);


/* task 7 */
int huffman_extract_and_insert(heap_t *priority_queue);


/* task 8 */
void freeNestedNode(void *data);
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size);


#endif /* HUFFMAN_H */
