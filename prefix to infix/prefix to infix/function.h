//
//  function.h
//  prefix to infix
//
//  Created by 朱季葳 on 2021/3/23.
//
#ifndef FUNCTION_H
#define FUNCTION_H

typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
} Node;

void constructTree(Node** head);
void printInfix(Node *root);
void freeTree(Node *root);

#endif
