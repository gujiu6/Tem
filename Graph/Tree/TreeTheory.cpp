#include <bits/stdc++.h>
using namespace std;
const int MAXX=5e5+10, INF=1e9+7;


namespace Centre {

int n, cnt, best;
array<int,MAXX> h, sz, maxsub;
array<int,MAXX> to, nxt;
vector<int> ans;
void build(){
    cnt = 1;
    best = INF;
    fill(h.begin(), h.begin() + n + 1, 0);
}

void addEdge(int u,int v){
    nxt[cnt] = h[u];
    to[cnt] = v;
    h[u] = cnt++;
}

//第一种求法
void dfs1(int u, int f){
    sz[u] = 1;
    maxsub[u] = 0;
    for(int ei = h[u], v; ei > 0; ei = nxt[ei]){
        v = to[ei];
        if(v != f){
            dfs1(v, u);
            sz[u] += sz[v];
            maxsub[u] = max(maxsub[u], sz[v]);
        }
    }
    maxsub[u] = max(maxsub[u], n - sz[u]);
}
void calc(){
    for(int i = 1; i <= n; i++){
        if(maxsub[i] <= n / 2){
            ans.push_back(i);
        }
    }
}

//第二种求法
void dfs2(int u, int f){
    sz[u] = 1;
    int maxsub = 0;
    for(int ei = h[u], v; ei > 0; ei = nxt[ei]){
        v = to[ei];
        if(v != f){
            dfs2(v, u);
            sz[u] += sz[v];
            maxsub=max(maxsub, sz[v]);
        }
    }
    maxsub = max(maxsub, n - sz[u]);
    if(maxsub < best){
        ans.resize(1, u);
    }
    else if(maxsub == best){
        ans.push_back(u);
    }
}

}

namespace Diameter {

array<int, MAXX> h, last, dist;
array<int, MAXX << 1> to, nxt, wei;
int n, cnt, diameter;
void build(){
    cnt = 1;
    diameter = 0;
    fill(h.begin(), h.begin() + n + 1, 0);
}
void addEdge(int u, int v, int w){
    nxt[cnt] = h[u];
    to[cnt] = v;
    wei[cnt] = w;
    h[u] = cnt++;
}

//两遍dfs版本
void dfs(int u,int f,int w){
    last[u] = f;
    dist[u] = dist[f] + w;
    for(int ei = h[u], v ; ei > 0; ei = nxt[ei]){
        v = to[ei];
        if(v != f){
            dfs(v, u, wei[ei]);
        }
    }
}
array<int,3> road(){
    dfs(1, 0, 0);
    int st = 1, ed = 1, dis;
    for(int i = 2; i <= n; i++){
        if(dist[i] > dist[st]){
            st = i;
        }
    }
    dfs(st, 0, 0);
    for(int i = 2; i <= n; i++){
        if(dist[i] > dist[ed]){
            ed = i;
        }
    }
    dis = dist[ed];
    return {st, ed, dis};
}

//树上dp
void dp(int u,int f){
    for(int ei = h[u], v; ei > 0; ei = nxt[ei]){
        v = to[ei];
        if(v != f){
            dp(v, u);
        }
    }
    for(int ei = h[u], v; ei > 0; ei = nxt[ei]){
        v = to[ei];
        if(v != f){
            diameter = max(diameter, dist[u] + dist[v] + wei[ei]);
            dist[u] = max(dist[u], dist[v] + wei[ei]);
        }
    }
}

}


