//
//  main.c
//  Gey_cool
//
//  Created by 朱季葳 on 2021/9/25.
//

#include <stdio.h>
#include <stdlib.h>
long long int num;
long long int record[2000005];

int main(int argc, const char * argv[]) {
    int n,q;
       while(scanf("%d %d", &n,&q)!=EOF)
       {
                   
                   long long int ans=0;
                   int index_a=0;
                   int index_b=0;
                   for(int i = 1;i <= n;i ++){
                       scanf("%lld",&num);
                       record[i] = record[i-1] + num;
                   }
                  
                     
                   
                   while(q--){
                       int a,b;
                       long long int value;
                       scanf("%d %d",&a,&b);
                       if(a == b){
                           if(a == 1)
                               value = record[1];
                           else
                               value = record[a] - record[a-1];
                       }
                       else if(a > b)
                           value = record[b] + (record[n] - record[a-1]);
                       else{
                           if(a == 1)
                               value = record[b];
                           else
                               value = record[b] - record[a-1];
                       }
                      // printf("test:%lld ",value);
                       if(value > ans){
                           
                           ans = value;
                           index_a = a;
                           index_b = b;
                           
                       }
                           
                   }
           printf("\n");
                   printf("Max_range: (%d,%d); Value: %lld\n",index_a,index_b,ans);
       }
    
   
        
    
    return 0;
}
