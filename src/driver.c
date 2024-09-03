#include "rbtree.h"

rbtree *mock_rbtree(void);

int main(int argc, char *argv[]) {
    rbtree* t = new_rbtree();
    // key_t arr[] = {0, 9, 1, 7, 2, 5, 3, 4, 6, 8};
    key_t arr[] = {5, 17, 19, 7, 19, 19, 5, 11, 13, 7, 1, 5, 19};
    int cnt = sizeof(arr) / sizeof(arr[0]);

    for(int i=0; i<cnt; i++) {
        rbtree_insert(t, arr[i]);
    }

    for(int i=0; i<cnt; i++) {
        pre_order(t, t->root);
        node_t* del = rbtree_find(t, arr[i]);
        // printf("%p %d\n", del, del->key);
        rbtree_erase(t, del);
        // printf("\n");
    }

    // pre_order(t, t->root);

    delete_rbtree(t);


    // printf("%d\n", rbtree_min(t)->key);
    // printf("%d\n", rbtree_max(t)->key);
    // printf("%d\n", rbtree_find(t, 5)->key);

    // key_t *to_arr = (key_t*)malloc(sizeof(key_t)*10);
    // rbtree_to_array(t, to_arr, 10);

    // for(int i=0; i<10; i++) {
    //     printf("%d ", to_arr[i]);
    // }
    // printf("\n");

    // free(to_arr);

    // post_order(t->root);
    // in_order(t->root);

    /*  mock rbtree test */
    // rbtree* t = mock_rbtree();
    // pre_order(t->root);
    // printf("min: %d\n", rbtree_min(t)->key);
    // printf("max: %d\n", rbtree_max(t)->key);
    // printf("find: %d\n", rbtree_find(t, 5)->key);
    // key_t *to_arr = (key_t*)malloc(sizeof(key_t)*10);
    // rbtree_to_array(t, to_arr, 10);
    // for(int i=0; i<10; i++) {
    //     printf("%d ", to_arr[i]);
    // }
    // printf("\n");
    // free(to_arr);
    // delete_rbtree(t);
}

rbtree *mock_rbtree(void) {
    rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
    // TODO: initialize struct if needed
    node_t* node[10] = {NULL, };

    for(int i=0; i<10; i++) {
        node[i] = (node_t *)calloc(1, sizeof(node_t));
        node[i]->key = i;
    }

    p->root = node[3];

    node[0]->color = RBTREE_BLACK;
    node[0]->parent = NULL;
    node[0]->left = NULL;
    node[0]->right = NULL;

    node[1]->color = RBTREE_RED;
    node[1]->parent = node[3];
    node[1]->left = node[0];
    node[1]->right = node[2];

    node[2]->color = RBTREE_BLACK;
    node[2]->parent = node[1];
    node[2]->left = NULL;
    node[2]->right = NULL;

    node[3]->color = RBTREE_BLACK;
    node[3]->parent = NULL;
    node[3]->left = node[1];
    node[3]->right = node[7];

    node[4]->color = RBTREE_RED;
    node[4]->parent = node[6];
    node[4]->left = NULL;
    node[4]->right = NULL;

    node[5]->color = RBTREE_BLACK;
    node[5]->parent = node[7];
    node[5]->left = node[4];
    node[5]->right = node[6];

    node[6]->color = RBTREE_RED;
    node[6]->parent = node[7];
    node[6]->left = NULL;
    node[6]->right = NULL;

    node[7]->color = RBTREE_RED;
    node[7]->parent = node[3];
    node[7]->left = node[5];
    node[7]->right = node[9];

    node[8]->color = RBTREE_RED;
    node[8]->parent = node[9];
    node[8]->left = NULL;
    node[8]->right = NULL;

    node[9]->color = RBTREE_BLACK;
    node[9]->parent = node[7];
    node[9]->left = node[8];
    node[9]->right = NULL;

    return p;
}