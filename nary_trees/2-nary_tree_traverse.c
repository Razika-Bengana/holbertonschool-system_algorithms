#include "nary_trees.h"

/**
 * nary_tree_traverse_helper - a recursive helper function designed to perform
 * depth-first traversal on an N-ary tree
 *
 * this function applies a specified action to each node, tracking and updating
 * the maximum depth encountered;
 * it calls itself recursively for each child of the current node, incrementing
 * the depth at each level;
 * if the current node's depth exceeds the known maximum, it updates the
 * maximum depth accordingly;
 * it ensures every node in the tree is visited, applying the action function
 * at each step
 *
 * @node: the current node being visited in the traversal
 * @action: a callback function to be executed on each node, which takes the
 *          node and its depth as arguments
 * @depth: the depth of the current node in the tree, starting from 0 for
 *         the root
 * @max_depth: a pointer to the maximum depth encountered during the traversal,
 *             updated throughout the recursion
 *
 * Return: nothing (void)
 */

void nary_tree_traverse_helper(nary_tree_t const *node,
			       void (*action)(nary_tree_t const *node, size_t depth),
			       size_t depth, size_t *max_depth)
{
	nary_tree_t const *child;

	if (!node)
		return;

	action(node, depth);

	if (depth > *max_depth)
	{
		*max_depth = depth;
	}

	child = node->children;

	while (child != NULL)
	{
		nary_tree_traverse_helper(child, action, depth + 1, max_depth);
		child = child->next; /* Move to the next sibling */
	}
}



/**
 * nary_tree_traverse - program that initiates traversal of an 'N-ary tree' from
 * the root, executing a user-defined action on each node
 *
 * this function leverages 'nary_tree_traverse_helper' to recursively traverse
 * the tree, applying the provided action at each node and determining the tree's
 * maximum depth;
 * it calculates and returns the maximum depth of the tree as a 'size_t' value
 *
 * @root: the root node of the N-ary tree to start traversal from
 * @action: a pointer to a function that will be executed for each node
 *          encountered;
 *          this function should accept a node and its depth as parameters
 *
 * Return: the maximum depth encountered across all nodes in the tree
 */

size_t nary_tree_traverse(nary_tree_t const *root, void (*action)(nary_tree_t const *node, size_t depth))
{
	size_t max_depth = 0;

	nary_tree_traverse_helper(root, action, 0, &max_depth);

	return (max_depth);
}
