#include "rb_trees.h"

/**
 * rb_tree_remove - Removes a node from a Red-Black Tree
 *
 * @root: Pointer to the root node of the tree
 * @n: Value to search for and remove from the tree
 *
 * Return: Pointer to the new root of the tree after deletion
 */

rb_tree_t *rb_tree_remove(rb_tree_t *root, int n)
{
	rb_tree_t *remove = root;

	while (remove && remove->n != n)
	{
		if (remove->n > n)
			remove = remove->left;
		else
			remove = remove->right;
	}
	return (rb_tree_delete(root, remove));
}

/**
 * rb_tree_delete - Deletes a node from the Red-Black Tree
 *
 * @root: Pointer to the root node of the tree
 * @remove: Node to remove from the tree
 *
 * Return: Pointer to the new root of the tree after deletion
 */

rb_tree_t *rb_tree_delete(rb_tree_t *root, rb_tree_t *remove)
{
	rb_tree_t *x = NULL;
	rb_tree_t *y = remove;
	rb_color_t original_color = remove->color;

	if (remove->left == NULL)
	{
		x = remove->right;
		rb_transplant(&root, remove, remove->right);
	}
	else if (remove->right == NULL)
	{
		x = remove->left;
		rb_transplant(&root, remove, remove->left);
	}
	else
	{
		y = tree_min(remove->right);
		if (y->color)
			original_color = y->color;
		x = y->right;
		if (y->parent && y->parent == remove)
			x->parent = y;
		else
		{
			rb_transplant(&root, y, y->right);
			y->right = remove->right;
			y->right->parent = y;
		}
		rb_transplant(&root, remove, y);
		y->left = remove->left;
		y->left->parent = y;
		y->color = remove->color;
	}
	if (original_color == BLACK)
		rb_delete_fixup(&root, x);
	return (root);
}

/**
 * rb_transplant - Replaces one subtree as a child of its parent
 * with another subtree
 *
 * @root: Pointer to the root node of the tree
 * @x: Root of the subtree to replace
 * @y: Subtree to replace with
 */

void rb_transplant(rb_tree_t **root, rb_tree_t *x, rb_tree_t *y)
{
	if (x->parent == NULL)
		*root = y;
	else if (x->parent->left && x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	if (y)
		y->parent = x->parent;
}

/**
 * rb_delete_fixup - Restores the Red-Black tree properties after deletion
 *
 * @root: Pointer to the root node of the tree
 * @x: Node to fix
 *
 * Return: Pointer to the new root of the tree
 */

rb_tree_t *rb_delete_fixup(rb_tree_t **root, rb_tree_t *x)
{
	while (x != NULL && x->color == BLACK)
	{
		if (x == x->parent->left)
			x = rb_delete_fix_right(root, x);
		else
			x = rb_delete_fix_left(root, x);
	}
	if (x)
		x->color = BLACK;
	return (*root);
}

/**
 * rb_delete_fix_left - Fixes the left sibling after deletion
 *
 * @root: Pointer to the root node of the tree
 * @x: Node to fix
 *
 * Return: Pointer to the updated node
 */
rb_tree_t *rb_delete_fix_left(rb_tree_t **root, rb_tree_t *x)
{
	rb_tree_t *y;

	y = x->parent->left;
	/* CASE 1 */
	if (y && y->color == RED)
	{
		y->color = BLACK;
		x->parent->color = RED;
		rb_rotate_right(root, x->parent);
		y = x->parent->left;
	}
	/* CASE 2 */
	if (y && y->right->color == BLACK && y->left->color == BLACK)
	{
		y->color = RED;
		x = x->parent;
	}
	/* CASE 3 */
	else if (y && y->left->color == BLACK)
	{
		y->right->color = BLACK;
		y->color = RED;
		rb_rotate_left(root, y);
		y = x->parent->left;
	}
	/* CASE 4 */
	y->color = x->parent->color;
	x->parent->color = BLACK;
	y->right->color = BLACK;
	rb_rotate_right(root, x->parent);
	x = *root;

	return (x);
}

/**
 * rb_delete_fix_right - Fixes the right sibling after deletion
 *
 * @root: Pointer to the root node of the tree
 * @x: Node to fix
 *
 * Return: Pointer to the new root of the tree
 */

rb_tree_t *rb_delete_fix_right(rb_tree_t **root, rb_tree_t *x)
{
	rb_tree_t *y = NULL;

	y = x->parent->right;
	/* CASE 1 */
	if (y && y->color == RED)
	{
		y->color = BLACK;
		x->parent->color = RED;
		rb_rotate_left(root, x->parent);
		y = x->parent->right;
	}
	/* CASE 2 */
	if (y && y->left->color == BLACK && y->right->color == BLACK)
	{
		y->color = RED;
		x = x->parent;
	}
	/* CASE 3 */
	else if (y && y->right->color == BLACK)
	{
		y->left->color = BLACK;
		y->color = RED;
		rb_rotate_right(root, y);
		y = x->parent->right;
	}
	/* CASE 4 */
	y->color = x->parent->color;
	x->parent->color = BLACK;
	y->right->color = BLACK;
	rb_rotate_left(root, x->parent);
	x = *root;

	return (x);
}

/**
 * tree_min - Finds the minimum value in a Red-Black Tree
 *
 * @root: Pointer to the root node of the tree
 *
 * Return: Node with the minimum value
 */

rb_tree_t *tree_min(rb_tree_t *root)
{
	while (root->left)
		root = root->left;
	return (root);
}
