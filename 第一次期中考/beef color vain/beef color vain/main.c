//
//  main.c
//  beef color vain
//
//  Created by 朱季葳 on 2021/4/27.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
long long int p,q;
int n;
long long int a[100000];
long long int coef[100000];
char s[1000005];
int len;
int idx=0;
int d,v;
long long int build(long long int nowcoef);
int main()
{
    scanf("%lld %lld %d",&p,&q,&n);
    for(int i=0;i<n;i++)scanf("%lld",&a[i]);
    scanf(" %s",s);
    long long int ans=build(1);
    
    
    
    
    return 0;
}
long long int build(long long int nowcoef)
{
    long long int num=0;
    if(s[idx]=='f')
    {
        idx+=2;
        long long int a=build((nowcoef*p)%q);
        idx++;
        long long int b=build(nowcoef);
        idx++;
        num=(a+b)%q;
    }
    else
    {
        while(s[idx]>='0'&&s[idx]<='9')
        {
            num=num*10+s[idx]-'0';
            idx++;
        }
        coef[num]=(coef[num]+nowcoef)%q;
    }
    
    
    
    
    
    return num;
}
