//
//  function.cpp
//  11935
//
//  Created by 朱季葳 on 2021/5/21.
//

#include "function.hpp"
void _stack:: push(const _node N)
{
    int data=N.data;
//    printf("test:%d",N.data);
    if(Begin->data==0)
    {
        Begin->data=data;
        End=Begin;
//        printf("test:%d\n",End->data);
    }
    else
    {
        End->next=new _node(data);
        End->next->prev=End;
        End=End->next;
        
    }
    
}
void _stack:: pop()
{
    if(End!=nullptr)
    {
        _node* temp=End;
            if(End->prev)
            {
                
                End->prev->next=nullptr;
                End=End->prev;
                delete temp;
            }
            else
            {
                End=nullptr;
                Begin=nullptr;
                delete temp;
            }
    }
    else
        return;
    
}
_node*  _stack:: get_data()
{
   if(End!=NULL) return End;
   else return NULL;
}
void _queue:: push(const _node N)
{
    
    int data=N.data;
//    printf("test:%d",N.data);
    if(Begin->data==0)
    {
        Begin->data=data;
        End=Begin;
//        printf("test:%d\n",End->data);
    }
    else
    {
        End->next=new _node(data);
        End->next->prev=End;
        End=End->next;
        
    }
    
}
void _queue:: pop()
{
    if(Begin!=nullptr)
    {
        _node* temp=Begin;
        if(Begin->next)
        {
            
            Begin->next->prev=nullptr;
                    Begin=Begin->next;
                    delete temp;
        }
        else
        {
            Begin=nullptr;
            End=nullptr;
            delete temp;
        }
        
    }
    else
        return;
}
_node*  _queue :: get_data()
{
    if(Begin!=NULL)return Begin;
    else return NULL;
}
