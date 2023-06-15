#include "rb_trees.h"

/**
 * rb_tree_node - function that creates a Red-Black Tree node
 * @parent: Pointer to the parent node of the node to create
 * @value: The value to put in the new node
 * @color: The color of the node
 *
 * This function creates a new Red-Black Tree node with the specified @value
 * and @color. The @parent parameter is a pointer to the parent node of the
 * node to be created. The @parent pointer can be NULL if the node is to be
 * inserted as the root of the tree.
 *
 * Return: On success, a pointer to the newly created node. On failure, NULL.
 */

rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *node = malloc(sizeof(rb_tree_t));

	if (node == NULL)
		return (NULL);

	node->n = value;
	node->color = color;
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;

	return (node);
}
