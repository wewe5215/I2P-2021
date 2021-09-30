//
//  function.c
//  after rain
//
//  Created by 朱季葳 on 2021/9/29.
//

#include "function.h"

void insert(Node** head, char* buf, int num1){
    //head's index is 0
    int index = 0;
    Node* temp = *head;
    Node* temp2;
    Node* new = (Node*)malloc(sizeof(Node));
    strcpy(new->color, buf);
    new->next = NULL;
    if((*head)->next == NULL)
        (*head)->next = new;
    else{
        while (temp->next != NULL) {
                
                if(index == num1)
                    break;
                
                index++;
                temp = temp->next;
        }
        temp2 = temp->next;
        temp->next = new;
        new->next = temp2;
    }
}

//erase the color locates at <dest>
void erase1(Node** head, int num1){
    if((*head) == NULL)return;
    int index = 0;
    Node* temp = *head;
    Node* temp2 = *head;
    while (temp != NULL) {
        if(index == num1 - 1)
            break;
        if(temp->next->next == NULL)
            break;
        temp = temp->next;
        index++;
    }
    if(temp->next){
        temp2 = temp->next;
        temp->next = temp2->next;
    }
    else{
        temp2 = temp->next;
        temp->next = NULL;
    }
        
    
    if(temp2)
        free(temp2);
   
}

//erase all <color> in the sequence
void erase2(Node** head, char* buf){
    if((*head) == NULL)return;
    Node* temp = *head;
    Node* temp2 = *head;
    while (temp->next != NULL) {
        
        if(!strcmp(temp->next->color, buf)){
            
            temp2 = temp->next;
            temp->next = temp2->next;
            //printf("test:%s\n",temp2->color);
            free(temp2);
            continue;
        }
        temp = temp->next;
            
    }
    
    
}

//reverse the elements from dest1> to <dest2>
void reverse(Node** head, int num1, int num2){
    int index = 0;
    Node* temp = *head;
    Node* temp2 = *head;
    Node* pre;
    Node* after_end;
    if((*head) == NULL)return;
    if(num1 == num2||num1 < 1 || num2 <1)return;
    if(num1 > num2){
        int t = num1;
        num1 = num2;
        num2 = t;
    }
    while (temp->next != NULL) {
        if(index == num1 - 1)
            pre = temp;
        else if (index == num2 + 1){
            break;
        }
        temp = temp->next;
        index++;
        
    }
    if(index == num2 + 1)
       after_end = temp;//index==num2 + 1
    else
        after_end = NULL;
    Node* now= pre->next->next;
    Node* end = pre->next;
    temp = pre->next;//the last one before "now"
    while(now != after_end){
        temp2 = now->next;
        now->next = temp;
        temp = now;
        now = temp2;
    }
    pre->next = temp;
    end->next = after_end;
  
    
}

