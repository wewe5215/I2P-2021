//
//  function.cpp
//  go on mission
//
//  Created by 朱季葳 on 2021/5/14.
//

#include "function.hpp"
#include<string.h>
BigInt:: BigInt()
{
    sign=true;
    for(int i=0;i<N;i++)
    {
        bigInt[i]=0;
    }
}
BigInt:: BigInt(char* input)
{
    sign=true;
    for(int i=0;i<N;i++)bigInt[i]=0;
    int len=strlen(input);
    int cursor=0;
    int i;
    for(i=len-1;i>7;i-=8)
    {
        int num=0;
        for(int j=i-7;j<=i;j++)
        {
            num*=10;
            num+=input[j]-'0';
        }
        bigInt[cursor]=num;
        cursor++;
    }
    int num=0;
    for(int j=0;j<=i;j++)
    {
        num*=10;
        num+=input[j]-'0';
    }
    bigInt[cursor]=num;
    
}
BigInt:: BigInt(const BigInt& input)
{
  *this=input;
}
// copy assignment operator
BigInt& BigInt:: operator = (const BigInt& input)
{
    sign=input.sign;
    for(int i=0;i<N;i++)
    {
        bigInt[i]=input.bigInt[i];}
    return *this;
}
// comparison operator
bool BigInt:: operator < (BigInt a)
{
    if(this->sign==false&&a.sign==true)return true;
    else if(this->sign==true&&a.sign==false)return false;
    else if(this->sign==true&&a.sign==true)
    {
        for(int i=N-1;i>=0;i--)
        {
            if(this->bigInt[i]>a.bigInt[i])return false;
            else if(this->bigInt[i]<a.bigInt[i])return true;
        }
    }
    else if(this->sign==false&&a.sign==false)
    {
        for(int i=N-1;i>=0;i--)
        {
            if(this->bigInt[i]<a.bigInt[i])return false;
            else if(this->bigInt[i]>a.bigInt[i])return true;
        }
    }
    return false;
    
}
bool BigInt:: operator > (BigInt a)
{
    if(this->sign==false&&a.sign==true)return false;
    else if(this->sign==true&&a.sign==false)return true;
    else if(this->sign==true&&a.sign==true)
    {
        for(int i=N-1;i>=0;i--)
        {
            if(this->bigInt[i]>a.bigInt[i])return true;
            else if(this->bigInt[i]<a.bigInt[i])return false;
        }
    }
    else if(this->sign==false&&a.sign==false)
    {
        for(int i=N-1;i>=0;i--)
        {
            if(this->bigInt[i]<a.bigInt[i])return true;
            else if(this->bigInt[i]>a.bigInt[i])return false;
        }
    }
    return false;
    
}
bool BigInt:: operator == (BigInt a)
{
    if(this->sign!=a.sign)return false;
    for(int i=N-1;i>=0;i--)
    {
        if(this->bigInt[i]!=a.bigInt[i])return false;
    }
    return true;
}
bool BigInt:: operator >= (BigInt a)
{
    if(this->sign==false&&a.sign==true)return false;
    else if(this->sign==true&&a.sign==false)return true;
    else if(this->sign==true&&a.sign==true)
    {
        for(int i=N-1;i>=0;i--)
        {
            if(this->bigInt[i]>a.bigInt[i])return true;
            else if(this->bigInt[i]<a.bigInt[i])return false;
        }
    }
    else if(this->sign==false&&a.sign==false)
    {
        for(int i=N-1;i>=0;i--)
        {
            if(this->bigInt[i]<a.bigInt[i])return true;
            else if(this->bigInt[i]>a.bigInt[i])return false;
        }
    }
    return true;}
bool BigInt:: operator <= (BigInt a)
{
    if(this->sign==false&&a.sign==true)return true;
    else if(this->sign==true&&a.sign==false)return false;
    else if(this->sign==true&&a.sign==true)
    {
        for(int i=N-1;i>=0;i--)
        {
            if(this->bigInt[i]>a.bigInt[i])return false;
            else if(this->bigInt[i]<a.bigInt[i])return true;
        }
    }
    else if(this->sign==false&&a.sign==false)
    {
        for(int i=N-1;i>=0;i--)
        {
            if(this->bigInt[i]<a.bigInt[i])return false;
            else if(this->bigInt[i]>a.bigInt[i])return true;
        }
    }
    return true;
    
}
// arithmetic operator
BigInt BigInt:: operator + (BigInt a)
{
    for(int i=0;i<N;i++)
    {
        bigInt[i]+=a.bigInt[i];
        bigInt[i+1]+=bigInt[i]/BASE;
        bigInt[i]=bigInt[i]%BASE;
        
    }
    return *this;
}
BigInt BigInt:: operator - (BigInt a)
{
    if(sign)
    {
        if(*this< a){
            *this=a-*this;
            sign=false;
        }
        else
        {
            for(int i=0;i<N;i++)
            {
                bigInt[i]-=a.bigInt[i];
                if(bigInt[i]<0)
                {
                    bigInt[i]+=BASE;
                    bigInt[i+1]-=1;
                }
            }
        }
    }
    else *this+a;
    return *this;
}
// insertion & extraction operator
istream& operator >> (istream& input, BigInt& a)//cin
{
    char s[BigInt::N*BigInt::WIDTH+5];
    input>>s;
    a=BigInt(s);
    return input;
}
ostream& operator << (ostream& output, BigInt& a)//cout
{
    if(a.sign==0)output<<"-";//print '-'
    int n=BigInt::N-1;
    while(a.bigInt[n]==0)n--;
    int first=1;
    if(n==-1)printf("0");//if the answer is 0,then n=-1,and the following code doesn't consider this condition,which may cause the second test case wrong answer
    else
    {
        while(n>=0)
            {
                if(first)
                {
                    printf("%d",a.bigInt[n]);
                    n--;
                    first=0;
                    
                }
                else{
                    
                    printf("%08d",a.bigInt[n]);
                    n--;
                }
            }
    }
    
    
    return output;
}

void solution(BigInt &tanjiro, BigInt &zenitsu, BigInt &inosuke, int n)
{
    while(n--)
    {
        BigInt mission;
        cin>>mission;
        if(inosuke>=tanjiro&&inosuke>=zenitsu)inosuke-mission;
        else if(tanjiro>=zenitsu)tanjiro-mission;
        else zenitsu-mission;
    }
}
