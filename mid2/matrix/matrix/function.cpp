//
//  function.cpp
//  matrix
//
//  Created by 朱季葳 on 2021/5/19.
//

#include "function.hpp"
Matrix:: Matrix(int s )
{
    size=s;
    buf=nullptr;
    matrix=new int*[s];
    for(int i=0;i<size;i++)matrix[i]=new int[s];
}

std::ostream &operator<<(std::ostream & out, const Matrix & a)
{
    
    for(int i=0;i<a.size;i++)
    {
        for(int j=0;j<a.size;j++)
        {
            out<<a.matrix[i][j];
            if(j<a.size-1)out<<" ";
        }
        out<<std::endl;
    }
    
    return out;
}
std::istream &operator>>(std::istream & in, Matrix & a)
{
    for(int i=0;i<a.size;i++)
    {
        for(int j=0;j<a.size;j++)
        {
            in>>a.matrix[i][j];
        }
    }
    
    return in;
}
