//
//  function.cpp
//  polynomial class
//
//  Created by 朱季葳 on 2021/5/4.
//

#include "function.hpp"
using namespace std;
Polynomial::Polynomial()
{
    for(int i=0;i<101;i++)
    {
        coefficients[i]=0;
    }
    greatestPower=0;
}
Polynomial::Polynomial(const int  power, const int coef[51])
{
    for(int i=0;i<=101;i++)coefficients[i]=0;
    greatestPower=power;
    for(int i=0;i<=power;i++)coefficients[i]=coef[i];
}
Polynomial Polynomial ::add( const Polynomial poly) const // add function
{
    Polynomial output;
    int power;
    if(greatestPower>poly.greatestPower)power=greatestPower;
    else power=poly.greatestPower;
    output.greatestPower=power;
    for(int i=0;i<=power;i++)
    {
        output.coefficients[i]=coefficients[i]+poly.coefficients[i];
    }
    return output;
}
Polynomial Polynomial:: subtract( const Polynomial poly) const// subtract function
{
    Polynomial output;
    int power;
    if(greatestPower>poly.greatestPower)power=greatestPower;
    else power=poly.greatestPower;
    output.greatestPower=power;
    for(int i=0;i<=power;i++)
        output.coefficients[i]=coefficients[i]-poly.coefficients[i];
    return output;
}
Polynomial Polynomial:: multiplication( const Polynomial poly) const // multiplication function
{
    Polynomial output;
    output.greatestPower=greatestPower+poly.greatestPower;
    for(int i=0;i<=greatestPower;i++)
    {
        for(int j=0;j<=poly.greatestPower;j++)
        {
            output.coefficients[i+j]+=coefficients[i]*poly.coefficients[j];
            //+= or the pervious value can't be counted in
        }
    }
    return output;
}
void Polynomial::output() const
{
    for(int i=greatestPower;i>=0;i--)
    {
        cout<<coefficients[i];
        if(i!=0)cout<<" ";
    }
}
