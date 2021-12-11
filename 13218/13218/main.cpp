//
//  main.cpp
//  13218
//
//  Created by 朱季葳 on 2021/6/3.
//

#include <iostream>
#include <set>
using namespace std;
long long n,q;
long long ans[100005];
int main(int argc, const char * argv[])
{
    cin>>n>>q;
    set<pair<long, long>>s;
    for(int i=1;i<=n;i++)
    {
        s.insert(make_pair(0, i));
        ans[i]=0;
    }
    while(q--)
    {
        int type=0;
        cin>>type;
        if(type==1)
        {
            long long p,u;
            cin>>p>>u;
            auto it=s.find(pair<long, long>(ans[p],p));
            s.erase(it);
            ans[p]+=u;
            s.insert(make_pair(ans[p], p));
        }
        else
        {
            long long x,y,v;
            cin>>x>>y>>v;
            auto it=s.lower_bound(pair<long, long>(y,x));//least element greater than (x+v,y)
            if(it!=s.end()&&it->first==y&&it->second<=x+v)
            {
                ans[it->second]-=it->second-x;
                s.erase(it);
                s.insert(make_pair(ans[it->second],it->second));
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        cout<<ans[i];
        if(i!=n)cout<<" ";
        else cout<<"\n";
    }
       ;
    return 0;
}
