//
//  main.c
//  prefix boolean expression
//
//  Created by 朱季葳 on 2021/3/25.
//

#include <stdio.h>
char expr[35];
int n=0;
int i=0;
int f();

int main(int argc, const char * argv[])
{
    scanf("%s" , expr);
    for( i = 0;i < 16;i++ )
    {
        printf("%d %d %d %d %d\n",(i>>3)&1,(i>>2)&1,(i>>1)&1,i&1,f());
        n=0;//記得重置
    }
    return 0;
}

int f()
{
    int x,y;
    if(expr[n]=='&')
    {
        n++;
        x=f();
        n++;
        y=f();
        x&=y;
    }
     else if(expr[n]=='|')//一定要else if不然會重複算
    {
        n++;
        x=f();
        n++;
        y=f();
        x|=y;
    }
     
    else
    {
        x=(i>>(3-expr[n]+'A'))&1;//Ａ在最左邊，不要搞反！
    }
    return x;
}
