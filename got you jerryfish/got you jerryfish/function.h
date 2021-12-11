//
//  function.h
//  got you jerryfish
//
//  Created by 朱季葳 on 2021/3/7.
//

#ifndef function_h
#define function_h

#include <stdio.h>
typedef struct node {
    struct node* next;
    int val;
} Node;
void createLinkedList(Node **head, int N, int *arr);
void swapTwoSegment(Node **head, int a, int b, int len);
#endif /* function_h */
