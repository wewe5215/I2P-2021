//
//  main.c
//  move the books
//
//  Created by 朱季葳 on 2021/4/27.
//
//warning!!
//1.the left side of book[p1] isn't always be table[p1]
//2.the position of book[p2] isn't always be table[p2]
#include <stdio.h>
#include <stdlib.h>
typedef struct _Node{

    int val;

    struct _Node* next;

} Node;


Node table[25];
Node book[25];
int position[25];


void resetBook(int p2) {

    Node* head=book[p2].next;
    
    while(head)
    {
        int val=head->val;
        position[val]=val;
        table[val].next=head;
        head=head->next;
        book[val].next=NULL;
        
       
    }
    
}

void pileOnto(int p1, int p2) {

    
    Node* temp=&table[position[p1]];
    while(temp->next->val!=p1)
    {
        temp=temp->next;
        
    }
    temp->next=NULL;
    book[p2].next=&book[p1];
    Node* head=&book[p1];
    while(head)
    {
        position[head->val]=position[p2];
        head=head->next;
    }
}

void initialize(int n) {
  
    for(int i=0;i<n;i++)
    {
        position[i]=i;
        table[i].next=&book[i];
        book[i].next=NULL;
        book[i].val=i;
    }
}


int main() {

    int n;

    int i;


    scanf("%d", &n);
   
    initialize(n);


    while(1){

        char input[100] = {0};

        int p1, p2;

        scanf("%s", input);

        if(input[0] == 'e')

            break;

        scanf("%d", &p1);

        scanf("%s", input);

        scanf("%d", &p2);

        if(position[p1] == position[p2])

            continue;


        resetBook(p2);

        pileOnto(p1, p2);

    }


    Node* tmp;

    for(i = 0; i < n; i++){

        printf("%d:", i);

        tmp = table[i].next;

        while(tmp != NULL){

            printf(" %d", tmp->val);

            tmp = tmp->next;

        }

        printf("\n");

    }


        return 0;

}
