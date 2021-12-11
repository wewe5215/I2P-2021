//
//  main.c
//  text editor
//
//  Created by 朱季葳 on 2021/3/5.
//

#include <stdio.h>
#include<stdlib.h>
char s[1000005];
typedef struct _data
{
    struct _data *prev;
    struct _data *next;
    char letter;
}data;
int main()
{
    int t=0;
    scanf("%d",&t);
    while(t--)
    {
        int n=0;
        scanf("%d",&n);
        scanf(" %s",s);
        data *temp;
        data *head=(data*)malloc(sizeof(data));//要加head不然在全部刪掉的情況很難處理
        head->prev=NULL;
        head->next=NULL;
        temp=head;
        for(int i=0;i<n;i++)
        {
            if(s[i]!='L'&&s[i]!='R'&&s[i]!='B')
            {
                
                    data *ans=(data*)malloc(sizeof(data));
                    ans->prev=temp;
                    if(temp->next)temp->next->prev=ans;
                    ans->next=temp->next;
                    temp->next=ans;
                    ans->letter=s[i];
                    temp=ans;
                    
                
            }
            else if(s[i]=='L'&&temp->prev!=NULL)temp=temp->prev;
            else if(s[i]=='R'&&temp->next!=NULL)temp=temp->next;
            else if(s[i]=='B')
            {
                
                    data *temp2;
                    temp2=temp;
                    if(temp->next)temp->next->prev=temp->prev;
                      temp->prev->next=temp->next;
                      temp=temp->prev;
                      free(temp2);
                
            }
        }
        head=head->next;
        while(head!=NULL)
        {
            printf("%c",head->letter);
            temp=head;
            head=head->next;
            free(temp);//不可以直接free(head)因為之後還要用
        }
        printf("\n");
    }
    return 0;
}
