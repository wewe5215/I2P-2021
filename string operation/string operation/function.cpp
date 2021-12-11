//
//  function.cpp
//  string operation
//
//  Created by 朱季葳 on 2021/5/13.
//

#include "function.hpp"
Str:: Str(char* s)//the original string and when new string is inserted,it will not be changed
{
    head=new Char(s[0]);
    tail=head;
    for(int i=1;s[i]!='\0';i++)
    {
        tail->next=new Char(s[i]);
        tail=tail->next;
        
    }
   
    
}// construct a new Str by linked list of Char

Str:: Str(const Str & s)//when new string is inserted,it will help to connect them
{
    head=new Char(s.head->text);
    tail=head;
    Char *temp=s.head->next;
    while(temp)
    {
        tail->next=new Char(temp->text);
        tail=tail->next;
        temp=temp->next;
    }
}// copy constructor
Str& Str:: strInsert(const Str & s)
{
    Str *temp=new Str(s);
    tail->next=temp->head;
    tail=temp->tail;
    return *this;
}
