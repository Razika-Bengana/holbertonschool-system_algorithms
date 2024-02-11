#include "nary_trees.h"

/**
 * max - program that determines the greater of two 'size_t' values
 *
 * this utility function is fundamental in comparing sizes, such as depths
 * of subtrees, to compute the maximum diameter of an 'N-ary tree';
 * by comparing two values, it facilitates identifying the longest paths
 * in the tree
 *
 * @a: the first value for comparison
 * @b: the second value for comparison
 *
 * Return: the larger of the two input values
 */

size_t max(size_t a, size_t b)
{
	return ((a > b) ? a : b);
}



/**
 * nary_tree_diameter_helper - program that calculates the height of a subtree
 * and updates the diameter of the 'N-ary tree'
 *
 * this recursive function traverses the tree from a given node downwards, updating
 * the diameter to reflect the longest path found within the subtree;
 * it achieves this by comparing the depths of the two deepest subtrees at each node,
 * ensuring the diameter reflects the longest possible path between any two nodes
 * in the tree
 *
 * @node: the node from which the subtree's height and potential diameter contributions
 *        are calculated
 * @diameter: a pointer to the value representing the current maximum diameter of the tree,
 *            which is updated as necessary
 *
 * Return: the height of the subtree rooted at the specified node,
 *         facilitating the calculation of diameters at higher recursive levels
 */

size_t nary_tree_diameter_helper(nary_tree_t const *node, size_t *diameter)
{
	size_t max_depth1, max_depth2;
	size_t child_depth;

	if (node == NULL)
	{
		return (0);
	}

	max_depth1 = 0, max_depth2 = 0;

	for (nary_tree_t const *child = node->children; child != NULL; child = child->next)
	{
		child_depth = nary_tree_diameter_helper(child, diameter);

		if (child_depth > max_depth1)
		{
			max_depth2 = max_depth1;
			max_depth1 = child_depth;
		}
		else if (child_depth > max_depth2)
		{
			max_depth2 = child_depth;
		}
	}

	*diameter = max(*diameter, max_depth1 + max_depth2);

	/* Return height of the current subtree */
	return (max_depth1 + 1);
}



/**
 * nary_tree_diameter - program that computes the diameter of an N-ary tree,
 * defined as the longest path between any two nodes
 *
 * this function initiates the recursive process to traverse the tree,
 * applying the helper function to calculate the diameter from the root node;
 * it leverages the 'depth-first search' approach to explore each path and
 * determine the maximum length among them
 *
 * @root: the root node of the tree from which to calculate the diameter
 *
 * Return: the maximum diameter of the tree, represented as the length
 *         of the longest path
 */

size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t diameter = 0;

	nary_tree_diameter_helper(root, &diameter);

	return (diameter);
}
