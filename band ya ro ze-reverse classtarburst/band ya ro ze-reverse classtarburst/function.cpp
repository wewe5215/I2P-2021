//
//  function.cpp
//  band ya ro ze-reverse classtarburst
//
//  Created by 朱季葳 on 2021/5/9.
//

#include "function.hpp"
#include <string>
#include <iostream>
/* TODO: destructor for this class */
Node::~Node()
{
    Node*temp;
    if(neighbors[0]!=nullptr)temp=neighbors[0];
    else temp=neighbors[1];
    if(temp)
    {
        temp->unLink(this);
        delete temp;
    }
}
/* TODO: using a string to initialize this linked list */
void List::init(std::string s)
{
    if(s=="\n")
    {
        head=nullptr;
        tail=nullptr;
    }
    else
    {
        head=new Node(s[0]);//new[size] so you have to use ( )
        tail=head;//allocate the memory and let it help the establishment of neighbors
        //not allocate a memory to tail,so we don't have to delete it
        for(int i=1;i<s.size();i++)
        {
            Node *temp=new Node(s[i]);
            temp->link(tail);
            tail->link(temp);
            tail=temp;
            
        }
    }
}
/* TODO: make this linked list be a new linked list which is merged from two linked list */
void List:: merge(List &front, List &back)
{
    if(front.tail==nullptr)
    {
        head=back.head;
        tail=back.tail;
    }
    else if(back.tail==nullptr)
    {
        head=front.head;
        tail=front.tail;
    }
    else
    {
        
        front.tail->link(back.head);
        back.head->link(front.tail);
        head=front.head;
        tail=back.tail;
    }
    
}

/* TODO: exchange this linked list with another linked list; try to use std::swap! */
void List:: swap(List &swapList)
{
   std:: swap(head,swapList.head);
   std:: swap(tail,swapList.tail);
}
/* TODO: reverse the order of this linked list */
void List:: reverse()
{
    std:: swap(head,tail);
}

/* TODO: destructor for this class */
List::~List()
{
    delete head;
  
}
