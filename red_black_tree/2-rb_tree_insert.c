#include "rb_trees.h"

/**
 * rb_tree_insert - inserts a value in a Red-Black Tree
 *
 * @tree: double pointer to the root node of the Red-Black tree
 * to insert the value in
 * @value: the value to store in the node to be inserted
 *
 * Return: pointer to the created node, or NULL on failure
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *current = NULL;
	rb_tree_t *parent = NULL;
	rb_tree_t *new_node = NULL;

	if (!tree)
		return (NULL);

	current = *tree;
	while (current != NULL)
	{
		parent = current;
		if (current->n == value)
			return (NULL);
		if (value < current->n)
			current = current->left;
		else if (value > current->n)
			current = current->right;
	}
	new_node = rb_tree_node(parent, value, RED);
	if (!new_node)
		return (NULL);

	if (parent == NULL)
		*tree = new_node;
	else if (new_node->n < parent->n)
		parent->left = new_node;
	else
		parent->right = new_node;
	rb_insert_fixup(tree, new_node);
	return (new_node);
}

/**
 * rb_insert_fixup - rotates nodes and recolors to fix the violation
 *
 * @tree: double pointer to the root node
 * @new_node: the new node to fix
 */
void rb_insert_fixup(rb_tree_t **tree, rb_tree_t *new_node)
{
	while (new_node->parent && new_node->parent->color == RED)
	{
		if (new_node->parent->parent && new_node->parent ==
		    new_node->parent->parent->left)
			new_node = rb_insert_right(tree, new_node);
		else
			new_node = rb_insert_left(tree, new_node);
	}
	(*tree)->color = BLACK;
}

/**
 * rb_insert_left - fixes when p->p->left
 *
 * @tree: root node
 * @new_node: node to be fixed
 *
 * Return: pointer to the new node
 */
rb_tree_t *rb_insert_left(rb_tree_t **tree, rb_tree_t *new_node)
{
	rb_tree_t *uncle = NULL;

	uncle = new_node->parent->parent->left;
	if (uncle && uncle->color == RED)
	{
		new_node->parent->color = BLACK;
		uncle->color = BLACK;
		new_node->parent->parent->color = RED;
		new_node = new_node->parent->parent;
	}
	else
	{
		if (new_node == new_node->parent->left)
		{
			new_node = new_node->parent;
			rb_rotate_right(tree, new_node);
		}
		new_node->parent->color = BLACK;
		new_node->parent->parent->color = RED;
		rb_rotate_left(tree, new_node->parent->parent);
	}
	return (new_node);
}

/**
 * rb_insert_right - fixes when p->p->right
 *
 * @tree: root node
 * @new_node: node to be fixed
 *
 * Return: pointer to the new node
 */
rb_tree_t *rb_insert_right(rb_tree_t **tree, rb_tree_t *new_node)
{
	rb_tree_t *uncle = NULL;

	uncle = new_node->parent->parent->right;
	if (uncle && uncle->color == RED)
	{
		new_node->parent->color = BLACK;
		uncle->color = BLACK;
		new_node->parent->parent->color = RED;
		new_node = new_node->parent->parent;
	}
	else
	{
		if (new_node == new_node->parent->right)
		{
			new_node = new_node->parent;
			rb_rotate_left(tree, new_node);
		}
		new_node->parent->color = BLACK;
		new_node->parent->parent->color = RED;
		rb_rotate_right(tree, new_node->parent->parent);
	}
	return (new_node);
}

/**
 * rb_rotate_left - rotates the subtree to the left
 *
 * @tree: root node
 * @x: node to rotate
 */
void rb_rotate_left(rb_tree_t **tree, rb_tree_t *x)
{
	rb_tree_t *y = NULL;

	y = x->right;
	x->right = y->left;
	if (y->left)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == NULL)
		*tree = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

/**
 * rb_rotate_right - rotates the subtree to the right
 *
 * @tree: root node
 * @y: node to rotate
 */
void rb_rotate_right(rb_tree_t **tree, rb_tree_t *y)
{
	rb_tree_t *x = NULL;

	x = y->left;
	y->left = x->right;
	if (x->right)
		x->right->parent = y;
	x->parent = y->parent;
	if (y->parent == NULL)
		*tree = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;
	x->right = y;
	y->parent = x;
}
