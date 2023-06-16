#include "rb_trees.h"

/**
 * get_sibling - retrieves sibling of parent node in RBT
 *
 * @node: starting node
 * Return: pointer to sibling node, or NULL if parent or sibling missing
 */

rb_tree_t *get_sibling(rb_tree_t *node)
{
	rb_tree_t *parent = node ? node->parent : NULL;

	/* No parent or sibling means no sibling */
	if (!parent || !parent->parent)
		return (NULL);

	if (node == parent->left)
		return (parent->right);

	return (parent->left);
}

/**
 * rotate_left - rotates the tree to the left
 * The left child of the root becomes the new root,
 * preserving the BST ordering of values.
 *
 * @tree: tree to left rotate
 * Return: pointer to the new root node, or NULL if `tree` is NULL
 */
rb_tree_t *rotate_left(rb_tree_t *tree)
{
	rb_tree_t *pivot = NULL;

	if (!tree)
		return (NULL);

	/* Pivot becomes the new root */
	pivot = tree->right;

	/* Migrate children to maintain BST order */
	tree->right = pivot->left;
	if (pivot->left)
		pivot->left->parent = tree;

	/* Handle upstream connections if `tree` is a subtree */
	pivot->parent = tree->parent;
	if (tree->parent)
	{
		if (tree == tree->parent->left)
			tree->parent->left = pivot;
		else
			tree->parent->right = pivot;
	}

	/* Finally, rotate pivot into root position */
	pivot->left = tree;
	tree->parent = pivot;

	return (pivot);
}

/**
 * rotate_right - rotates the tree to the right
 * The right child of the root becomes the new root,
 * preserving the BST ordering of values.
 *
 * @tree: tree to right rotate
 * Return: pointer to the new root node, or NULL if `tree` is NULL
 */
rb_tree_t *rotate_right(rb_tree_t *tree)
{
	rb_tree_t *pivot = NULL;

	if (!tree)
		return (NULL);

	/* Pivot becomes the new root */
	pivot = tree->left;

	/* Migrate children to maintain BST order */
	tree->left = pivot->right;
	if (pivot->right)
		pivot->right->parent = tree;

	/* Handle upstream connections if `tree` is a subtree */
	pivot->parent = tree->parent;
	if (tree->parent)
	{
		if (tree == tree->parent->right)
			tree->parent->right = pivot;
		else
			tree->parent->left = pivot;
	}

	/* Finally, rotate pivot into root position */
	pivot->right = tree;
	tree->parent = pivot;

	return (pivot);
}

/**
 * insert_case4 - handles the fourth repair case for insertion into an RBT:
 * the parent is red, but the sibling (uncle) is black or missing.
 *
 * @node: newly inserted node
 * Return: pointer to the new root node, or NULL on failure
 */
rb_tree_t *insert_case4(rb_tree_t *node)
{
	rb_tree_t *parent = node ? node->parent : NULL;
	rb_tree_t *grandparent = parent ? parent->parent : NULL;
	rb_tree_t *new_root = NULL;

	if (!parent || !grandparent)
		return (NULL);
	/*
	 * Step 1: May need to rotate into parent to prepare for rotation
	 * into grandparent
	 * Ensure the inserted node is on the outside of its subtree
	 */
	/* 1A: Node is "center left" of grandparent's potential grandchildren */
	if (node == parent->right && parent == grandparent->left)
	{
		new_root = rotate_left(parent);
		node = node->left;
	}
	/* 1B: Node is "center right" of grandparent's potential grandchildren */
	else if (node == parent->left && parent == grandparent->right)
	{
		new_root = rotate_right(parent);
		node = node->right;
	}

	parent = node ? node->parent : NULL;
	grandparent = parent ? parent->parent : NULL;
	/* Step 2: Rotate into grandparent */
	if (node == parent->left)
		new_root = rotate_right(grandparent);
	else
		new_root = rotate_left(grandparent);

	while (new_root && new_root->parent)
		new_root = new_root->parent;

	parent->color = BLACK;
	grandparent->color = RED;

	return (new_root);
}

/**
 * insert_repair - traverses a RBT after insertion of a new node to
 * restore Red-Black Tree properties.
 *
 * @root: tree to repair
 * @node: newly inserted node
 * Return: pointer to the new root node, or NULL on failure
 */
rb_tree_t *insert_repair(rb_tree_t *root, rb_tree_t *node)
{
	/* New nodes are inserted in BST order and colored red by default */
	if (!node)
		return (root);

	if (node->parent == NULL)
	{
		/* Case 1: Node is the root, recolor it black */
		node->color = BLACK;
		return (node);
	}
	else if (node->parent->color == BLACK)
	{
		/*
		 * Case 2: Node's parent exists and is black, the tree is still
		 * a valid RBT
		 */
		return (root);
	}
	else if (get_sibling(node) != NULL && get_sibling(node)->color == RED)
	{
		/*
		 * Case 3: Node's parent is red, and the sibling (uncle) is red
		 */
		node->parent->color = BLACK;
		get_sibling(node)->color = BLACK;
		node->parent->parent->color = RED;
		return (insert_repair(root, node->parent->parent));
	}

	/*
	 * Case 4: Node's parent is red, and the sibling (uncle) is black
	 or missing
	*/
	return (insert_case4(node));
}

/**
 * insert_recurse - recursively traverses RBT to insert value;
 * a new node is added in BST order and colored red by default.
 *
 * @tree: tree to insert value into, or start new if NULL
 * @value: integer to insert into tree
 * Return: pointer to the new node, or NULL on failure or ignored value
 */
rb_tree_t *insert_recurse(rb_tree_t *tree, int value)
{
	rb_tree_t *new_node = NULL;

	if (tree)
	{
		if (tree->n > value)
		{
			if (tree->left == NULL)
			{
				new_node = rb_tree_node(tree, value, RED);
				tree->left = new_node;
				return (new_node);
			}

			return (insert_recurse(tree->left, value));
		}

		if (tree->n < value)
		{
			if (tree->right == NULL)
			{
				new_node = rb_tree_node(tree, value, RED);
				tree->right = new_node;
				return (new_node);
			}

			return (insert_recurse(tree->right, value));
		}

		/* tree->n == value, duplicates are ignored */
		return (NULL);
	}

	/* A new root, which will be colored black during the repair process */
	return (rb_tree_node(NULL, value, RED));
}

/**
 * rb_tree_insert - inserts a value into a Red-Black Tree
 * (redundant values are ignored).
 *
 * @tree: tree to insert value into, or start new if NULL
 * @value: integer to insert into tree
 * Return: pointer to the new node, or NULL on failure or ignored value
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new_node = NULL, *new_root = NULL;

	if (!tree)
		/* Start a new tree */
		new_node = insert_recurse(NULL, value);
	else
		/* Insert into the current tree */
		new_node = insert_recurse(*tree, value);
	if (!new_node)
		return (NULL);

	/* Repair the red-black properties of the tree after insertion */
	new_root = insert_repair(*tree, new_node);
	if (!new_root)
		return (NULL);

	*tree = new_root;

	return (new_node);
}
