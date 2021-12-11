//
//  main.cpp
//  12264 - NPK-easy
//
//  Created by 朱季葳 on 2021/6/22.
//

#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <algorithm>//remember to include this to use find in line 30
using namespace std;
list<int>mylist;
queue<int>country[3];
int record[3]={0};//you can't use record!!to prevent from空集合
int main(int argc, const char * argv[])
{
    int n;
    cin>>n;
    while(n--)
    {
        string str;
        cin>>str;
        if(str=="ENQUEUE")
        {
            int id;
            cin>>id;
            country[id%3].push(id);
            if(find(mylist.begin(), mylist.end(), id%3)==mylist.end())
                mylist.push_back(id%3);
//            cout<<"test:";
//            cout<<record[id%3]<<endl;
           /* if(record[id%3]==0)
            {
                record[id%3]=1;
                mylist.push_back(id%3);
                country[id%3].push(id);
            }
            else
            {
                country[id%3].push(id);
            }*/
            
        }
        else if(str=="DEQUEUE")
        {
            if(!mylist.empty())
            {
                int first=mylist.front();
                cout<<country[first].front()<<endl;
                country[first].pop();
                if(country[first].empty())mylist.pop_front();
            }
            
        }
       
   }
    
    return 0;
}
