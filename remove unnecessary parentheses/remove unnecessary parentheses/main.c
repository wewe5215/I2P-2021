//
//  main.c
//  remove unnecessary parentheses
//
//  Created by 朱季葳 on 2021/3/25.
//

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
char input[260];
typedef struct _node
{
    char data;
    struct _node* left;
    struct _node* right;
}node;
node* expr();
node* factor();
node* make_leaf(char c);
int pos;
void print(node* head);
int main(int argc, const char * argv[])
{
    scanf("%s",input);
    pos=strlen(input)-1;
    node* root=expr();
    print(root);
    return 0;
}
node* expr()
{
    node* head=NULL;
    node* right=NULL;
    right=factor();
    pos--;
    if(pos==-1||input[pos]=='(')
    {
        return right;//不要pos--!不然下一個會讀不到
    }
    if(input[pos]=='&'||input[pos]=='|')
    {
        head=make_leaf(input[pos]);
        pos--;
        head->right=right;
        head->left=expr();
    }
    
    return head;
}
node* factor()
{
    node* head=NULL;
    if(input[pos]==')')
    {
        pos--;
        return expr();
    }
    else
        head=make_leaf(input[pos]);
    return head;
}
node* make_leaf(char c)
{
    node* leaf=(node*)malloc(sizeof(node));
    leaf->data=c;
    leaf->left=NULL;
    leaf->right=NULL;
    return leaf;
}
void print(node* head)
{
    if(head->data=='|'||head->data=='&')
    {
        if(head->left)print(head->left);
        printf("%c",head->data);
        if(head->right)
        {
            if(head->right->data=='|'||head->right->data=='&')
            {
                printf("(");
                print(head->right);
                printf(")");
            }
            else print(head->right);
        }
    }
    else printf("%c",head->data);
}
