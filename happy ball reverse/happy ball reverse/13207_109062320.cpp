//
//  function.cpp
//  happy ball reverse
//
//  Created by 朱季葳 on 2021/5/21.
//

#include "function.hpp"

/* TODO */
void Array:: move(int d)
{
    cur+=d;
    if(cur>size)cur=size;
    else if(cur<=0)cur=1;//d<0 cur一樣加等於d不然會負負得正
    
}
/* TODO */
void Array:: remove()
{
    for(int i=cur;i<=size;i++)
        mem[i]=mem[i+1];
    size--;
    if(cur>size)cur=size;//don't forget it!!!
    
}
/* TODO */
void Array:: reverse()
{
    for(int i=1;i<=size/2;i++)
    {
        int temp=mem[i];
        mem[i]=mem[i+size-1];
        mem[i+size-1]=temp;
    }
}
/* TODO */
void List:: move(int d)
{
    if(d>=0)
    {
        while(d--)
        {
            if(cur->nxt)
                cur=cur->nxt;
            else break;
        }
    }
    else
    {
        while(d!=0)
        {
            if(cur->pre)
                cur=cur->pre;
            else break;
            d++;
        }
    }
    
}
/* TODO */
void List:: remove()
{
    if(cur->nxt)
    cur=cur->remove(false);
    else
        cur=cur->remove(true);
}
/* TODO */
void List:: reverse()
{
    
}
ContainerBase* create(int n, int* arr, int op2, int op3)
{
    ContainerBase* solver;
    if(op3>op2)solver=new List(n,arr);
    else solver=new Array(n,arr);
    return solver;
    
}
