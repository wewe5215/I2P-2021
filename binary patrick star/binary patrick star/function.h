//
//  function.h
//  binary patrick star
//
//  Created by 朱季葳 on 2021/3/26.
//

#ifndef function_h
#define function_h

#include <stdio.h>

typedef struct _Node {
    struct _Node *left, *right;
    int id;
} Node;

Node* buildBinaryTree(int n, int* lch, int* rch);
void Traversal(Node* root, int* sz);
void freeBinaryTree(Node* root);

/*
You can malloc the space for every node in advance.

Node* buildBinaryTree(int n, int* lch, int* rch) {
    Node* node = (Node*) malloc(sizeof(Node) * n);
    ...
    ...
    ...
    return node;
}

void freeBinaryTree(Node* root) {
    free(root);
}
*/
#endif
/* function_h */
