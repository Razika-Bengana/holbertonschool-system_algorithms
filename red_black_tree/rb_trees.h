#ifndef _RB_TREE_H_
#define _RB_TREE_H_

#include <stddef.h>
#include <stdlib.h>

/**
 * enum rb_color_e - Possible color of a Red-Black tree
 *
 * @RED: 0 -> Red node
 * @BLACK: 1 -> Black node
 * @DOUBLE_BLACK: 2 -> Double-black node (used for deletion)
 */
typedef enum rb_color_e
{
	RED = 0,
	BLACK,
	DOUBLE_BLACK
} rb_color_t;

/**
 * struct rb_tree_s - Red-Black tree node structure
 *
 * @n: Integer stored in the node
 * @parent: Pointer to the parent node
 * @left: Pointer to the left child node
 * @right: Pointer to the right child node
 * @color: Color of the node (RED or BLACK)
 */
typedef struct rb_tree_s
{
	int n;
	rb_color_t color;
	struct rb_tree_s *parent;
	struct rb_tree_s *left;
	struct rb_tree_s *right;
} rb_tree_t;


/* 0. Red-Black - New node */
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color);

/* 1. Red-Black - Is Red-Black */
int rb_tree_is_valid(const rb_tree_t *tree);
int is_binary_search_tree(const rb_tree_t *tree, int min, int max);
int has_valid_colors(const rb_tree_t *tree);
int calculate_height(const rb_tree_t *tree);
int check_black_height(const rb_tree_t *tree, int black_height, int height);

#define MAXIMUM(a, b) ((a) > (b) ? (a) : (b))

/* 2. Red-Black - Insert */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value);
rb_tree_t *get_sibling(rb_tree_t *node);
rb_tree_t *rotate_left(rb_tree_t *tree);
rb_tree_t *rotate_right(rb_tree_t *tree);
rb_tree_t *insert_case4(rb_tree_t *node);
rb_tree_t *insert_repair(rb_tree_t *root, rb_tree_t *node);
rb_tree_t *insert_recurse(rb_tree_t *tree, int value);

/* 3. Red-Black - Array to R-B Tree */
rb_tree_t *array_to_rb_tree(int *array, size_t size);

/* 4. Red-Black - Remove */
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n);


#endif /* _RB_TREE_H_ */
