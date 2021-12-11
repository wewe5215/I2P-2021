//
//  main.c
//  moving books
//
//  Created by 朱季葳 on 2021/4/3.
//

#include <stdio.h>
#include <stdlib.h>
typedef struct _node
{
    int data;
    struct _node* right;
    struct _node* left;
}node;
char s1[10];char s2[10];
node table[25];
node book[25];
int A,B=0;
int flag=0;
void rearrange(node* head);
int main(int argc, const char * argv[])
{
    int n=0;
    scanf("%d",&n);
    
    for(int i=0;i<n;i++)
    {
        table[i].right=&book[i];
        book[i].data=i;
        book[i].right=NULL;
        book[i].left=&table[i];
    }
    while(scanf("%s",s1))
    {
        if(s1[0]=='e')break;//exit
        scanf("%d %s %d",&A,s2,&B);
        if(A==B)continue;
        if(A>=n||B>=n||A<0||B<0)continue;
        node* temp=&book[A];
        while(temp->left)temp=temp->left;
        while(temp)
        {
            if(temp->data==B)
            {
                flag=1;
                break;
            }
            temp=temp->right;
        }
        if(flag){
            flag=0;
            continue;
        }
        if(s1[0]=='m')rearrange(&book[A]);
        if(s2[0]=='o'&&s2[1]=='n')//move A onto B +pile A onto B
        {
               rearrange(&book[B]);
               book[B].right=&book[A];
               book[A].left->right=NULL;
               book[A].left=&book[B];
            
        }
        else if(s2[0]=='o'&&s2[1]=='v')
        {
                
                //to find the tail
                node* tail=&book[B];
                while(tail->right)tail=tail->right;
                tail->right=&book[A];
                book[A].left->right=NULL;
                book[A].left=tail;
           
        }
        
    }
    for(int i=0;i<n;i++)
    {
        node* head=table[i].right;
        printf("%d:",i);
        while(head)
        {
            printf(" %d",head->data);
            head=head->right;
        }
        printf("\n");
    }
        
    
    return 0;
}
void rearrange(node* head)
{
    if(head->right)
    {
      node* root=head->right;
      node* temp;
      while(root)
      {
        table[root->data].right=root;
        root->left=&table[root->data];
        temp=root;
        root=root->right;
        temp->right=NULL;
      }
      head->right=NULL;
    }
   
}
