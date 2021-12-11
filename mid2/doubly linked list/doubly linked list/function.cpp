//
//  function.cpp
//  doubly linked list
//
//  Created by 朱季葳 on 2021/5/18.
//

#include "function.hpp"
void  List:: InsertHead(int data)
{
    if(head==nullptr)
    {
        head=new ListNode(data);
        middle=head;
        tail=head;
        cnt++;
        
    }
    else
    {
        /*ListNode* temp=new ListNode(data);
        temp->next=head;
        head->prev=temp;//NOT ALLOCATE MEMORY TO PREV,YOU HAVE TO ALLOCATE MEMORY TO PREV FIRST
        head=temp;*/
        head->prev=new ListNode(data);
        head->prev->next=head;
        head=head->prev;
        cnt++;
        if(cnt%2)middle=middle->prev;
    }
}
int   List:: RemoveHead()
{
   if(head)
    {
        int ans=0;
        ListNode* temp=head;
        //you can't put it outside,or it may cause unpredictable error
        ans=temp->data;
        if(head->next)
        {
            head=head->next;
            head->prev=nullptr;
            //don't forget it!!
            delete temp;
            cnt--;
            if(cnt%2==0)middle=middle->next;
        }
        else
        {
            reset();
        }
        
        return ans;
    }
    else
    {
        throw std::out_of_range("\n");//when there's nothing
    }
    
}
void  List:: InsertTail(int data)
{
    if(tail==nullptr)
    {
        tail=new ListNode(data);
        head=tail;
        middle=tail;
        cnt++;
    }
    else
    {
        /*ListNode* temp=new ListNode(data);//RE
        temp->prev=tail;
        tail->next=temp;
        tail=temp;*/
        tail->next=new ListNode(data);
        tail->next->prev=tail;
        tail=tail->next;
        cnt++;
        if(cnt%2==0)middle=middle->next;
    }
}
int  List:: RemoveTail()
{
    if(tail)
    {
        int ans=0;
        ListNode* temp=tail;
        ans=tail->data;
        if(tail->prev)
        {
            tail=tail->prev;
            tail->next=nullptr;
            delete temp;
            cnt--;
            if(cnt%2)middle=middle->prev;//if there's nothing before middle,then the unpredictable problem may happen
        }
        else reset();
       
        return ans;
    }
    else
        throw std::out_of_range("\n");
    
}
void List:: Swap()
{
    if(cnt<=1)return;
    ListNode* a=head;
    ListNode* b=tail;
    head=middle;
    tail=middle->prev;
    head->prev=nullptr;
    tail->next=nullptr;
    b->next=a;
    a->prev=b;
    if(cnt%2)middle=b;
    else middle=a;
  /*  List* a=new List;    //TLE!!!
    List* b=new List;
    a->head=head;
    b->tail=tail;
    int mid=cnt/2+1;
    int now=0;
    ListNode* temp=head;
    while(temp)
    {
        now++;
        if(now==mid-1)
        {
            a->tail=temp;
            b->head=temp->next;
            a->tail->next=nullptr;
            //don't forget it!!or there will br a infinite loop
            break;
        }
        temp=temp->next;
    }
    b->tail->next=a->head;
    a->head->prev=b->tail;
    head=b->head;
    tail=a->tail;*/
  
}
int  List:: getSize()
{
    return cnt;
}
int  List:: getMiddle()
{
    return middle->data;
}
