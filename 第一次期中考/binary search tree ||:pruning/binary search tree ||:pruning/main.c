//
//  main.c
//  binary search tree ||:pruning
//
//  Created by 朱季葳 on 2021/4/5.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct _node
{
    int data;
    struct _node* left;
    struct _node* right;
    int cut;
    int size;
}node;
void search1(int root_num,node *leaf);
void search2(int root_num,node *leaf,char dir);
void search(int max,int min,node* leaf,int flag);
void note_cut(node* leaf);
void count(node* leaf);
int main(int argc, const char * argv[])
{
    int n=0;
    scanf("%d",&n);
    node* tree=(node*)malloc(sizeof(node)*(n+1));
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&tree[i].data);
        tree[i].right = NULL;
        tree[i].left = NULL;
        tree[i].cut=0;
    }
    int root=0;
    node* head=NULL;
    char dir;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&root);
        if(root == 0)
        {
            head=&tree[i];
            continue;
        }
        else
            scanf(" %c",&dir);
        if(dir == 'R')
            tree[root].right = &tree[i];
        else if(dir == 'L')
            tree[root].left = &tree[i];
    }
   
//    search1(head->data, head);
    
        count(head);
    search(INT_MAX, INT_MIN, head,0);
    for(int i=1;i<=n;i++)
    {
        if(i<n)printf("%d ",tree[i].data);
        else if(i==n)printf("%d\n",tree[i].data);

    }
   
    

    
    return 0;
}
/*void search1(int root_num,node *leaf)//左右判斷要修一下
{
    if(leaf->left&&leaf->left->cut!=1)//避免重複算
    {
        search2(root_num, leaf->left, 'L');//以右左為單位下去判斷，這樣才能完整判斷root左右邊是否符合
        search1(leaf->left->data, leaf->left);//換到下一個root
    }
    if(leaf->right&&leaf->right->cut!=1)
    {
        search2(root_num, leaf->right, 'R');
        search1(leaf->right->data, leaf->right);
    }
}
void search2(int root_num,node* leaf,char dir)
{
    if(dir=='L'&&leaf->data>=root_num)
        note_cut(leaf);
    else if(dir=='R'&&leaf->data<=root_num)
        note_cut(leaf);
    if(leaf->right)search2(root_num, leaf->right, dir);//即使這個葉子是某個根的左葉，依然視他為最上面跟的右（左）葉，依據dir判斷
    if(leaf->left)search2(root_num, leaf->left, dir);
}*/
void search(int max,int min,node* leaf,int flag)
{
    if(leaf->data>=max||leaf->data<=min)
        flag=1;
    if(flag)
    {
        leaf->data=leaf->size*(-1);
    }
    if(leaf->left)
        search(leaf->data, min, leaf->left,flag);
    if(leaf->right)
        search(max, leaf->data, leaf->right,flag);
}
void count(node* leaf)//這個也要修一下
{
    int a=1,b=1;
    if(leaf->right==NULL&&leaf->left==NULL)leaf->size=1;
    if(leaf->right)
    {
        count(leaf->right);
        a+=leaf->right->size;
    }
    if(leaf->left)
    {
        count(leaf->left);
        b+=leaf->left->size;
    }
    
        if(a<b)leaf->size=b;
        else leaf->size=a;
    

}
void note_cut(node* leaf)//this will let you have TLE!!!
{
    leaf->cut=1;
    if(leaf->right)note_cut(leaf->right);
    if(leaf->left)note_cut(leaf->left);
}
