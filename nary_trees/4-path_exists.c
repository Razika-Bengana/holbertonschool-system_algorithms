#include "nary_trees.h"

/**
 * check_node_match - program that checks if the current node matches
 * the expected path node
 *
 * @node_content: the content of the current tree node
 * @expected_content: the expected content from the path
 *
 * Return: 1 if the content matches, 0 otherwise
 */

int check_node_match(char const *node_content, char const *expected_content)
{
	if (strncmp(node_content, expected_content, strlen(node_content) + 1) != 0)
	{
		return (0);
	}
	return (1);
}



/**
 * search_path_in_tree - program that recursively searches for the path
 * in the tree
 *
 * @node: the current node in the N-ary tree
 * @path: the path to search for, represented as a NULL terminated
 *        array of strings
 * @index: the current index in the path array
 *
 * Return: 1 if the path exists in the tree from the current node, 0 otherwise
 */

int search_path_in_tree(nary_tree_t const *node, char const * const *path,
			size_t index)
{
	nary_tree_t *child;

	if (!node || !node->content || path == NULL)
	{
		fprintf(stderr, "search_path_in_tree: NULL parameter\n");
		return (0);
	}

	if (!check_node_match(node->content, path[index]))
	{
		return (0);
	}

	if (path[index + 1] == NULL)
	{
		return (1);
	}

	for (child = node->children; child; child = child->next)
	{
		if (search_path_in_tree(child, path, index + 1))
		{
			return (1);
		}
	}

	return (0);
}



/**
 * path_exists - program that checks if a path exists in an N-ary tree,
 * by checking node content
 *
 * @root: a pointer to the root node of the tree
 * @path: the path to test, represented by a NULL terminated array of strings
 *
 * Return: 1 if a contiguous sequence of nodes with content matching the path
 *         strings in order, or 0 on failure
 */

int path_exists(nary_tree_t const *root, char const * const *path)
{
	if (!root || !path || !path[0])
	{
		return (0);
	}

	return (search_path_in_tree(root, path, 0));
}
