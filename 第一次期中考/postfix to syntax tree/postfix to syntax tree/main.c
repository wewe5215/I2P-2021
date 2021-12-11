//
//  main.c
//  postfix to syntax tree
//
//  Created by 朱季葳 on 2021/4/3.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
} Node;
void printInfix(Node *root);

void freeTree(Node *root);

char s1[100] , s2[100] ;

int idx ;
int flag=1;
void constructTree(Node** head)
{
    *head=(Node*)malloc(sizeof(Node));
     Node* root=*head;
     if(flag)//initialize the value of idx
     {
         idx=strlen(s1)-1;
         flag=0;
     }
    root->data=s1[idx];
    root->left=NULL;
    root->right=NULL;
    idx--;
    if(idx<0)flag=1;
if(idx>=0)
{
    if(s1[idx]>='A'&&s1[idx]<='D')
        {
            Node* right=(Node*)malloc(sizeof(Node));
            right->data=s1[idx];
            right->left=NULL;
            right->right=NULL;
            root->right=right;
            idx--;
            if(idx<0)flag=1;
        }
        else if(s1[idx]=='&'||s1[idx]=='|')
        {
            Node* right;
            constructTree(&right);
            root->right=right;
        }
}
    
 if(idx>=0)
 {
     
     if(s1[idx]>='A'&&s1[idx]<='D')
         {
             Node* left=(Node*)malloc(sizeof(Node));
             left->data=s1[idx];
             left->left=NULL;
             left->right=NULL;
             root->left=left;
             idx--;
             if(idx<0)flag=1;
         }
         else if(s1[idx]=='&'||s1[idx]=='|')
         {
             Node* left;
             constructTree(&left);
             root->left=left;
         }
        
     }
 }
    
    

void printInfix(Node *root){
    if (root != NULL) {
        printInfix(root->left);

        printf("%c", root->data);

        if((root->data == '|' || root->data == '&') && (root->right->left != NULL && root->right->right != NULL))
            printf("(");

        printInfix(root->right);

        if((root->data == '|' || root->data == '&') && (root->right->left != NULL && root->right->right != NULL))
            printf(")");
    }
}

void print_preprder(Node* root)
{
    printf("%c",root->data);
    if(root->left)
    print_preprder(root->left);
    if(root->right)
    print_preprder(root->right);
}
void freeTree(Node *root)
{
    if (root!=NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main(void)
{
    int n;
    int i , j ;
    scanf("%d", &n);// the number of test cases

    while(n>0)
    {
        scanf("%s" ,s1) ;
        idx = 0 ;
        for(i = 0 ; i < strlen(s1) ; i++){
            s2[i] = s1[strlen(s1)-1-i] ;
        }
        Node *root=NULL;
        constructTree(&root);// you have to implement this function
        printInfix(root);//output function
        printf("\n");
        print_preprder(root);
        freeTree(root);
        n--;


    }

    return 0;
}
