#include "rb_trees.h"

/**
 * rb_tree_is_valid - function that checks if a binary tree is a valid
 * Red-Black Tree
 *
 * @tree: Pointer to the root node of the tree to check
 *
 * This function checks if the given binary tree satisfies the properties of a
 * Red-Black Tree:
 *   1. It is a binary search tree (BST).
 *   2. Every node has a color either red or black.
 *   3. The root of the tree is always black.
 *   4. There are no two adjacent red nodes (a red node cannot have a
 *      red parent or red child).
 *   5. Every path from the root to a NULL node has the same number of
 *      black nodes.
 *
 * Return: 1 if the tree is a valid Red-Black Tree, - 0 otherwise.
 */

int rb_tree_is_valid(const rb_tree_t *tree)
{
	if (tree == NULL)
		return (0);

	/* Check BST property */
	if (!is_bst(tree))
		return (0);

	/* Check Red-Black Tree properties */
	if (!is_red_black(tree, NULL, 0))
		return (0);

	return (1);
}

/**
 * is_bst - Helper function to check if a tree is a binary search tree (BST)
 *
 * @node: Pointer to the current node
 *
 * Return: - 1 if the tree rooted at @node is a binary search tree,
 *         - 0 otherwise.
 */

int is_bst(const rb_tree_t *node)
{
	if (node == NULL)
		return (1);

	if (node->left != NULL && node->left->n >= node->n)
		return (0);

	if (node->right != NULL && node->right->n <= node->n)
		return (0);

	if (!is_bst(node->left) || !is_bst(node->right))
		return (0);

	return (1);
}

/**
 * is_red_black - Helper function to check Red-Black Tree properties
 *
 * @node: Pointer to the current node
 * @parent: Pointer to the parent of the current node
 * @black_count: Number of black nodes from the root to the current node
 *
 * Return: - 1 if the tree rooted at @node satisfies the Red-Black Tree
 *         properties, 0 otherwise.
 */

int is_red_black(const rb_tree_t *node, const rb_tree_t *parent,
		 int black_count)
{
	if (node == NULL)
	{
		/*
		 * Check property 5:
		 * Every path from root to a NULL node has the same number
		 * of black nodes
		 */
		return (black_count == 0);
	}

	/* Check property 3: The root of the tree is always black */
	if (parent == NULL && node->color != BLACK)
		return (0);

	/* Check property 4: There are no two adjacent red nodes */
	if (parent != NULL && parent->color == RED && node->color == RED)
		return (0);

	/* Recursively check the left and right subtrees */
	return (is_red_black(node->left, node, (node->color == BLACK)
			     ? black_count + 1 : black_count) &&
		is_red_black(node->right, node, (node->color == BLACK)
			     ? black_count + 1 : black_count));
}
