//
//  function.cpp
//  stack
//
//  Created by 朱季葳 on 2021/5/9.
//

#include "function.hpp"
using namespace std;
List_stack::List_stack()
{
    head=nullptr;//in c++,null=0
    tail=nullptr;
}
List_stack::~List_stack()
{
    head=nullptr;
    tail=nullptr;
    
}
void List_stack::push(const int &n)
{
    ListNode* node=nullptr;
    if(head==nullptr)
    {
        node=new ListNode(n);
        head=node;
        tail=node;
    }
    else
    {
        ListNode* temp=head;
        node=new ListNode(n);
        while(temp->nextPtr)temp=temp->nextPtr;
        temp->nextPtr=node;
        node->prevPtr=temp;
        tail=node;
        
        
    }
}
void List_stack::pop()
{
    if(tail==head)head=tail=nullptr;
    else tail=tail->prevPtr;
    if(tail)tail->nextPtr=nullptr;
    
   
}
void List_stack::print()
{
    ListNode* temp=tail;
    
       while(temp)
       {
         cout<<temp->data;
         if(temp->prevPtr)cout<<" ";
         temp=temp->prevPtr;
        
       }
}
