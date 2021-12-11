//
//  function.c
//  binary patrick star
//
//  Created by 朱季葳 on 2021/3/26.
//

#include "function.h"
#include <stdlib.h>
Node* buildBinaryTree(int n, int* lch, int* rch)
{
    Node* root=(Node*)malloc(sizeof(Node)*n);
    for(int i=0;i<n;i++)root[i].id=i;//put in the number
    for(int i=0;i<n;i++)
    {
        if(lch[i]!=-1)root[i].left=&root[lch[i]];//root[i].left是一個地址
        else root[i].left=NULL;
        if(rch[i]!=-1)root[i].right=&root[rch[i]];
        else root[i].right=NULL;
    }
    return root;
}
void Traversal(Node* root, int* sz)
{
    sz[root->id]=1;
    if(root->left)
    {
        Traversal(root->left, sz);
        sz[root->id]+=sz[root->left->id];
    }
    if(root->right)
    {
        Traversal(root->right, sz);
        sz[root->id]+=sz[root->right->id];
    }
}
void freeBinaryTree(Node* root)
{
    free(root);
}
