//
//  main.cpp
//  15puzzle
//
//  Created by 朱季葳 on 2021/6/24.
//

#include <iostream>
#include <queue>
#include <cmath>
using namespace std;
int puzzle[4][4];
int road_row[16]={-1,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3};//橫列
int road_col[16]={-1,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2};
class state
{
public:
    int puzzle[4][4];
    int g;
    int h;
    int empty_x;
    int empty_y;
    int move_direction;
    state(int puzzle[4][4])
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                this->puzzle[i][j]=puzzle[i][j];
            }
        }
        empty_x=-1;
        empty_y=-1;
        move_direction=-1;
        g=0;
        setH();
    }
    state(const state& s)
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                this->puzzle[i][j]=s.puzzle[i][j];
            }
        }
        empty_x=s.empty_x;
        empty_y=s.empty_y;
        move_direction=s.move_direction;
        g=s.g;
        h=s.h;
        
    }
    void setH()
    {
        //Manhattan distance+linear diatance*2
        int M_D=0;
        int L_C=0;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(puzzle[i][j]!=0)
                {
                    M_D+=abs(road_row[puzzle[i][j]]-i);
                    M_D+=abs(road_col[puzzle[i][j]]-j);
               
                if(road_row[puzzle[i][j]]==i)//same row
                {
                    for(int k=j;k<4;k++)
                    {
                        {
                        if(puzzle[i][k]!=0&&puzzle[i][j]>puzzle[i][k]&&road_row[puzzle[i][k]]==i)
                            L_C++;
                        }
                    }
                }
                if(road_col[puzzle[i][j]]==j)
                {
                    for(int k=i;k<4;k++)
                    {
                        if(puzzle[k][j]!=0&&puzzle[i][j]>puzzle[k][j]&&road_col[puzzle[k][j]]==j)
                            L_C++;
                    }
                }
                    
                }
            }
        }
        h=M_D+L_C*2;
        
    }
    void update(int direction,int newx,int newy)
    {
        this->move_direction=direction;
        swap(puzzle[empty_x][empty_y], puzzle[newx][newy]);
        this->empty_x=newx;
        this->empty_y=newy;
        g++;
        setH();
    }
    bool operator<(const state& rhs)const
    {
        return g+h>rhs.g+rhs.h;//靠北喔大於小於不要打錯拉幹
    }
    
};
int main(int argc, const char * argv[])
{
    int ex=0;
    int ey=0;
    int puzzle[4][4];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            cin>>puzzle[i][j];
            
        }
    }
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(!puzzle[i][j])
                {
                    ex=i;
                    ey=j;
                }

        }
    }
    
    state s(puzzle);
    s.empty_x=ex;
    s.empty_y=ey;
    priority_queue<state>pq;
    pq.push(s);
    const int dx[4]={0,0,1,-1};
    const int dy[4]={1,-1,0,0};
    while(!pq.empty())
    {
        state pre=pq.top();
       
        if(pre.h==0)
        {
            cout<<pre.g<<endl;
            break;
        }
        pq.pop();
        if(pre.g+pre.h>80)continue;
        int new_ex=0;
        int new_ey=0;
        for(int i=0;i<4;i++)
        {
            new_ex=pre.empty_x+dx[i];
            new_ey=pre.empty_y+dy[i];
        
            if(new_ex<0||new_ex>3||new_ey<0||new_ey>3)continue;
            if(i==(pre.move_direction^1))continue;
            state new_state=pre;
            new_state.update(i, new_ex, new_ey);
            
            pq.push(new_state);
            
        }
        
        
    }
    if(pq.empty())cout<<-1<<endl;
    return 0;
}
