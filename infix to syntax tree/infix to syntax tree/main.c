//
//  main.c
//  infix to syntax tree
//
//  Created by 朱季葳 on 2021/3/18.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXEXPR 256
#define NUMSYM 6
char expr[MAXEXPR];  // string to store the input expression.
int pos;             // current position of parsing, from end to start

typedef enum {ID_A, ID_B, ID_C, ID_D, OP_AND, OP_OR} TokenSet;
char sym[NUMSYM];

typedef struct _Node {
    TokenSet data;
    struct _Node *left, *right;
} BTNode;

BTNode* EXPR(void);
BTNode* FACTOR(void);
BTNode* makeNode(char c);
void freeTree(BTNode *root);
void printPrefix(BTNode *root);

int main(void){
    sym[0]='A';
    sym[1]='B';
    sym[2]='C';
    sym[3]='D';
    sym[4]='&';
    sym[5]='|';
    while (scanf("%s", expr)!=EOF)
    {
        pos = strlen(expr) - 1;
        BTNode *root = EXPR();
        printPrefix(root);
        printf("\n");
        freeTree(root);
    }

    return 0;
}

/* print a tree by pre-order. */
void printPrefix(BTNode *root){
    if (root != NULL) {
        printf("%c",sym[root->data]);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}

/* clean a tree.*/
void freeTree(BTNode *root){
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

BTNode* EXPR()
{
    BTNode* node=NULL;
    BTNode* right=NULL;
    right =FACTOR();
    pos--;
    if(pos==-1||expr[pos]=='(')return right;// If a left parenthesis is encountered, or if we've hit the end of the input,
    // then the expression we just computed has to be a left expression instead.
    // So return it immediately.
    node=makeNode(expr[pos]);
    pos--;
    node->right=right;
    node->left=EXPR();
    return node;
}
    
    

BTNode* FACTOR(){
    BTNode* node=NULL;
   if(expr[pos]==')')
   {
       pos--;
       return EXPR();
   }
    else if(expr[pos]>='A'&&expr[pos]<='D')
        node=makeNode(expr[pos]);
    return node;
}
BTNode* makeNode(char c)
{
    BTNode* node=(BTNode*)malloc(sizeof(BTNode));
    int data=0;
    for(int i=0;i<NUMSYM;i++){
        if(c==sym[i]){
            data=i;
            break;
        }
    }
    node->data=data;
    node->left=NULL;
    node->right=NULL;
    return node;
}
