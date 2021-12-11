//
//  main.cpp
//  co-sequence
//
//  Created by 朱季葳 on 2021/6/25.
//

#include <iostream>
#include <set>
#include <vector>
#include <queue>
using namespace std;
int main(int argc, const char * argv[]) {
    int n=0;
    cin>>n;
    while(n--)
    {
        vector<int>A(8),B(8);
        for(int i=0;i<8;i++)cin>>A[i];
        for(int i=0;i<8;i++)cin>>B[i];
        set<vector<int>>walked;
        queue<pair<vector<int>, int>>record;
        record.push(pair<vector<int>, int>(A,0));
        walked.insert(A);
        while (!record.empty())
        {
            vector<int>temp(8);
            int count;
            temp=record.front().first;
            count=record.front().second;
            if(temp==B)
            {
                cout<<count<<endl;
                break;
            }
            record.pop();
            vector<int>new_vec(8);
            //first type
            for(int i=0;i<8;i++)new_vec[i]=temp[(i+7)%8];
            if(walked.find(new_vec)==walked.end())
            {
                walked.insert(new_vec);
                record.push(pair<vector<int>, int>(new_vec,count+1));
            }
            //second type
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)new_vec[j]=temp[j];
                swap(new_vec[i],new_vec[(i+1)%8]);
                if(walked.find(new_vec)==walked.end())
                {
                    walked.insert(new_vec);
                    record.push(pair<vector<int>, int>(new_vec,count+1));
                }
            }
        }
        if(record.empty())cout<<"-1"<<endl;
    }
    
    return 0;
}
