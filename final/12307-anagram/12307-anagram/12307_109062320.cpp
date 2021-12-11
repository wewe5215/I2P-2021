//
//  main.cpp
//  12307-anagram
//
//  Created by 朱季葳 on 2021/6/25.
//

#include <iostream>
#include <string.h>
#include <string>
#include <set>
#include <map>
using namespace std;
int main(int argc, const char * argv[])
{
    int n;
    cin>>n;
    
    set<map<int, int>>all_rec;
    map<string,int>record_by_name;
    while(n--)
    {
        map<int,int>record;//the distance to a,count
        string str;
        cin>>str;
        for(int i=0;i<str.size();i++)
        {
            if(str[i]>='a'&&str[i]<='z')
            {
                if(record.find(str[i]-'a')==record.end())
                record.insert(pair<int, int>(str[i]-'a',1));
                else
                {
                    auto it=record.find(str[i]-'a');
                    int temp=it->second;
                    temp+=1;
                    record.erase(it);
                    record.insert(pair<int, int>(str[i]-'a',temp));
                }
//                cout<<"test:"<<str[i]-'a'<<endl;
            }
            else if(str[i]>='A'&&str[i]<='Z')
            {
                if(record.find(str[i]-'A')==record.end())
                record.insert(pair<int, int>(str[i]-'A',1));
                else
                {
                    auto it=record.find(str[i]-'A');
                    int temp=it->second;
                    temp+=1;
                    record.erase(it);
                    record.insert(pair<int, int>(str[i]-'A',temp));
                }
                
            }
        }
      /*  for(auto it:record)
        {
            cout<<it.first<<" "<<it.second<<endl;
        }*/
        all_rec.insert(record);
    }
    for(auto it1=all_rec.begin();it1!=all_rec.end();it1++)
    {
        int flag=0;
        for(auto it2=++it1;it2!=all_rec.end();it2++)
        {
            if(it1==it2)
            {
                all_rec.erase(it2);
                flag=1;
            }
        }
        if(flag==1)
        {
            all_rec.erase(it1);
        }
    }
   
    return 0;
}
