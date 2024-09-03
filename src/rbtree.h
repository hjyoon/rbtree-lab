#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { RBTREE_RED, RBTREE_BLACK } color_t;

typedef int key_t;

typedef struct node_t {
  color_t color;
  key_t key;
  struct node_t *parent, *left, *right;
} node_t;

typedef struct {
  node_t *root;
  node_t *nil;  // for sentinel
} rbtree;

rbtree *new_rbtree(void);
void delete_rbtree(rbtree *);

node_t *rbtree_insert(rbtree *, const key_t);
node_t *rbtree_find(const rbtree *, const key_t);
node_t *rbtree_min(const rbtree *);
node_t *rbtree_max(const rbtree *);
int rbtree_erase(rbtree *, node_t *);

int rbtree_to_array(const rbtree *, key_t *, const size_t);

/* custom functions */
void free_recursive(rbtree*, node_t*);
void pre_order(rbtree*, node_t*);
void post_order(node_t*);
void in_order(node_t*);
int in_order_to_array(rbtree*, node_t*, key_t*, int);
void rot_left(rbtree*, node_t*);
void rot_right(rbtree*, node_t*);
void insert_restructure(rbtree*, node_t*);
void rb_transplant(rbtree*, node_t*, node_t*);
void rb_delete_fixup(rbtree*, node_t*);
node_t* tree_minimum(rbtree*, node_t*);
void rbtree_delete_check(rbtree*, node_t*);

#endif  // _RBTREE_H_
