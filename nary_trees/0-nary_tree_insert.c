#include "nary_trees.h"

/**
 * create_node - program that allocates memory and creates a new
 * 'N-ary tree' node with the specified string content
 *
 * this function performs the following steps:
 *
 * 1. allocates memory for a new nary_tree_t node
 * 2. duplicates the input string and assigns it to the node's content
 * 3. initializes the parent, children, and next pointers to NULL, and
 *    sets the number of children to 0
 *
 * if memory allocation for the node or the string duplication fails,
 * the function cleans up any allocated memory and returns NULL
 *
 * @str: the string content to be stored in the new node;
 *       the function duplicates this string for the node's content
 *
 * Return: a pointer to the newly created nary_tree_t node if successful,
 *         or NULL if an error occurs during node creation or string
 *         duplication
 */

nary_tree_t *create_node(char const *str)
{
	nary_tree_t *node = malloc(sizeof(nary_tree_t));

	if (!node)
		return (NULL);

	node->content = strdup(str);

	if (!node->content)
	{
		free(node);
		return (NULL);
	}
	node->parent = NULL;
	node->nb_children = 0;
	node->children = NULL;
	node->next = NULL;

	return (node);
}



/**
 * insert_at_beginning - program that inserts a node at the beginning
 * of the children list of a specified parent node in an 'N-ary tree'
 *
 * this function updates the parent node's children list by performing
 * the following steps:
 *
 * 1. if the parent already has children, sets the new node's next pointer
 *    to point to the current first child of the parent
 * 2. updates the parent's children pointer to point to the new node,
 *    effectively inserting it at the beginning of the list
 * 3. increments the parent's children count
 * 4. sets the new node's parent pointer to the specified parent node
 *
 * @parent: the parent node under which the new node will be added;
 *          this node's children list is updated
 * @node: the new node to be inserted as the first child of the specified
 *        parent node
 *
 * Return: nothing (void)
 */

void insert_at_beginning(nary_tree_t *parent, nary_tree_t *node)
{
	if (parent->children)
	{
		node->next = parent->children;
	}
	parent->children = node;
	parent->nb_children++;
	node->parent = parent;
}



/**
 * nary_tree_insert - program that creates a new 'N-ary tree' node
 * with specified string content and inserts it under a given parent node
 *
 * this function combines the creation of a new node and its insertion
 * into the tree by:
 *
 * 1. creating a new node with the specified string content using create_node()
 * 2. if a parent is specified, inserting the new node as the first child of
 *    the parent using insert_at_beginning()
 *
 * @parent: the parent node under which to insert the new node;
 *          if NULL, the new node remains unattached
 * @str: the string content for the new node;
 *       this string is duplicated and stored in the new node
 *
 * Return: a pointer to the newly created node if successful,
 *         or NULL if the node creation fails
 */

nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *new_node = create_node(str);

	if (!new_node)
		return (NULL);

	if (parent)
	{
		insert_at_beginning(parent, new_node);
	}
	return (new_node);
}