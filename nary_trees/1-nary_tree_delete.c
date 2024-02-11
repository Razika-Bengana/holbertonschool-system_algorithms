#include "nary_trees.h"

/**
 * nary_tree_delete - program that deletes an 'N-ary tree', freeing all allocated memory
 *
 * this function uses a depth-first approach to recursively free each node,
 * starting from the leaf nodes and working up to the root;
 * it ensures all child nodes are deleted before freeing the parent node,
 * preventing memory leaks and dangling pointers
 *
 * @tree: the root of the N-ary tree to delete;
 *        if NULL, the function does nothing
 *
 * Return: nothing (void)
 */

void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *current_child;
	nary_tree_t *next_child;

	if (tree == NULL)
	{
		return;
	}

	/* Recursively delete all children */
	current_child = tree->children;

	while (current_child != NULL)
	{
		next_child = current_child->next; /* Save next child before freeing */
		nary_tree_delete(current_child);
		current_child = next_child;
	}

	free(tree->content);
	free(tree);
}
