//
//  main.c
//  12303_operation on sequence
//
//  Created by 朱季葳 on 2021/10/2.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct _node{
   struct _node* pre;
   struct _node* next;
   int data;
}Node;
void insert(Node* head, int val1, int val2);
void erase_node(Node* head, int val);
void move_cursor(Node** head, int value);
void show(Node* head);
char buf[10];
int element=1;
int main(int argc, const char * argv[]) {
    
    int x,q;
    int num1,num2;
    scanf("%d %d", &x, &q);
    Node* head = (Node*)malloc(sizeof(Node));
    Node** cursor = &head;
    head->pre = head->next = head;
    head->data = x;
    while (q--) {
        
            scanf("%s",buf);
            if(!strcmp("insert", buf)){
                scanf("%d %d",&num1,&num2);
                insert(*cursor, num1, num2);
                element += num2;
            }
            else if (!strcmp("erase", buf)){
                scanf("%d",&num1);
                if(num1 > element)
                    num1 = element-1;
                erase_node(*cursor, num1);
                element -= num1;
            }
            else if (!strcmp("move", buf)){
                scanf("%d",&num1);
                num1 = num1 % element;
                move_cursor(cursor, num1);
              //  printf("test2:%d\n",*cursor);
                
            }
            else
                show(*cursor);
    }
    
    return 0;
}
//insert <val1> <val2>: Insert <val2> number of elements, all with value <val1>

void insert(Node* head, int val1, int val2){
    
    Node* now = head;
    while(val2--){
        
        Node* new = (Node*)malloc(sizeof(Node));
        new->data = val1;
        new->next = now->next;
        now->next->pre = new;//sometimes new will be the last one
        now->next = new;
        new->pre = now;
        now = now->next;
    }
    
}
//erase <val>: erase <val> number of elements next to you
void erase_node(Node* head, int val){
    
    Node* temp = head;
    while(val--){
        temp = head->next;
        head->next = temp->next;
        temp->next->pre = head;
        free(temp);
    }
}
/*move <value>: Move <value> number of indexes forward. Note that <value> might be negative, which means you might move forward or backward.*/
void move_cursor(Node** head, int value){
    //這裡不能直接傳入Node* head，因為他在此被定為一個變數，如果想要改編他的話就應該傳入他的地址
    Node* now = *head;
    if(value >= 0){
        while(value--){
            now = now->next;
        }
    }
    else{
        value = abs(value);
        while(value--){
            if(now->pre)
                now = now->pre;
        }
    }
    *head = now;
   // printf("test:%d\n",now);
   // printf("test2:%d\n",*head);
    
    
}
/*
 show: Start from your position, output the sequence a. Each element separated by a space. Note that there should be no space at the end but a '\n'. */
void show(Node* head){
    
    Node* now = head->next;
    printf("%d",head->data);
    while(now != head){
       
        printf(" %d",now->data);
        now = now->next;
    }
    printf("\n");
}
