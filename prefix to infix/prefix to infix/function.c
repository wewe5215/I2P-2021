//
//  function.c
//  prefix to infix
//
//  Created by 朱季葳 on 2021/3/23.
//

#include "function.h"
#include <stdio.h>
#include<stdlib.h>
void printInfix(Node *root)
{
    if(root->data=='&'||root->data=='|')
    {
        if(root->left)printInfix(root->left);
        printf("%c",root->data);
        if(root->right->data=='|'||root->right->data=='&')
        {
            printf("(");
            printInfix(root->right);
            printf(")");
        }
        else printInfix(root->right);
    }
    else
    {
        printf("%c",root->data);
        return;
    }
}
