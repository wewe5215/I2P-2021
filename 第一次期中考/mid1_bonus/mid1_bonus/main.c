//
//  main.c
//  mid1_bonus
//
//  Created by 朱季葳 on 2021/5/4.
//

#include <stdio.h>
#include <stdlib.h>
int lch[500005],rch[500005];
int root;
int ans[500005];
int input[500005];
int node_index[500005];
int idx[500005];
int pos;
void traverse(int node)
{
    if(node)
    {
    traverse(lch[node]);
   // if(node==root)ans[pos]=0;
   // else
    ans[pos]=node;
    pos++;
    traverse(rch[node]);
 
    }
    return;
 
}
int main()
{
    int n=0;
   while(scanf("%d",&n)!=EOF)
   {
       for(int i=1;i<=n;i++)
    {
        scanf("%d",&idx[i]);
        if(idx[i]==0)
        {
            root=i;
            continue;
        }
        if(lch[idx[i]]!=0)rch[idx[i]]=i;
        else lch[idx[i]]=i;
 
    }
 
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&input[i]);
        if(input[i]==0)node_index[root]=i;
        else node_index[input[i]]=i;
    }
  //  for(int i=1;i<=n;i++)printf("%d",node_index[i]);
  //  printf("\n");
    for(int i=1;i<=n;i++)
    {
        int temp;
        if(lch[i]!=0&&node_index[lch[i]]>node_index[i])
        {
            temp=rch[i];
            rch[i]=lch[i];
            lch[i]=temp;
        }
        if(rch[i]!=0&&node_index[rch[i]]<node_index[i])
        {
            temp=rch[i];
            rch[i]=lch[i];
            lch[i]=temp;
        }
    }
   /* for(int i=1;i<=n;i++)
    {
        printf("%d,%d ",lch[i],rch[i]);
    }
    printf("\n");*/
    pos=1;
    int flag=1;
    traverse(root);
    for(int i=1;i<=n;i++)
    {
        if(input[i]==0)continue;
        if(ans[i]!=input[i])
        {
            flag=0;
            break;
        }
    }
    if(flag)printf("YES\n");
    else printf("NO\n");
   // for(int i=1;i<=n;i++)printf("%d",ans[i]);
       for(int i=1;i<=n;i++)
       {
           lch[i]=0;
           rch[i]=0;
       }
   }
 
    return 0;
}
