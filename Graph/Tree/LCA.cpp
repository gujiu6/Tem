#include <bits/stdc++.h>
using namespace std;
const int MAXX = 5e5+10, LIMIT = 20;



namespace BinaryLifting {

int cnt, lg2, n;
array<int,MAXX> h, deep;
array<int,MAXX << 1> nxt, to, wei;
array<array<int, LIMIT>, MAXX> stjump;

void build(){
    cnt = 1;
    lg2 = __lg(n);
    fill(h.begin(), h.begin() + n + 1, 0);
    fill(deep.begin(), deep.begin() + n + 1, 0);
}

void addEdge(int u, int v, int w = 0){
    nxt[cnt] = h[u];
    to[cnt] = v;
    wei[cnt] = w;
    h[u] = cnt++;
}

void dfs(int u, int f){
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    for(int p = 1; p <= lg2; p++){
        int mid = stjump[u][p - 1];
        stjump[u][p] = stjump[mid][p - 1];
    }
    for(int ei = h[u], v;ei > 0; ei = nxt[ei]){
        v = to[ei];
        if(v == f) continue;
        dfs(v, u);
    }
}

int lca(int a, int b){
    if(deep[a] < deep[b]) swap(a, b);
    for(int p = lg2; p >= 0; p--){
        if(deep[stjump[a][p]] >= deep[b]){
            a = stjump[a][p];
        }
    }
    if(a == b) return a;
    for(int p = lg2; p >= 0; p--){
        if(stjump[a][p] != stjump[b][p]){
            a = stjump[a][p];
            b = stjump[b][p];
        }
    }
    return stjump[a][0];
}

int dist(int u, int v) {
    return deep[u] + deep[v] - 2 * deep[lca(u, v)];
}

}

namespace Tarjan {

int cnt, n, m;
array<int, MAXX> h, fa, vis;
array<int, MAXX << 1> nxt, to, wei;
vector<vector<array<int, 2>>> Question(MAXX);
vector<int> lca;

void build(){
    cnt = 1;
    fill(h.begin(), h.begin() + n + 1, 0);
    fill(vis.begin(), vis.begin() + n + 1, 0);
    fill(lca.begin(), lca.begin() + m + 1, 0);
    for(int i = 1; i <= n; i++) 
        fa[i] = i;
}

void addEdge(int u, int v, int w=0){
    nxt[cnt] = h[u];
    to[cnt] = v;
    wei[cnt] = w;
    h[u] = cnt++;
}

int find(int i){
    if(i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

void tarjan(int u, int f){
    vis[u] = 1;
    for(int ei = h[u], v; ei > 0; ei = nxt[ei]){
        v = to[ei];
        if(v != f){
            tarjan(v, u);
            fa[v] = u;
        }
    }
    for(auto [v, id] : Question[u]){
        if(vis[v]){
            lca[id] = find(v);
        }
    }
}

}