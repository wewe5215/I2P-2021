//
//  main.cpp
//  13221 bfs-increasing
//
//  Created by 朱季葳 on 2021/6/4.
//

#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int n,m;
queue<pair<int, int>>q;
int main(int argc, const char * argv[]) {
    cin>>n>>m;
    vector<vector<int>>dist(n+1,vector<int>(m+1,100005));
    vector<vector<int>>grid(n+1,vector<int>(m+1));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>grid[i][j];
        }
    }
    int x,y,x2,y2;
    cin>>x>>y>>x2>>y2;
    dist[x][y]=0;
    q.push(pair<int, int>(x,y));
    while(!q.empty())
    {
        x=q.front().first;
        y=q.front().second;
        q.pop();
        //(1,0)
        if(x+1>=1&&x+1<=n&&y>=1&&y<=m&&dist[x][y]+1<dist[x+1][y]&&grid[x+1][y]>=grid[x][y])
        {
            dist[x+1][y]=dist[x][y]+1;
            q.push(pair<int, int>(x+1,y));
        }
        if(x-1>=1&&x-1<=n&&y>=1&&y<=m&&dist[x][y]-1<dist[x-1][y]&&grid[x-1][y]>=grid[x][y])
        {
            dist[x-1][y]=dist[x][y]+1;
            q.push(pair<int, int>(x-1,y));
        }
        if(x>=1&&x<=n&&y+1>=1&&y+1<=m&&dist[x][y]+1<dist[x][y+1]&&grid[x][y+1]>=grid[x][y])
        {
            dist[x][y+1]=dist[x][y]+1;
            q.push(pair<int, int>(x,y+1));
        }
        if(x>=1&&x<=n&&y-1>=1&&y-1<=m&&dist[x][y]+1<dist[x][y-1]&&grid[x][y-1]>=grid[x][y])
        {
            dist[x][y-1]=dist[x][y]+1;
            q.push(pair<int, int>(x,y-1));
        }
        
    }
    if(dist[x2][y2]==100005)cout<<"-1"<<endl;
    else cout<<dist[x2][y2]<<endl;
    return 0;
}
