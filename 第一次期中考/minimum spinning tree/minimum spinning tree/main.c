//
//  main.c
//  minimum spinning tree
//
//  Created by 朱季葳 on 2021/4/13.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int n=0;
int now=0;
char s[300005];
typedef struct _node
{
    struct _node* left;
    struct _node* right;
    int oper;
    int eval;
    char data;
}node;
int ans;
void evaluate(node* root);
void create(node** head);
void check(node** head);
void left_spinning(node** head);
void right_spinning(node** head);
int main(int argc, const char * argv[])
{
    scanf("%d",&n);
    scanf(" %s",s);
    node* head=NULL;
    create(&head);
    ans=head->eval;
    if(head->left->oper==1)left_spinning(&head);
    
//    check(&head);
//    printf("\n");
    if(head->right->oper==1)right_spinning(&head);
    printf("%d\n",ans);
    
    return 0;
}
void create(node** head)
{
    
    *head=(node*)malloc(sizeof(node));
    node* root=*head;
    root->data=s[now];
    root->left=NULL;
    root->right=NULL;
    now++;
    if(s[now]=='-'||s[now]=='+'||s[now]=='*')create(&root->left);
    else
    {
        root->left=malloc(sizeof(node));
        root->left->data=s[now];
        root->left->left=NULL;
        root->left->right=NULL;
        root->left->oper=0;
        root->left->eval=root->left->data-'0';
        now++;
    }
    if(s[now]=='-'||s[now]=='+'||s[now]=='*')create(&root->right);
    else
    {
        root->right=malloc(sizeof(node));
        root->right->data=s[now];
        root->right->left=NULL;
        root->right->right=NULL;
        root->right->oper=0;
        root->right->eval=root->right->data-'0';
        now++;
    }
    if(root->data=='-'||root->data=='+'||root->data=='*')
    {
        root->oper=1;
        if(root->data=='-')
           root->eval=root->left->eval-root->right->eval;
        else if(root->data=='+')
           root->eval=root->left->eval+root->right->eval;
        else
            root->eval=root->left->eval*root->right->eval;
    }

}
void check(node** head)
{
    node* root=*head;
    printf("%c ",root->data);
    if(root->left)check(&root->left);
    if(root->right)check(&root->right);
}
void left_spinning(node** head)
{
    node* root=*head;
    node* temp=root->right;
    root->right=temp->left;
    temp->left=root;
    int a=root->eval;
    int b=temp->eval;
    if(root->data=='-')
       root->eval=root->left->eval-root->right->eval;
    else if(root->data=='+')
    {
        root->eval=root->left->eval+root->right->eval;
//        printf("+:%d\n",root->eval);
    }
       
    else
        root->eval=root->left->eval*root->right->eval;
    if(temp->data=='-')
       temp->eval=temp->left->eval-temp->right->eval;
    else if(temp->data=='+')
       temp->eval=temp->left->eval+temp->right->eval;
    else
    {
        temp->eval=temp->left->eval*temp->right->eval;
        
        
    }
    if(temp->eval<ans)ans=temp->eval;
//    printf("l:%d\n",temp->eval);
    if(temp->right->oper==1)left_spinning(&temp);
    node* temp2=root->right;
    root->right=temp;
    temp->left=temp2;
    root->eval=a;
    temp->eval=b;
    return;
}
void right_spinning(node** head)
{
    node* root=*head;
    node* temp=root->left;
    root->left=temp->right;
    temp->right=root;
    int a=root->eval;
    int b=temp->eval;
    if(root->data=='-')
       root->eval=root->left->eval-root->right->eval;
    else if(root->data=='+')
    {
        root->eval=root->left->eval+root->right->eval;
//        printf("%d\n",root->right->eval);
    }
       
    else
        root->eval=root->left->eval*root->right->eval;
    if(temp->data=='-')
    {
        temp->eval=temp->left->eval-temp->right->eval;
//        printf("%d\n",temp->eval);
    }
       
    else if(temp->data=='+')
       temp->eval=temp->left->eval+temp->right->eval;
    else
        temp->eval=temp->left->eval*temp->right->eval;
    if(temp->eval<ans)ans=temp->eval;
//    printf("r:%d\n",temp->eval);
    if(temp->left->oper==1)right_spinning(&temp);
    node* temp2=root->left;
    root->left=temp;
    temp->right=temp2;
    root->eval=a;
    temp->eval=b;
    return;
}
