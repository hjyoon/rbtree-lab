#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct bt_t {
    int size;
    struct node_t* root;
} bt_t;

typedef struct node_t {
    int data;
    struct node_t* parent_link;
    struct node_t* left_link;
    struct node_t* right_link;
} node_t;


bt_t create_bt() {
    bt_t bt = {0, NULL};
    // node_t* node = (node_t*)malloc(sizeof(node_t));
    // node->data = -1;
    // node->parent_link = NULL;
    // node->left_link = NULL;
    // node->right_link = NULL;

    // bt.size = 0;
    // bt.root = node;
    
    return bt;
}

void push(int data, bt_t* bt) {
    node_t* node = (node_t*)malloc(sizeof(node_t));
    node->data = data;
    node->parent_link = NULL;
    node->left_link = NULL;
    node->right_link = NULL;

    if(bt->size == 0) {
        bt->root = node;
    } else {
        node_t* now = bt->root;
        node_t* prev_node = NULL;
        while(now) {
            prev_node = now;
            if(now->data < data) {
                now = now->right_link;
                if(now == NULL) {
                    prev_node->right_link = node;
                }
            } else {
                now = now->left_link;
                if(now == NULL) {
                    prev_node->left_link = node;
                }
            }
        }
        node->parent_link = prev_node;
    }
    bt->size++;
}

void pre_order(node_t* root) {
    if(root != NULL) {
        printf("%d\n", root->data);
        pre_order(root->left_link);
        pre_order(root->right_link);
    }
}

void post_order(node_t* root) {
    if(root != NULL) {
        post_order(root->left_link);
        post_order(root->right_link);
        printf("%d\n", root->data);
    }
}

void in_order(node_t* root) {
    if(root != NULL) {
        in_order(root->left_link);
        printf("%d\n", root->data);
        in_order(root->right_link);
    }
}

void destroy(node_t* root) {
    if(root != NULL) {
        destroy(root->left_link);
        destroy(root->right_link);
        printf("%d\n", root->data);
        free(root);
    }
}

int main(void) {
    bt_t bt = create_bt();

    push(50, &bt);
    push(30, &bt);
    push(60, &bt);
    push(40, &bt);
    push(20, &bt);

    printf("pre order:\n");
    pre_order(bt.root);

    printf("post order:\n");
    post_order(bt.root);

    printf("in order:\n");
    in_order(bt.root);

    printf("free:\n");
    destroy(bt.root);

    return 0;
}