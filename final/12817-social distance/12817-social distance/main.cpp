//
//  main.cpp
//  12817-social distance
//
//  Created by 朱季葳 on 2021/6/23.
//

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
struct segment
{
    int left;
    int right;
    int mid;
    int min_dist;
    segment(int left,int right):left(left),right(right)
    {
        mid=(left+right)/2;
        min_dist=(right-left)/2;
    }
};
struct mycompare
{
    bool operator() (const segment& lhs, const segment& rhs) const
    {
        /* if(lhs.min_dist<rhs.min_dist||
           (lhs.min_dist==rhs.min_dist&&lhs.mid>rhs.mid))
            return false;//不能這樣搞...不知道內部機制是啥
        else
            return true;*/
         if(lhs.min_dist!=rhs.min_dist)
            return lhs.min_dist>rhs.min_dist;
        else
            return lhs.left<rhs.left;
    }
    
};
int n,m,s;//n=seats,m=students,s=social distance
set<segment,mycompare>seg;
vector<int>student_seat;//this vector only shows where the students 1~m are sit in
set<int>sitted_seat;//because the students may not sit according to their numbers
int main(int argc, const char * argv[])
{
    cin>>n>>m>>s;
    int t=m*2;
    char c;
    int x;
    int D=n+1;
    student_seat.resize(m+1);
    sitted_seat.insert(0);//wall-left
    sitted_seat.insert(n+1);//wall-right
    seg.insert(segment(0,n+1));
    while(t--)
    {
        cin>>c>>x;
        if(c=='i')
        {
            auto it=seg.begin();
            int mid=it->mid;
            int left=it->left;
            int right=it->right;
            seg.erase(it);
            if(left!=0)D=min(D, mid-left);
            if(right!=n+1)D=min(D,right-mid);
            seg.insert(segment(left,mid));
            seg.insert(segment(mid,right));
            student_seat[x]=mid;
            sitted_seat.insert(mid);
            
        }
        else if(c=='o')
        {
            auto it=sitted_seat.find(student_seat[x]);
            auto left_it=it;
            auto right_it=it;
            int left=*(--left_it);//不能共用一個拉！！
            int right=*(++right_it);
            seg.erase(segment(left,student_seat[x]));
            seg.erase(segment(student_seat[x], right));
            seg.insert(segment(left,right));
            sitted_seat.erase(it);
            student_seat[x]=-1;
            
        }
    }
    if(D<s)cout<<"NO"<<endl;
    else cout<<"YES"<<endl;
    if(D>=n+1)cout<<"INF"<<endl;
    else cout<<D<<endl;
    return 0;
}
