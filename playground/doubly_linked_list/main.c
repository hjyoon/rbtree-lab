#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct ll_t {
    int size;
    struct node_t* tail;
    struct node_t* head;
} ll_t;

typedef struct node_t {
    char* data;
    struct node_t* prev_link;
    struct node_t* next_link;
} node_t;


ll_t create_ll() {
    ll_t ll;
    node_t* node = (node_t*)malloc(sizeof(node_t));
    node->data = "dummy";
    node->prev_link = NULL;
    node->next_link = NULL;

    ll.size = 0;
    ll.head = node;
    ll.tail = node;
    
    return ll;
}

void push_back(char* data, ll_t* ll) {
    node_t* node = (node_t*)malloc(sizeof(node_t));
    node->data = data;
    node->prev_link = ll->tail;
    node->next_link = NULL;

    ll->tail->next_link = node;
    ll->tail = node;
    ll->size++;
}

void push_front(char* data, ll_t* ll) {
    node_t* node = (node_t*)malloc(sizeof(node_t));
    node->data = data;
    node->prev_link = ll->head;
    node->next_link = ll->head->next_link;

    ll->head->next_link = node;
    ll->size++;
}

node_t pop(ll_t* ll) {
    if (ll->size == 0) {
        exit(-1);
    }
    // node_t* now = ll->head;
    // for(int i=0; i<ll->size-1; i++) {
    //     now = now->plink;
    // }

    // printf("%p\n", ll->tail);
    node_t ret = *(ll->tail);

    ll->tail = ll->tail->prev_link;
    free(ll->tail->next_link);
    ll->tail->next_link = NULL;

    ll->size--;
    return ret;
}

node_t pop_front(ll_t* ll) {
    if (ll->size == 0) {
        exit(-1);
    }
    // node_t* now = ll->head;
    // for(int i=0; i<ll->size-1; i++) {
    //     now = now->plink;
    // }

    // printf("%p\n", ll->tail);
    node_t ret = *(ll->head->next_link);

    ll->head->next_link = ll->head->next_link->next_link;
    free(ll->head->next_link->prev_link);
    ll->head->next_link->prev_link = ll->head;

    ll->size--;
    return ret;
}

void iter(ll_t* ll) {
    node_t* now = ll->head->next_link;
    while(now) {
        printf("%s\n", now->data);
        now = now->next_link;
    }
}

void iter_reverse(ll_t* ll) {
    node_t* now = ll->tail;
    for(int i=0; i<ll->size; i++) {
        printf("%s\n", now->data);
        now = now->prev_link;
    }
    // while(now) {
    //     printf("%s\n", now->data);
    //     now = now->prev_link;
    // }
}

node_t* fromIndex(int idx, ll_t* ll) {
    node_t* now = ll->head->next_link;
    for(int i=0; i<idx; i++) {
        now = now->next_link;
    }
    return now;
}

int main(void) {
    ll_t ll = create_ll();

    push_back("one", &ll);
    push_back("two", &ll);
    push_back("three", &ll);
    push_back("four", &ll);

    push_front("zero", &ll);

    printf("%s\n", pop_front(&ll).data);
    // printf("%s\n", pop_front(&ll).data);
    // printf("%s\n", pop_front(&ll).data);
    // printf("%s\n", pop_front(&ll).data);

    // node_t* node = fromIndex(3, &ll);

    // printf("%s\n", node->data);

    iter(&ll);
    iter_reverse(&ll);

    // printf("%s\n", fromIndex(2, &ll)->data);

    // printf("%s\n", pop(&ll).data);
    // printf("%s\n", pop(&ll).data);
    // printf("%s\n", pop(&ll).data);
    // printf("%s\n", pop(&ll).data);
    // // // printf("%s\n", pop(&ll).data);

    // push_back("five", &ll);
    // push_back("six", &ll);

    // push_back("one", &ll);
    // push_back("two", &ll);

    // iter(&ll);

    return 0;
}