//
//  main.c
//  bee cover rain
//
//  Created by 朱季葳 on 2021/4/14.
//

#include <stdio.h>
#include <string.h>
long long int p;
long long int q;
char s[5000005];
long long int idx=0;
long long int function();
int len;
int main(int argc, const char * argv[])
{
    scanf("%lld %lld",&p,&q);
    scanf(" %s",s);
    len=strlen(s);
    long long int ans=function();
    printf("%lld\n",ans);
    return 0;
}
long long int function()
{
    long long int num=0;
    long long int a=0,b=0;
    int flag=0;
   if(s[idx]=='f')
    {
        idx+=2;
        a=function();
        idx++;
        b=function();
        idx++;
        num=(a*p+b)%q;
    }
    while (s[idx]<='9'&&s[idx]>='0')
    {
       num=num*10+s[idx]-'0';
        idx++;
    }
   /* for(;idx<len;idx++)
    {
        if(s[idx]=='f')
        {
            if(flag)
            {
                idx+=2;
                b=function();
            }
            else
            {
                idx+=2;
                a=function();
            }
        }
        else if(s[idx]==',')
        {
            flag=1;
            
        }
        else if(s[idx]<='9'&&s[idx]>=0)
        {
            if(!flag)a=a*10+s[idx]-'0';
            else b=b*10+s[idx]-'0';
        }
        else if(s[idx]==')')
        {
            idx++;
            num=(a*p+b)%q;
            return num;
        }
    }
        num=(a*p+b)%q;*/
        return num;
}
