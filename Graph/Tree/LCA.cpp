#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int MAXX = 5e5+10, LIMIT = 20;



namespace BinaryLifting {

struct MEdge {
    int v;
    i64 w = 0;
};
int lg2, n;
array<int, MAXX> deep;
array<array<int, MAXX>, LIMIT> stjump;
vector<vector<MEdge>> g(MAXX);
void build(){
    lg2 = __lg(n);
    fill(deep.begin(), deep.begin() + n + 1, 0);
}

void dfs(int u, int f){
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    for(int p = 1; p <= lg2; p++){
        int mid = stjump[p - 1][u];
        stjump[p][u] = stjump[p - 1][mid - 1];
    }
    for(auto &[v, w] : g[u]){
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

struct MEdge {
    int v;
    i64 w;
};
vector<int> Tarjan(const vector<vector<MEdge>>& g, const vector<vector<pair<int, int>>> &q) {
    int n = g.size() - 1, m = q.size() - 1;
    vector<int> lca(m + 1);
    vector<bool> vis(n + 1);
    vector<int> fa(n + 1);
    iota(fa.begin(), fa.end(), 0);
    auto find = [&](auto && self, int i)->int {
        if(i != fa[i]) {
            fa[i] = self(self, fa[i]);
        }
        return fa[i];
    };
    auto tarjan = [&](auto &&self, int u, int f)->void {
        vis[u] = 1;
        for(auto &[v, w] : g[u]){
            if(v != f){
                self(self, v, u);
                fa[v] = u;
            }
        }
        for(auto [v, id] : q[u]){
            if(vis[v]){
                lca[id] = find(find, v);
            }
        }
    };
    tarjan(tarjan, 1, 0);
}

}