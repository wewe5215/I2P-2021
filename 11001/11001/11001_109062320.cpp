//
//  function.cpp
//  11001
//
//  Created by 朱季葳 on 2021/5/21.
//

#include "function.hpp"
#include <stdio.h>
Polynomial:: Polynomial(const int & power, const int coef[51])
{
    greatestPower=power;
    for(int i =0 ; i< 101 ; i++){
        coefficients[i]=0;
    }
    for(int i=greatestPower;i>=0;i--)
    {
        coefficients[i]=coef[i];
    }
}
Polynomial Polynomial:: operator+( const Polynomial & a) const
{
    Polynomial ans;
    if(greatestPower>=a.greatestPower)
    {
        ans.greatestPower=greatestPower;
        for(int i=ans.greatestPower;i>=0;i--)
        {
            ans.coefficients[i]=coefficients[i]+a.coefficients[i];
        }
    }
    else
    {
        ans.greatestPower=a.greatestPower;
        for(int i=ans.greatestPower;i>=0;i--)
        {
            ans.coefficients[i]=coefficients[i]+a.coefficients[i];
            
        }
    }
    return ans;
}// addition
Polynomial Polynomial:: operator-( const Polynomial & a) const
{
    Polynomial ans;
    if(greatestPower>=a.greatestPower)
    {
        ans.greatestPower=greatestPower;
        for(int i=ans.greatestPower;i>=0;i--)
        {
            ans.coefficients[i]=coefficients[i]-a.coefficients[i];
        }
    }
    else
    {
        ans.greatestPower=a.greatestPower;
        for(int i=ans.greatestPower;i>=0;i--)
        {
            ans.coefficients[i]=coefficients[i]-a.coefficients[i];
            
        }
    }
    return ans;}// subtraction
std::ostream &operator<<(std::ostream & os, const Polynomial &a)
{
    for(int i=a.greatestPower;i>=0;i--)
    {
        if(i!=0)
            os<<a.coefficients[i]<<" ";
        else
            os<<a.coefficients[i];
      
    }
    return os;
}
