//
//  function.h
//  after rain
//
//  Created by 朱季葳 on 2021/9/29.
//

#ifndef function_h
#define function_h

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct _NODE
{
    char color[10];
    struct _NODE *next;
} Node;
void insert(Node** head, char* buf, int num1);

void erase1(Node**, int num1);

void erase2(Node**, char* buf);

void reverse(Node**, int num1, int num2);

#endif /* function_h */
