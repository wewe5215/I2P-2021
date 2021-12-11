//
//  main.cpp
//  13220
//
//  Created by 朱季葳 on 2021/6/4.
//

#include <iostream>
#include <set>
using namespace std;
long long int ans[100005];
int main(int argc, const char * argv[])
{
    int n,q;
    cin>>n>>q;
    set<pair<long long int, long long int>>s;
    for(int i=1;i<=n;i++)
    {
        s.insert(pair<long long int, long long int>(0,i));//set the reverse of coordinates
        ans[i]=0;
    }
    int type=0;
    
    while (q--) {
        cin>>type;
        if(type==1)
        {
            int p,u;
            cin>>p>>u;
            if(p>=1&&p<=n)
            {
                auto it=s.find(pair<long long int, long long int>(ans[p],p));
                ans[p]+=u;
                s.erase(it);
                s.insert(pair<long long int, long long int>(ans[p],p));
            }
        }
        else
        {
            int x,y,v=0;
            cin>>x>>y>>v;
            auto it=s.lower_bound(pair<long long int, long long int>(y,x));
//            cout<<x<<" "<<y<<"\n";
//            cout<<it->first<<" "<<it->second<<"\n";
            if(it!=s.end()&&it->first!=-1&&it->first==y&&it->second<=x+v)
            {
                ans[it->second]=-1;
                s.erase(it);
                s.insert(pair<long long int, long long int>(ans[it->second],it->second));
                
            }
        }
    }
    
    for(int i=1;i<=n;i++)
    {
        cout<<ans[i];
        if(i==n)cout<<"\n";
        else cout<<" ";
    }
    return 0;
}
