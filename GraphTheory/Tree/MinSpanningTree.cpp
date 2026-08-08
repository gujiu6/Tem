/*
1.最小生成树
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int MAXX = 2e5+10;
constexpr i64 INF = 1e18;



//1.最小生成树
namespace MinSpanningTree {
class DSU {
private:
    int n;
    vector<int> fa,sz;
public:
    DSU(int n) : n(n), fa(n + 1), sz(n + 1, 1) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int i){
        if(fa[i] != i){
            fa[i] = find(fa[i]);
        }
        return fa[i];
    }

    bool same(int x, int y){
        return find(x) == find(y);
    }

    bool merge(int x, int y){
        x = find(x), y = find(y);
        if(x == y) return false;
        if(sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
        return true;
    }
    int size(int x){
        return sz[find(x)];
    }
};
struct Edge {
    int u, v;
    i64 w;
};
optional<pair<i64, vector<Edge>>> KrusKal(vector<Edge> edge, int n) {
    sort(edge.begin(), edge.end(), [](const Edge& a, const Edge& b){
        return a.w < b.w;
    });
    DSU d(n);
    vector<Edge> use;
    i64 ans = 0;
    for(auto &e : edge) {
        if(!d.merge(e.u, e.v)) continue;
        ans += e.w;
        use.push_back(e);
    }
    if(use.size() + 1 != n && n) {
        return nullopt;
    }
    return pair{ans, use};
}

optional<i64> Prim(vector<vector<pair<int, i64>>>&g) {
    int n = g.size() - 1;
    vector<i64> dis(n + 1, INF);
    vector<bool> vis(n + 1);
    priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<pair<i64, int>>> q;
    dis[1] = 0;
    q.push({0, 1});
    i64 ans = 0;
    int cnt = 0;
    while(!q.empty()) {
        auto [w, u] = q.top();
        q.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        cnt++;
        ans += w;
        for(auto [v, ww] : g[u]) {
            if(!vis[v] && ww < dis[v]) {
                dis[v] = ww;
                q.push({ww, v});
            }
        }
    }
    if(cnt != n) {
        return nullopt;
    }
    return ans;
}
}




