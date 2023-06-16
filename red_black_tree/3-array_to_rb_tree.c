#include "rb_trees.h"

/**
 * array_to_rb_tree - function that builds a Red-Black Tree from an array
 *
 * @array: Pointer to the first element of the array
 * @size: Number of elements in the array
 *
 * Return: Pointer to the root node of the created R-B tree, or NULL on failure
 */

rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
	rb_tree_t *root = NULL;
	size_t i;

	if (array == NULL || size == 0)
		return (NULL);

	for (i = 0; i < size; i++)
		rb_tree_insert(&root, array[i]);

	return (root);
}
