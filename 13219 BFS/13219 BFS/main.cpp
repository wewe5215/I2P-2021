//
//  main.cpp
//  13219 BFS
//
//  Created by 朱季葳 on 2021/6/4.
//

#include <iostream>
#include <queue>
#include <vector>
using namespace std;
queue<pair<int, int>>q;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};

int main(int argc, const char * argv[])
{
    int n,m=0;
    cin>>n>>m;
    vector<vector<int>>dist(n+2,vector<int>(m+2,100005));
    vector<vector<char>>map(n+2,vector<char>(m+2));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
            cin>>map[i][j];
    }
    int x,y,ex,ey;
    cin>>x>>y>>ex>>ey;
    dist[x][y]=0;//the start point
    q.push(pair<int, int>(x,y));
   // q.push((x,y)); not qualified
    while (q.size()) { //如果走到最後一個就會是0
        x=q.front().first;
        y=q.front().second;
        q.pop();
        for(int i=0;i<4;i++)
        {
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(dist[x][y]+1<dist[nx][ny]&&nx>0&&ny>0&&nx<=n&&ny<=m&&map[nx][ny]=='0')
            {
                dist[nx][ny]=dist[x][y]+1;
                q.push(pair<int, int>(nx,ny));
            }
        }
    }
    if(dist[ex][ey]==100005)cout<<"-1"<<endl;
    else cout<<dist[ex][ey]<<endl;
    return 0;
}
