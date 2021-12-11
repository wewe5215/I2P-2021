//
//  function.cpp
//  happy ball
//
//  Created by 朱季葳 on 2021/5/20.
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
void List:: move(int d)
{
    if(d>=0)
    {
        while(d--)
        {
            if(cur->getNxt())
                cur=cur->getNxt();
            else break;
        }
    }
    else
    {
        while(d!=0)
        {
            if(cur->getPre())
                cur=cur->getPre();
            else break;
            d++;
        }
    }
    
}
/* TODO */
void List:: remove()
{
    cur=cur->remove();
    size--;
}
ContainerBase* create(int n, int* arr, int q, Operation* ops)
{
    //看第二個比較多還是第三個來決定用哪一個方法
    ContainerBase* solver;
    int op2=0;
    int op3=0;
    for(int i=1;i<=q;i++)
    {
        if(ops[i].type==2)op2++;
        else if(ops[i].type==3)op3++;
    }
//    Array* array=new Array(n,arr);
//    just try the syntax
    if(op3>op2)solver=new List(n,arr);
    else solver=new Array(n,arr);
    return solver;
    
}
