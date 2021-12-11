//
//  main.cpp
//  co-board
//
//  Created by 朱季葳 on 2021/6/25.
//

#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

int main(int argc, const char * argv[])
{
    int T;
    cin>>T;
    while(T--)
    {
        vector<int>A(8),B(8);
        set<vector<int>>walked;//to prevent from counting too many times
        queue<pair<vector<int>, int>>record;
        cin>>A[0]>>A[1]>>A[2]>>A[7]>>A[3]>>A[6]>>A[5]>>A[4];
        cin>>B[0]>>B[1]>>B[2]>>B[7]>>B[3]>>B[6]>>B[5]>>B[4];
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
            //move
            for(int i=0;i<8;i++)
            {
                new_vec[i]=temp[(i+7)%8];//+1-->counterclockwise
            }
            if(walked.find(new_vec)==walked.end())
            {
                walked.insert(new_vec);
                record.push(pair<vector<int>, int>(new_vec,count+1));
            }
            //隔壁
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)new_vec[j]=temp[j];
                swap(new_vec[i], new_vec[(i+1)%8]);
                if(walked.find(new_vec)==walked.end())
                {
                    walked.insert(new_vec);
                    record.push(pair<vector<int>, int>(new_vec,count+1));
                }
            }
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)new_vec[j]=temp[j];
                swap(new_vec[i], new_vec[(i+4)%8]);
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
