//
//  function.c
//  after rain
//
//  Created by 朱季葳 on 2021/9/29.
//

#include "function.h"
// insert <color> after the location of <dest>
void insert(Node** head, char* buf, int num1){
       
    int index = 0;
    Node* temp = *head;
    Node* temp2;
    Node* new = (Node*)malloc(sizeof(Node));
    strcpy(new->color, buf);
   // printf("%s\n",new->color);
            if(num1 != 0){
                while (temp != NULL) {
                            index++;
                            temp = temp->next;
                            if(index == num1)
                                break;
                            
                }
            }
                if(temp==NULL)
                    temp = new;
                else{
                    temp2 = temp->next;
                    temp = new;
                    new->next = temp2;
                }
            

}

//erase the color locates at <dest>
void erase1(Node** head, int num1){
    Node* temp = *head;
    Node* temp2 = *head;
    int index = 0;
    if(num1 != 0){
        while(temp != NULL){
            
            if(index == num1 - 1)
                break;
            
            temp = temp->next;
            index++;
        }
        if(temp){
            temp2 = temp->next;
            temp->next = temp2->next;
        }
    }
    else{
        *head = temp2->next;
    }
    
        
    free(temp2);
}

//erase all <color> in the sequence
void erase2(Node** head, char* buf){
    
    
}

//reverse the elements from dest1> to <dest2>
void reverse(Node** head, int num1, int num2){
    
}
