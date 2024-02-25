#include "nary_trees.h"

/**
 * path_exists - program that checks if a path exists in an N-ary tree
 *
 * @root: a pointer to the root node of the N-ary tree
 * @path: the NULL terminated array of strings representing the path
 *
 * Return: 1 if the path exists, 0 otherwise
 */

int path_exists(nary_tree_t const *root, char const * const *path)
{
	nary_tree_t *child;

	if (!root || !path || !*path)
		return (0);

	if (!*path[0])
		return (0);

	if (strcmp(root->content, *path) == 0)
	{

		if (!*(path + 1))
			return (1);

		// Recursively check for the rest of the path among the children
		for (child = root->children; child; child = child->next)
		{
			if (path_exists(child, path + 1))
				return (1); // Path exists in one of the subtrees
		}
	}

	// If no match is found or the end of the path is not reached, the path does not exist
	return (0);
}