//
//  main.c
//  band ya rou ze
//
//  Created by 朱季葳 on 2021/3/10.
//

#include <stdio.h>
#include<stdlib.h>
typedef struct _node{
    char* c;
    struct _node* next;
}Node;
Node* ans[100005];
Node* tail[100005];//to connect the linked list
int main(int argc, const char * argv[]) {
    int N=0;
    scanf("%d",&N);
    for(int i=1;i<=N;i++){
        int data;
        ans[i]=NULL;
        scanf("%d",&data);
        if(data!=0){ //or you may scan the number in the next line
            ans[i]=(Node*)malloc(sizeof(Node));
            ans[i]->c=(char*)malloc(sizeof(char)*(data+1));
            scanf("%s",ans[i]->c);
            ans[i]->next=NULL;
        }
        tail[i]=ans[i];

    }
    int q=0;int type=0;int a=0;int b=0;
    scanf("%d",&q);
    while(q--){
        scanf("%d %d %d",&type,&a,&b);
        if(type==1&&ans[a]){
            if(ans[b]==NULL)tail[b]=tail[a];//we need to have a tail
            tail[a]->next=ans[b];//connect from tail
            ans[b]=ans[a];
            tail[a]=NULL;
            ans[a]=NULL;
        }
        if(type==2&&ans[a]){
            if(ans[b]==NULL){
                ans[b]=ans[a];
                tail[b]=tail[a];
            }
            else{
                tail[b]->next=ans[a];
                tail[b]=tail[a];
            }
            ans[a]=NULL;
            tail[a]=NULL;
        }
        if(type==3){
            Node* temp=ans[a];
            ans[a]=ans[b];
            ans[b]=temp;
            temp=tail[a];
            tail[a]=tail[b];
            tail[b]=temp;
        }
        
    }
    
    for(int i=1;i<=N;i++){
        while(ans[i]){
            printf("%s",ans[i]->c);
            ans[i]=ans[i]->next;
        }
        printf("\n");
    }
    return 0;
}
