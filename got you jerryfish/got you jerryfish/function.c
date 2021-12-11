//
//  function.c
//  got you jerryfish
//
//  Created by 朱季葳 on 2021/3/7.
//

#include "function.h"
#include<stdio.h>
#include<stdlib.h>
void createLinkedList(Node **head, int N, int *arr)
{
    *head=(Node*)malloc(sizeof(Node));
    Node* temp=*head;
    temp->val=arr[1];
    temp->next=NULL;
    *head=temp;
    for(int i=2;i<=N;i++)
    {
        Node* a=(Node*)malloc(sizeof(Node));
        temp->next=a;
        a->val=arr[i];
        a->next=NULL;
        temp=a;
    }
        
    temp->next=*head;
    
    
}
void swapTwoSegment(Node **head, int a, int b, int len)
{
   ;
    Node* A=*head;
    Node* B=*head;
    while(--a)A=A->next;//再跑迴圈之前減，不果不符就不跑，這樣就不用擔心要讀取head的問題
    while(--b)B=B->next;
    
   while(len--)
   {
       int temp=0;
       temp=A->val;
       A->val=B->val;
       B->val=temp;
       A=A->next;
       B=B->next;
   }
}


/*void createLinkedList(Node **head, int N, int *arr){
    Node *now = (Node*)malloc(sizeof(Node));
    now->val = arr[1], *head = now;                    //注意main裡arr下標從1開始
    for(int i=2;i<=N;i++) now->next = (Node*)malloc(sizeof(Node)), now = now->next, now->val = arr[i];
    now->next = *head;
}
void swapTwoSegment(Node **head, int a, int b, int len){
    Node *A = *head,*B = *head;
    while(--a) A = A->next;
    while(--b) B = B->next;
    while(len--){
        int tmp = A->val;
        A->val = B->val, B->val = tmp, A = A->next, B = B->next;
    }
}*/
