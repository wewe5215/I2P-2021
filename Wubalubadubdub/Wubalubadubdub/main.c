//
//  main.c
//  Wubalubadubdub
//
//  Created by 朱季葳 on 2021/3/26.
//

#include <stdio.h>
#include <stdlib.h>
typedef struct _node
{
    int data;
    struct _node*right;
    struct _node*left;
}node;
int val[200005];
int i=0;
node* construct(int start,int end);
node* make_node(int data);
void print(node* root);
int main(int argc, const char * argv[])
{
    while(~scanf("%d",&val[i++]));
    i--;
    node* root=construct(0,i-1);
    print(root);
    
    return 0;
}
node* construct(int start,int end)
{
    int n=0;
    if(start>end)return NULL;
    node* root=make_node(val[end]);
    for(n=end;n>=start;n--)
    {
        if(val[n]<root->data)break;
    }
    root->right=construct(n+1, end-1);
    root->left=construct(start, n);
    return root;
}
node* make_node(int data)
{
    node* root=(node*)malloc(sizeof(node));
    root->data=data;
    root->left=NULL;
    root->right=NULL;
    return root;
}
void print(node* root)
{
    printf("%d",root->data);
    if(root->left)
    {
        printf(" ");
        print(root->left);
    }
    if(root->right)
    {
        printf(" ");
        print(root->right);
        
    }
}
