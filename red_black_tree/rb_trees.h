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
void rb_insert_fixup(rb_tree_t **tree, rb_tree_t *new_node);
rb_tree_t *rb_insert_fixup_left(rb_tree_t **tree, rb_tree_t *new_node);
rb_tree_t *rb_insert_fixup_right(rb_tree_t **tree, rb_tree_t *new_node);
void rb_rotate_left(rb_tree_t **tree, rb_tree_t *x);
void rb_rotate_right(rb_tree_t **tree, rb_tree_t *y);

/* 3. Red-Black - Array to R-B Tree */
rb_tree_t *array_to_rb_tree(int *array, size_t size);

/* 4. Red-Black - Remove */
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n);
rb_tree_t *rb_tree_remove_r(rb_tree_t *root, int n, int *flag);
int remove_recurse_direction_helper(rb_tree_t *root, int n, int *flag);
rb_tree_t *rb_rebalance(rb_tree_t *root, int direction, int *flag);
void rebalance_red_siblings(
        int direction, rb_tree_t *p, rb_tree_t *s, rb_tree_t *root, int *flag);
rb_tree_t *single_rotation(rb_tree_t *root, int direction);
rb_tree_t *double_rotation(rb_tree_t *root, int direction);

#define IS_RED(node)	(node != NULL && node->color == RED)
int is_red(rb_tree_t *node);


#endif /* _RB_TREE_H_ */
