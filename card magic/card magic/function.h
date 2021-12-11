//
//  function.h
//  card magic
//
//  Created by 朱季葳 on 2021/3/6.
//

#ifndef __FUNCTION_H__
#define __FUNCTION_H__
typedef struct _Node{
    int size;
    int* data;
    struct _Node* next;
} Node;

Node* ReadOneList();
void PrintList(Node*);
void Merge(Node*, int, int);
void Cut(Node*, int, int);

#endif
