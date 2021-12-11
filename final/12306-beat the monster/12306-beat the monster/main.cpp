//
//  main.cpp
//  12306-beat the monster
//
//  Created by 朱季葳 on 2021/6/23.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int L,HP,MHP,MDMG=0;
int level[20][20];//damage,heal
struct state
{
    int lv,hp,mhp;
    int rounds;
    state(int lv,int hp,int mhp,int rounds=0):lv(lv),hp(hp),mhp(mhp),rounds(rounds){}
};
queue<state>q;
bool d[20][305][405]={false};//level,hp,mhp
int main(int argc, const char * argv[])
{
    cin>>L>>HP>>MHP>>MDMG;
    for(int i=1;i<L+1;i++)
    {
        cin>>level[i][0]>>level[i][1];
    }
    q.push(state(1,HP,MHP));
    while(q.size())
    {
        state s=q.front();
        if(s.mhp==0)break;
        q.pop();
        //attack
        if(s.hp-MDMG>0||s.mhp-level[s.lv][0]<=0)//you kill the enemy first,so you don't have to care about the thing that you are killed or not
        {
            state temp(s.lv,max(s.hp-MDMG,0),max(s.mhp-level[s.lv][0],0),s.rounds+1);//the index can't be 0!!
            if(d[temp.lv][temp.hp][temp.mhp]==false)
            {
              d[temp.lv][temp.hp][temp.mhp]=true;
              q.push(temp);
            }
        }
        //heal
        if(s.hp+level[s.lv][1]-MDMG>=0)//if the enemy will kill you,if the answer is yes,then you don't have to walk this road anymore
        {
            state temp2(s.lv,min(s.hp+level[s.lv][1]-MDMG,HP-MDMG),s.mhp,s.rounds+1);//to prevent the hp exceed the maximum,and remember even though you have the full hp,you also need to subtract mdmg!!!!!
            if(d[temp2.lv][temp2.hp][temp2.mhp]==false)
            {
                d[temp2.lv][temp2.hp][temp2.mhp]=true;
                q.push(temp2);
            }
        }
        //level-up
        if(s.hp-MDMG>0&&s.lv+1<=L)
        {
            state temp3(s.lv+1,max(s.hp-MDMG,0),s.mhp,s.rounds+1);
            if(d[temp3.lv][temp3.hp][temp3.mhp]==false)
            {
                    d[temp3.lv][temp3.hp][temp3.mhp]=true;
                    q.push(temp3);

            }
            
        }
        
    }
    if(q.empty())cout<<"-1"<<endl;
    else cout<<q.front().rounds<<endl;
    return 0;
}
