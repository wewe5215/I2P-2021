//
//  main.c
//  guess left or right
//
//  Created by 朱季葳 on 2021/4/28.
//

#include <stdio.h>
#include <stdlib.h>
int lch[200005],rch[200005];
int root;
int root_index[200005];
int ans[200005];
int input[200005];
int idx;
int point_to[200005];
void traverse(int node)
{
    
    if(node){
       traverse(lch[node]);
       ans[idx]=node;
       idx++;
       traverse(rch[node]);
    }
}
int main(int argc, const char * argv[]) {
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        idx=1;
        for(int i=1;i<=n;i++)
            {
                scanf("%d %d",&lch[i],&rch[i]);
                point_to[lch[i]]+=1;
                point_to[rch[i]]+=1;
            }
            for(int i=1;i<=n;i++)
            {
                scanf("%d",&input[i]);
                root_index[input[i]]=i;
            }
            for(int i=1;i<=n;i++)
            {
                if(lch[i]!=0&&root_index[lch[i]]>root_index[i])
                {
                    int temp=lch[i];
                    lch[i]=rch[i];
                    rch[i]=temp;
                }
                if(rch[i]!=0&&root_index[rch[i]]<root_index[i])
                {
                    int temp=lch[i];
                    lch[i]=rch[i];
                    rch[i]=temp;
                }
            }
        for(int i=1;i<=n;i++)
        {
            if(point_to[i]==0){
                root=i;break;
                
            }
        }
            traverse(root);
        //    printf("%d\n",root);
            int flag=1;
            for(int i=1;i<=n;i++)
            {
                if(ans[i]!=input[i]){
                    flag=0;
                    break;
                }
            }
        //    for(int i=1;i<=n;i++)printf("%d",ans[i]);
        //    printf("\n");
            if(flag)printf("YES\n");
            else printf("NO\n");
        for(int i=1;i<=n;i++)point_to[i]=0;
    }
    
    
    return 0;
}
