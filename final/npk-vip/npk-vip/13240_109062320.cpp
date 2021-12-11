//
//  main.cpp
//  npk-vip
//
//  Created by 朱季葳 on 2021/6/25.
//

#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;
list<int>mylist;
queue<int>country[3];
queue<int>vip;
int main(int argc, const char * argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string str;

    while(cin>>str)
    {
        
        
        if(str=="ENQUEUE")
        {
            int id;
            cin>>id;
            if(id%5==0)
            {
                vip.push(id);
            }
            else
            {
                country[id%3].push(id);
                if(find(mylist.begin(), mylist.end(), id%3)==mylist.end())
                    mylist.push_back(id%3);
                
            }
        }
        else if(str=="DEQUEUE")
        {
            int flag=0;
            if(!vip.empty())
            {
                cout<<vip.front();
                vip.pop();
                flag=1;
            }
            if(flag==1&&!mylist.empty())cout<<" ";
            if(!mylist.empty())
            {
                int first=mylist.front();
                cout<<country[first].front();
                country[first].pop();
                if(country[first].empty())mylist.pop_front();
                
            }
            cout<<endl;
        }
    }
    return 0;
}
