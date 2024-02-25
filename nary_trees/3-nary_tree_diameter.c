#include "nary_trees.h"


/**
 * calculate_max_depths - program that calculates the maximum depths of child nodes
 *
 * @child: a pointer to the current child node
 * @depth: the depth of the current node
 * @max_depth: the updated maximum depth found
 * @diameter: a pointer to the current maximum diameter
 *
 * Return: the maximum depth of the current node
 */

size_t calculate_max_depths(nary_tree_t const *child, size_t depth, size_t *diameter)
{
	if (!child)
	{
		return (depth);
	}
	return find_tree_diameter(child, depth + 1, diameter);
}



/**
 * update_diameter - program that updates the current diameter based on child depths
 *
 * @max_depth_1: the first maximum depth
 * @max_depth_2: the second maximum depth
 * @depth: the current depth
 * @diameter: a pointer to current maximum diameter
 *
 * Return: nothing (void)
 */

void update_diameter(size_t max_depth_1, size_t max_depth_2, size_t depth, size_t *diameter)
{
	size_t current_diameter = (max_depth_1 - depth) + (max_depth_2 - depth) + 1;

	if (current_diameter > *diameter)
	{
		*diameter = current_diameter;
	}
}



/**
 * find_tree_diameter - program that recursively finds the diameter of an N-ary tree
 *
 * @root: a pointer to the root node of the tree to measure
 * @depth: the depth of the current node
 * @diameter: a pointer to the current maximum diameter
 *
 * Return: the maximum depth from the current node
 */

size_t find_tree_diameter(nary_tree_t const *root, size_t depth, size_t *diameter)
{
	size_t *child_depths = NULL, max_depth_1 = depth, max_depth_2 = depth;
	nary_tree_t *temp;
	size_t i;

	if (!root || !diameter)
	{
		return (0);
	}

	if (root->nb_children)
	{
		child_depths = malloc(sizeof(size_t) * root->nb_children);

		if (!child_depths)
		{
			fprintf(stderr, "Memory allocation failed\n");
			return (0);
		}

		for (temp = root->children, i = 0; temp && i < root->nb_children; temp = temp->next, i++)
		{
			child_depths[i] = calculate_max_depths(temp, depth, diameter);
		}

		for (i = 0; i < root->nb_children; i++)
		{
			if (child_depths[i] > max_depth_1)
			{
				max_depth_2 = max_depth_1;
				max_depth_1 = child_depths[i];
			}
			else if (child_depths[i] > max_depth_2)
			{
				max_depth_2 = child_depths[i];
			}
		}

		free(child_depths);
	}

	update_diameter(max_depth_1, max_depth_2, depth, diameter);

	return (max_depth_1);
}



/**
 * nary_tree_diameter - program that computes the diameter of an N-ary tree
 *
 * @root: a pointer to the root node of the tree to measure
 *
 * Return: the diameter of the tree, or 0 on failure
 */

size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t diameter = 0;

	find_tree_diameter(root, 0, &diameter);

	return (diameter);
}
