#include "rb_trees.h"

/**
 * rb_tree_is_valid - checks if a binary tree is a valid Red-Black Tree
 * @tree: pointer to root node of the tree to check
 * Return: 1 if tree is valid, otherwise 0
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	int height;

	if (!tree)
		return (0);

	if (tree->color != BLACK)
		return (0);

	if (!is_binary_search_tree(tree, 0, 0))
		return (0);

	if (!has_valid_colors(tree))
		return (0);

	height = calculate_height(tree);

	if (!check_black_height(tree, height, 0))
		return (0);

	return (1);
}

/**
 * is_binary_search_tree - checks if tree is a valid Binary Search Tree
 * @tree: binary tree
 * @min: min value in the left subtree
 * @max: max value in the right subtree
 * Return: 1 if valid BST, otherwise 0
 */
int is_binary_search_tree(const rb_tree_t *tree, int min, int max)
{
	if (!tree)
		return (1);

	if ((min && tree->n < min) || (max && tree->n > max))
		return (0);

	return (is_binary_search_tree(tree->left, 0, tree->n) &&
		is_binary_search_tree(tree->right, tree->n, 0));
}

/**
 * has_valid_colors - checks if RBT has valid colors
 * @tree: binary tree
 * Return: 1 if colors are valid, otherwise 0
 */
int has_valid_colors(const rb_tree_t *tree)
{
	if (!tree)
		return (1);

	if (tree->color != RED && tree->color != BLACK)
		return (0);

	if (tree->color == RED)
	{
		if (tree->left && tree->left->color == RED)
			return (0);
		if (tree->right && tree->right->color == RED)
			return (0);
	}

	return (has_valid_colors(tree->left) && has_valid_colors(tree->right));
}

/**
 * calculate_height - gets height of red-black tree
 * @tree: binary tree
 * Return: maximum number of black nodes between root and leaf
 */
int calculate_height(const rb_tree_t *tree)
{
	int height;

	if (!tree)
		return (0);

	height = MAXIMUM(calculate_height(tree->left), calculate_height(tree->right));

	if (tree->color == BLACK)
		height++;

	return (height);
}

/**
 * check_black_height - checks if the height of black nodes in RBT is valid
 * @tree: tree to check
 * @black_height: number of black nodes
 * @height: current height
 * Return: 1 if height is valid, otherwise 0
 */
int check_black_height(const rb_tree_t *tree, int black_height, int height)
{
	if (!tree)
	{
		if (height == black_height)
			return (1);
		return (0);
	}

	if (tree->color == BLACK)
		height++;

	return (check_black_height(tree->left, black_height, height) &&
		check_black_height(tree->right, black_height, height));
}
