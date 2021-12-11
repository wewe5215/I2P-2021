#include "function.h"
#include  <stdlib.h>
#include  <stdio.h>
Node* ReadOneList()
{
    Node* N=(Node*)malloc(sizeof(Node));
    scanf("%d:",&N->size);//
    N->data=(int*)malloc(sizeof(int)*N->size);
    for(int i=0;i<N->size;i++)scanf("%d",&N->data[i]);
    N->next=NULL;//不這樣做，下面會結束不了
    return N;
    
}
void Merge(Node* head, int x, int y)
{
    Node* temp1=head;
    Node* temp2=head;
    Node* last=head;
    x-=1;
    while(x--)last=last->next;
    temp1=last->next;
    while(y--)temp2=temp2->next;
    int* store=(int*)malloc(sizeof(int)*temp2->size);//要存下來不然會不見
    for(int i=0;i<temp2->size;i++)store[i]=temp2->data[i];//存下來
    temp2->data=(int*)malloc(sizeof(int)*(temp2->size+temp1->size));//expand
    for(int i=0;i<temp2->size;i++)temp2->data[i]=store[i];//存回去
    for(int i=0;i<temp1->size;i++)temp2->data[temp2->size+i]=temp1->data[i];
    temp2->size+=temp1->size;
    last->next=temp1->next;
    free(temp1->data);free(temp1);free(store);//不能只free temp1,store有沒有都沒差，但要注意free temp1跟temp1->data的順序
}
void Cut(Node* head, int x, int y)
{
    Node* N=(Node*)malloc(sizeof(Node));
    Node* temp=head;
    while(x--)temp=temp->next;
    N->data=(int*)malloc(sizeof(int)*(temp->size-y));
    N->size=temp->size-y;
    for(int i=0;i<temp->size-y;i++)
    {
        N->data[i]=temp->data[y+i];
    }
    temp->size=y;//這裡不要搞混！差點打成-=y
    N->next=temp->next;
    temp->next=N;
}
void PrintList(Node* head)
{
    head=head->next;
    while(head!=NULL)
    {
        for(int i=0;i<head->size;i++)
        {
            printf("%d",head->data[i]);
            if(i<head->size-1)printf(" ");//注意格式
            else printf("\n");
           
        }
        head=head->next;
    }
}
