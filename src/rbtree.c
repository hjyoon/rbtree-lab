#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t *sentinel = (node_t *)calloc(1, sizeof(node_t));
  sentinel->color = RBTREE_BLACK;
  sentinel->parent = sentinel;
  sentinel->left = sentinel;
  sentinel->right = sentinel;

  p->nil = sentinel;
  p->root = sentinel;

  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free_recursive(t, t->root);
  free(t->nil);
  free(t);
}

node_t* rbtree_insert(rbtree* t, const key_t key) {
  // TODO: implement insert
  node_t* n = (node_t*)calloc(1, sizeof(node_t));
  n->key = key;
  n->parent = t->nil;
  n->left = t->nil;
  n->right = t->nil;
  if(t->root == t->nil) {
    n->color = RBTREE_BLACK;
    t->root = n;
  } else {
    node_t* now = t->root;
    node_t* prev = t->nil;
    while(now != t->nil) {
      prev = now;
      if(now->key < key) {
        now = now->right;
        if(now == t->nil) {
          prev->right = n;
        }
      } else {
        now = now->left;
        if(now == t->nil) {
          prev->left = n;
        }
      }
    }
    n->color = RBTREE_RED;
    n->parent = prev;
  }
  insert_restructure(t, n);
  return n;
}

node_t* rbtree_find(const rbtree* t, const key_t key) {
  // TODO: implement find
  node_t* now = t->root;
  while(now != t->nil) {
    if(now->key == key) {
      return now;
    }
    now = now->key >= key ? now->left : now->right;
  }
  return NULL;
}

node_t* rbtree_min(const rbtree* t) {
  // TODO: implement find
  node_t* now = t->root;
  node_t* prev = NULL;
  while(now != t->nil) {
    prev = now;
    now = now->left ? now->left : now->right;
  }
  return prev;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  node_t *now = t->root;
  node_t *prev = NULL;
  while(now != t->nil) {
    prev = now;
    now = now->right ? now->right : now->left;
  }
  return prev;
}

int rbtree_erase(rbtree* t, node_t* p) {
  // TODO: implement erase
  node_t* y = p;
  node_t* x = t->nil;
  int original = y->color;
  if (p->left == t->nil) {
    x = p->right;
    rb_transplant(t, p, p->right);
  } else if (p->right == t->nil) {
    x = p->left;
    rb_transplant(t, p, p->left);
  } else {
    y = tree_minimum(t, p->right);
    original = y->color;
    x = y->right;
    // if (x == t->nil) {
    //   x->parent = y->parent;
    // }

    if (y->parent == p) {
      x->parent = y;
    } else {
      rb_transplant(t, y, y->right);
      y->right = p->right;
      y->right->parent = y;
    }

    rb_transplant(t, p, y);
    y->left = p->left;
    y->left->parent = y;
    y->color = p->color;
  }
  if (original == RBTREE_BLACK) {
    rb_delete_fixup(t, x);
  } else {
    // printf("no need fixup\n");
  }
  t->nil->parent = t->nil;
  free(p);

  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  in_order_to_array(t, t->root, arr, 0);
  return 0;
}

/* custom function */
void free_recursive(rbtree* t, node_t* n) {
  if(n != t->nil) {
    free_recursive(t, n->left);
    free_recursive(t, n->right);
    free(n);
  }
}

/* custom function */
void pre_order(rbtree* t, node_t* root) {
  if(root != t->nil) {
    // printf("%d %s\n", root->key, root->color == 0 ? "red" : "black");
    pre_order(t, root->left);
    pre_order(t, root->right);
  } else {
    // printf("NIL\n");
  }
}

/* custom function */
void post_order(node_t* root) {
  if(root != NULL) {
    post_order(root->left);
    post_order(root->right);
    // printf("%d %s\n", root->key, root->color == 0 ? "red" : "black");
  }
}

/* custom function */
void in_order(node_t* root) {
  if(root != NULL) {
    in_order(root->left);
    // printf("%d %s\n", root->key, root->color == 0 ? "red" : "black");
    in_order(root->right);
  }
}

/* custom function */
int in_order_to_array(rbtree* t, node_t* root, key_t *arr, int i) {
  if(root != t->nil) {
    i = in_order_to_array(t, root->left, arr, i);
    arr[i++] = root->key;
    i = in_order_to_array(t, root->right, arr, i);
  }
  return i;
}

/* custom function */
void rot_left(rbtree* t, node_t* n) {
  if (n == t->nil) return;

  node_t* tmp = n->right;
  if (tmp == t->nil) return;

  n->right = tmp->left;
  if (tmp->left != t->nil) {
    tmp->left->parent = n;
  }
  tmp->parent = n->parent;
  if (n->parent == t->nil) {
    t->root = tmp;
  } else if (n == n->parent->left) {
    n->parent->left = tmp;
  } else {
    n->parent->right = tmp;
  }
  tmp->left = n;
  n->parent = tmp;
}

/* custom function */
void rot_right(rbtree* t, node_t* n) {
  if (n == t->nil) return;

  node_t* tmp = n->left;
  if (tmp == t->nil) return;

  n->left = tmp->right;
  if (tmp->right != t->nil) {
    tmp->right->parent = n;
  }
  tmp->parent = n->parent;
  if (n->parent == t->nil) {
    t->root = tmp;
  } else if (n == n->parent->right) {
    n->parent->right = tmp;
  } else {
    n->parent->left = tmp;
  }
  tmp->right = n;
  n->parent = tmp;
}

/* custom function */
// void insert_restructure(rbtree* t, node_t* n) {
//   if (n->parent == NULL) {
//     n->color = RBTREE_BLACK;
//     return;
//   }

//   while (n->parent && n->parent->color == RBTREE_RED) {
//     node_t* p = n->parent;
//     node_t* g = p->parent;

//     if (!g) break;

//     if (p == g->left) { // 왼쪽으로 1자로 뻗은 형태
//       node_t* u = g->right;
//       if (u && u->color == RBTREE_RED) {
//         p->color = RBTREE_BLACK;
//         u->color = RBTREE_BLACK;
//         g->color = RBTREE_RED;
//         n = g;
//         p = n->parent;
//         g = p->parent;
//       } else {
//         if (n == p->right) {
//           rot_left(t, p);
//           n = p;
//           p = n->parent;
//           g = p->parent;
//         }
//         p->color = RBTREE_BLACK;
//         g->color = RBTREE_RED;
//         rot_right(t, g);
//       }
//     } else { // 오른쪽으로 1자로 뻗은 형태
//       node_t* u = g->left;
//       if (u && u->color == RBTREE_RED) {
//         p->color = RBTREE_BLACK;
//         u->color = RBTREE_BLACK;
//         g->color = RBTREE_RED;
//         n = g;
//         p = n->parent;
//         g = p->parent;
//       } else {
//         if (n == p->left) {
//           rot_right(t, p);
//           n = p;
//           p = n->parent;
//           g = p->parent;
//         }`
//         p->color = RBTREE_BLACK;
//         g->color = RBTREE_RED;
//         rot_left(t, g);
//       }
//     }
//   }
//   t->root->color = RBTREE_BLACK;
// }

/* custom function */
void insert_restructure(rbtree* t, node_t* n) {
  node_t *p, *g, *u;
  while (n->parent && n->parent->parent && n->parent->color == RBTREE_RED) { // 부모 노드와 조부모 노드가 모두 존재할 때만 반복
    p = n->parent;
    g = p->parent;
    u = (p == g->left) ? g->right : g->left;

    if (u && u->color == RBTREE_RED) {
      p->color = RBTREE_BLACK;
      u->color = RBTREE_BLACK;
      g->color = RBTREE_RED;
      n = g;  // 현재 노드를 조부모 노드로 설정하여 계속 진행
    } else {
      if (p == g->left && n == p->right) { // 왼쪽, 오른쪽 꺾인 경우
        rot_left(t, p);
        n = p;
        p = n->parent;
      } else if (p == g->right && n == p->left) { // 오른쪽, 왼쪽 꺾인 경우
        rot_right(t, p);
        n = p;
        p = n->parent;
      }

      p->color = RBTREE_BLACK;
      g->color = RBTREE_RED;
      if (n == p->left) { // 왼쪽으로 일자인 경우
        rot_right(t, g);
      } else { // 오른쪽으로 일자인 경우
        rot_left(t, g);
      }
      
      break;
    }
  }
  t->root->color = RBTREE_BLACK;  // 루트는 항상 검은색
}

/* custom function */
void rb_transplant(rbtree *t, node_t *u, node_t *v) {
  if (u->parent == t->nil) {
    t->root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

/* custom function */
// void rb_delete_fixup(rbtree* t, node_t* x) {
//   // 경우의 수를 살펴보면
//   // case 1 -> case2-> case4
//   // case 1 -> case3-> case4
//   // case 1 -> case4
//   // case 4
//   // case 2
//   // case 3 -> case 4
//   while (x != t->root && (!x || x->color == RBTREE_BLACK)) {
//     if (!x) break;
    
//     if (x == x->parent->left) {
//       node_t* sibling = x->parent->right;
//       // 더블리 블랙의 형제가 red인경우
//       //  해결법 부모를 기준으로 회전 근데 회전 전에 부모와 형제의 색깔을 바꿔줌
//       if (sibling->color == RBTREE_RED) {
//         // case 1
//         sibling->color = RBTREE_BLACK;
//         x->parent->color = RBTREE_RED;
//         rot_left(t, x->parent);
//         sibling = x->parent->right;
//         // 이렇게 돌리고 나면 case 2,3,4를 체크해봐야 하므로 case1이 가장 상위단에 있어야함
//         // 모든 케이스를 다 돌리고 나서 확인을 할 수 있기 때문.
//       }
//       // 형제의 두 자녀가 모두 black인지를 체크해야함
//       if (sibling->left->color == RBTREE_BLACK && sibling->right->color == RBTREE_BLACK) {
//         // case 2
//         // 형제의 색깔을 레드로 바꿔 준 이후 부모에게 전달해야함
//         // 그리고서 부모에게 블랙에 대한 책임을 전가하고 비교 대상을 부모로 옮겨서
//         // 부모가 처리할 수 있도록 해야함
//         // 레드앤블랙인 경우 그냥 색깔만 바꾸고
//         // 더블리 블랙일때는 다시 그 노드가 루트냐 아니냐로 따지고
//         // 루트인 경우 블랙으로 변경,
//         // 루트가 아닌 경우 case1,2,3,4를 다시 적용
//         // 다시 적용해야하기에 while문을 통해서 다시 돌아가게끔 만듦
//         sibling->color = RBTREE_RED;
//         x = x->parent;
//       } else {
//         // 오른쪽 형제가 black이고,
//         //  그 형제의 왼쪽 자녀가 레드 이 조건은 위에 if문에서 해결이 될 것임
//         //  그리고 오른쪽 자녀가 블랙인 경우
//         if (sibling->right->color == RBTREE_BLACK) {
//           // case3
//           // 왼쪽 자식은 검은색으로 변경, 오른쪽은 더블리 블랙이 될 것임
//           sibling->left->color = RBTREE_BLACK;
//           // 형제의 색깔은 색깔을 내려준것이니까 레드로 바뀌게 됨
//           sibling->color = RBTREE_RED;
//           // 이후 형제를 기준으로 오른쪽으로 회전시키게 됨
//           rot_right(t, sibling);
//           // 형제는 다시 형제로 맞춰줘야하기 때문에 x의 형제의 오른쪽으로 진행하면 자기 자신이 나오게 됨
//           sibling = x->parent->right;
//           // 이후 케이스 4번을 적용해서 이 문제를 해결하면 됨
//         }
//         // case 4
//         // 형제의 색깔을 부모의 색깔로 바꿔줌
//         sibling->color = x->parent->color;
//         // 부모의 색깔은 블랙으로 변경해줌
//         x->parent->color = RBTREE_BLACK;
//         // 형제의 오른쪽 자식을 검은색으로 변경해줘야함
//         // 의문? 강의에서는 부모와 형제의 색깔을 변경하고 돌렸는데 여기는 그렇게 하지 않음
//         // 아마 결과론적으로 접근한게 코드가 더 짧아지기 때문에 그런 것 같음
//         sibling->right->color = RBTREE_BLACK;
//         // 이후 왼쪽으로 돌리고
//         rot_left(t, x->parent);
//         // x의 값을 루트로 만들어서 while문을 끝마치게 됨
//         x = t->root;
//       }
//     } else {
//       // 이 밑으로는 위에서 얘기한 것의 반대로 진행하면 됨
//       node_t* sibling = x->parent->left;
//       if (sibling->color == RBTREE_RED) {
//         sibling->color = RBTREE_BLACK;
//         x->parent->color = RBTREE_RED;
//         rot_right(t, x->parent);
//         sibling = x->parent->left;
//       }
//       if (sibling->right->color == RBTREE_BLACK && sibling->left->color == RBTREE_BLACK) {
//         sibling->color = RBTREE_RED;
//         x = x->parent;
//       } else {
//         if (sibling->left->color == RBTREE_BLACK) {
//           sibling->right->color = RBTREE_BLACK;
//           sibling->color = RBTREE_RED;
//           rot_left(t, sibling);
//           sibling = x->parent->left;
//         }
//         sibling->color = x->parent->color;
//         x->parent->color = RBTREE_BLACK;
//         sibling->left->color = RBTREE_BLACK;
//         rot_right(t, x->parent);
//         x = t->root;
//       }
//     }
//   }
//   if (x != NULL) {
//     x->color = RBTREE_BLACK;
//   }
// }

void rb_delete_fixup(rbtree* t, node_t* x) {
  // printf("start fixup\n");
  if (!x) {
    // printf("x is NULL\n");
  } else {
    // printf("x: %d\n", x->key);
  }

  while (x != t->root && x->color == RBTREE_BLACK) {
    node_t* sibling;
    int is_left = (x == x->parent->left);
    // printf("%d %d\n", x->parent->right->key, x->parent->parent->key);

    sibling = is_left ? x->parent->right : x->parent->left;
    // printf("%d\n", sibling->key);
    if (!sibling) {
      // printf("no sibling... continue\n");
      continue;  // 형제 노드가 없으면 다음 반복으로
    }

    if (sibling->color == RBTREE_RED) {
      // printf("do case 1\n");
      // case 1
      // 형제 노드가 레드인 경우, 부모와 형제의 색을 바꾸고 회전
      sibling->color = RBTREE_BLACK;
      x->parent->color = RBTREE_RED;
      if (is_left) {
        rot_left(t, x->parent);
        sibling = x->parent->right;
      } else {
        rot_right(t, x->parent);
        sibling = x->parent->left;
      }
    }

    if ((sibling->left && sibling->left->color == RBTREE_BLACK) &&
        (sibling->right && sibling->right->color == RBTREE_BLACK)) {
      // printf("do case 2\n");
      // case 2
      // 형제와 형제의 자식들이 모두 블랙인 경우
      sibling->color = RBTREE_RED;
      // printf("sibling->key: %d\n", sibling->key, sibling->color);
      x = x->parent;
    } else {
      // printf("do case 3\n");
      // case 3
      // 형제 노드의 적어도 하나의 자식이 레드
      if (is_left && (!sibling->right || sibling->right->color == RBTREE_BLACK)) {
        if (sibling->left) {
          sibling->left->color = RBTREE_BLACK;
        }
        sibling->color = RBTREE_RED;
        rot_right(t, sibling);
        sibling = x->parent->right;
      } else if (!is_left && (!sibling->left || sibling->left->color == RBTREE_BLACK)) {
        if (sibling->right) {
          sibling->right->color = RBTREE_BLACK;
        }
        sibling->color = RBTREE_RED;
        rot_left(t, sibling);
        sibling = x->parent->left;
      }

      // printf("do case 4\n");
      // case 4
      sibling->color = x->parent->color;
      x->parent->color = RBTREE_BLACK;
      if (is_left) {
        if (sibling->right) {
          sibling->right->color = RBTREE_BLACK;
        }
        rot_left(t, x->parent);
      } else {
        if (sibling->left) {
          sibling->left->color = RBTREE_BLACK;
        }
        rot_right(t, x->parent);
      }
      x = t->root; // 조정 완료, 루프 탈출
    }
  }

  if (x) {
    // printf("x->color = RBTREE_BLACK\n");
    x->color = RBTREE_BLACK;  // 최종 노드를 블랙으로 설정
  }
}

node_t* tree_minimum(rbtree* t, node_t* n) {
  while (n->left != t->nil) {
    n = n->left;
  }
  return n;
}

// int rbtree_erase(rbtree* t, node_t* p) {
//     // TODO: implement erase
//     key_t key = p->key;
//     color_t delete_color;
//     node_t *replace_node = bst_delete(t, p, &delete_color);
//     if (delete_color == RBTREE_BLACK) {
//         rbtree_delete_check(t, replace_node);
//     }

    // printf("delete %d\t: ", key);
//     // preorder_print(t, t->root);
    // printf("\n");
    
//     return 0;
// }

void rbtree_delete_check(rbtree* t, node_t* x) {
  if (x == NULL) {
    return;
  }

  if (t->root == x || x->color == RBTREE_RED) {
    x->color = RBTREE_BLACK;
    return;
  }

  node_t *bro;
  if (x->parent->left == x) {
    bro = x->parent->right;

    // case1 : 형제가 red
    if (bro->color == RBTREE_RED) {
      bro->color = RBTREE_BLACK;
      x->parent->color = RBTREE_RED;
      rot_left(t, x->parent);
      bro = x->parent->right;
    }
    // case2 : 형제의 자녀가 모두 black
    if (bro->left->color == RBTREE_BLACK && bro->right->color == RBTREE_BLACK) {
      bro->color = RBTREE_RED;
      rbtree_delete_check(t, x->parent);
      return;
    }
    // case3 : 형제의 왼쪽 자녀가 red
    if (bro->left->color == RBTREE_RED && bro->right->color == RBTREE_BLACK) {
      bro->left->color = RBTREE_BLACK;
      bro->color = RBTREE_RED;
      rot_right(t, bro);
      bro = x->parent->right;
    }
    // case4 : 형제의 오른쪽 자녀가 red
    bro->color = x->parent->color;
    x->parent->color = bro->right->color = RBTREE_BLACK;
    rot_left(t, x->parent);
  } else {
    bro = x->parent->left;

    // case1 : 형제가 red
    if (bro->color == RBTREE_RED) {
      bro->color = RBTREE_BLACK;
      x->parent->color = RBTREE_RED;
      rot_right(t, x->parent);
      bro = x->parent->left;
    }
    // case2 : 형제의 자녀가 모두 black
    if (bro->left->color == RBTREE_BLACK && bro->right->color == RBTREE_BLACK) {
      bro->color = RBTREE_RED;
      rbtree_delete_check(t, x->parent);
      return;
    }
    // case3 : 형제의 오른쪽 자녀가 red
    if (bro->right->color == RBTREE_RED && bro->left->color == RBTREE_BLACK) {
      bro->right->color = RBTREE_BLACK;
      bro->color = RBTREE_RED;
      rot_left(t, bro);
      bro = x->parent->left;
    }
    // case4 : 형제의 왼쪽 자녀가 red
    bro->color = x->parent->color;
    x->parent->color = bro->left->color = RBTREE_BLACK;
    rot_right(t, x->parent);
  }
  x->color = RBTREE_BLACK;
  t->nil->parent = t->nil;
}

node_t *bst_insert(rbtree *t, const key_t key) {
    node_t *insert_node = (node_t *)calloc(1, sizeof(node_t));
    insert_node->key = key;
    insert_node->color = RBTREE_RED;
    insert_node->right = insert_node->left = t->nil;

    if (t->root == t->nil){
        insert_node->color = RBTREE_BLACK;
        insert_node->parent = t->nil;
        t->root = insert_node;
    } else {
        node_t *now_node = t->root;
        node_t *prev_node = t->nil;
        while (now_node != t->nil) {
            prev_node = now_node;
            if (key < now_node->key){
                now_node = now_node->left;
            } else{
                now_node = now_node->right;
            }
        }

        if (key <= prev_node->key)
            prev_node->left = insert_node;
        else
            prev_node->right = insert_node;
        insert_node->parent = prev_node;
    }

    return insert_node;
}

void rbtree_insert_check(rbtree *t, node_t *check) {
    if (check == t->root) {
        check->color = RBTREE_BLACK;
        return;
    }
    if (check->parent->color == RBTREE_BLACK){
        return;
    }
    
    node_t *parent = check->parent;
    node_t *grand = parent->parent;
    node_t *uncle = (grand->left == parent)? grand->right : grand->left;
    
    if (uncle->color == RBTREE_RED) {
        parent->color = uncle->color = RBTREE_BLACK;
        grand->color = RBTREE_RED;
        rbtree_insert_check(t, grand);
    } else {
        grand->color = RBTREE_RED;
        if (grand->left == parent) {
            if (parent->left == check) {
                parent->color = RBTREE_BLACK;
                rot_right(t, grand);
            } else {
                check->color = RBTREE_BLACK;
                rot_left(t, parent);
                rot_right(t, grand);
            }
        } else {
            if (parent->right == check) {
                parent->color = RBTREE_BLACK;
                rot_left(t, grand);
            } else {
                check->color = RBTREE_BLACK;
                rot_right(t, parent);
                rot_left(t, grand);
            }
        }
    }
}
