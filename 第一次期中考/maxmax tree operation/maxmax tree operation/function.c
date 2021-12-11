//
//  function.c
//  maxmax tree operation
//
//  Created by 朱季葳 on 2021/4/14.
//

#include "function.h"
#include <stdio.h>
#include <stdlib.h>
struct Graph* createGraph(int n)
{
    struct Graph* g=(struct Graph*)malloc(sizeof(struct Graph));
    g->vertices_num=n;
    g->adjLists=(struct Node**)malloc(sizeof(struct Node*)*n);
    for(int i=0;i<g->vertices_num;i++)g->adjLists[i]=NULL;
    //每一個點都有自己的相鄰表，相鄰表的大小也不一樣，這裡是設定相鄰表們的地址
    return  g;
}
void addEdge(struct Graph* g, int u, int v)
{
    struct Node* a=g->adjLists[u];//保留原本的那個
    g->adjLists[u]=(struct Node*)malloc(sizeof(struct Node));
    g->adjLists[u]->id=v;
    g->adjLists[u]->next=a;//再串到後面去
    struct Node* b=g->adjLists[v];
    g->adjLists[v]=(struct Node*)malloc(sizeof(struct Node));
    g->adjLists[v]->id=u;
    g->adjLists[v]->next=b;
}
int findMax(struct Graph* g, int now, int pre)
{
    int a=now;//don't forget to count yourself!!
    for (struct Node* it = g->adjLists[now]; it; it = it->next)
    {
        if (it->id == pre) continue;
        int b=findMax(g, it->id, now);
        if(b>a)a=b;
    }
    
    return a;
}
void freeGraph(struct Graph* g)
{
   
    for(int i=0;i<g->vertices_num;i++)
    {
        struct Node* a=g->adjLists[i];
        while(a)
        {
            struct Node* b=a->next;
            free(a);
            a=b;
        }
        
    }
    free(g->adjLists);
    free(g);
    
}
