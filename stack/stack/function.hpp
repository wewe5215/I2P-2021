//
//  function.hpp
//  stack
//
//  Created by 朱季葳 on 2021/5/9.
//

#ifndef FUNCTION_H
#define FUNCTION_H
#include <iostream>

class ListNode
{
    friend class List_stack; //make List_stack a friend
    public:
        ListNode( const int &info ) //constructor
        : data( info ), nextPtr( NULL ), prevPtr( NULL )
    
        {
        } //end ListNode constructor
    /*equal to
     ListNode(const int &info)
     {
        data=info;
        nextptr=NULL;
        prevptr=NULL;
     }
    */
    private:
        int data; //data
        ListNode *nextPtr; // next node in list
        ListNode *prevPtr;
}; //end class ListNode

class List_stack {
    public:
        List_stack();
        ~List_stack();
        void push(const int &n);
        void pop();
        void print();
    private:
        ListNode *head;
        ListNode *tail;
};
#endif // FUNCTION_H
