//适用于小图,解决有负边(无负环)的单源最短路问题(SPFA优化)
#include <bits/stdc++.h>
using namespace std;
const int MAXX = 1005;
const int INF = 1e9+7;

int cnt;
array<int, MAXX> h;
array<int, MAXX << 1> nxt, to, wei;
vector<int> dis(MAXX, INF), updateCnt(MAXX), enter(MAXX);

void build(int n){
    cnt = 1;
    fill(h.begin(), h.begin() + n + 1, 0);
    enter.assign(MAXX, 0);
    updateCnt.assign(MAXX, 0);
    dis.assign(MAXX, INF);
}

void addEdge(int u, int v, int w=0){
    nxt[cnt] = h[u];
    to[cnt] = v;
    wei[cnt] = w;
    h[u] = cnt++;
}



bool Spfa(int n){
    dis[1] = 0;
    updateCnt[1]++;
    queue<int> q;
    q.push(1);
    enter[1] = 1;
    while(!q.empty()){
        int u = q.front(); q.pop();
        enter[u] = 0;
        for(int ei = h[u]; ei > 0; ei = nxt[ei]){
            int v = to[ei], w = wei[ei];
            if(dis[u] + w < dis[v]){
                dis[v] = dis[u] + w;
                if(!enter[v]){
                    if(updateCnt[v]++ == n){
                        return 0;//有负环
                    }
                    q.push(v);
                    enter[v] = 1;
                }
            }
        }
    }
    return 1;//没有负环
}









