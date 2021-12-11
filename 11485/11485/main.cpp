//
//  main.cpp
//  11485
//
//  Created by 朱季葳 on 2021/6/2.
//

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>//reverse
using namespace std;
int getValue(vector<int> v)
{
    int value = 0;
    int size = v.size();
    for(int i=0; i<size; i++)
    {
          /*YOUR CODE*/
        value+=v[i]*(size-i);
    }
    return value;
}
vector<int> readVector()
{
    int i=0;
    vector<int> new_vector;

    while(cin>>i)
    {
        if(i==0) break;
        /*push the integer into the vector*/
        /*YOUR CODE*/
        new_vector.push_back(i);
    }
    return new_vector;
}
struct mycompare
{
    bool operator() (const vector<int>& lhs, const vector<int>& rhs) const
    {
        return getValue(lhs) < getValue(rhs);
        //false的時候會交換
    }
};
void printVector(vector<int> v)
{
    for(int i=0;i < v.size();i++)
    {
        cout<<v.at(i)<<" ";
        //greater than [ ] 
    }
    cout<<'\n';
}
int main()
{
   set<vector<int>, mycompare> s;
    //because mycompare is defined in the set,all the element in the set will follow it
    string command;

    while(cin>>command)
    {
        if(command == "insert")
        {
            vector<int> t = readVector();//讀完全部的
            set<vector<int>, mycompare>::iterator it;//迭代器可使使用者在容器物件上遍訪，不受型別限制
            for(it=s.begin();it!=s.end();it++)        /*go through all vectors in the set*/
           {   //the last one is 0
                vector<int> cur = *it;
                if(getValue(cur)==getValue(t))          /*if the key value has existed*/
                {
                        cout<<"exist"<<endl;
                        /*YOUR CODE*/            /*erase the sequence*/
                        s.erase(cur);
                        /*YOUR CODE*/            /*reverse the sequence*/
                        reverse(t.begin(), t.end());
                        break;
                }
            }
             /*YOUR CODE*/            /*insert  the new sequence*/
            s.insert(t);
        }
        else if(command == "range_out")
        {
            int from=getValue(readVector());
            int to=getValue(readVector());
            set<vector<int>, mycompare>::iterator it;
            for(it=s.begin();it!=s.end();it++)
            {
                vector<int> cur = *it;
                int keyvalue=getValue(cur);
              /*if the key value of the sequence is in the range, print it*/
                if(keyvalue>=from&&keyvalue<=to) printVector(cur);
                else if(keyvalue > to) break;//because the key value is arranged
            }
        }
        else if(command == "output")
        {
            set<vector<int>, mycompare>::iterator it;
            for(it=s.begin();it!=s.end();it++)
            {
                vector<int> cur = *it;
                printVector(cur);
            }
        }
    }
    return 0;
}
