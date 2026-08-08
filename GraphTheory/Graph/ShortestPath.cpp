/*
1.Dijkstra:非负边权图的单源最短路
2.Bellman‑Ford:允许负边权求单源最短路
3.SPFA,SLF优化与负环判定/输出
*/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using i64 = long long;
const i64 INF = 1e18;
struct WEdge {int v;i64 w = 0;};struct DEdge {int u, v;i64 w = 0;};struct Edge {int v;};

//1.Dijkstra:非负边权图的单源最短路
vector<i64> Dijkstra(const vector<vector<WEdge>>& g, int s = 1) {
    //s:源点;返回源点到各点最短距离,不可达点为INF
    int n = g.size() - 1;
    vector<i64> d(n + 1, INF);
    priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<>> q;
    d[s] = 0;
    q.push({0, s});
    while(!q.empty()) {
        auto [du, u] = q.top(); q.pop();
        if(du != d[u]) continue;
        for(auto &e : g[u]) {
            assert(e.w >= 0);
            if(d[e.v] < du + e.w) {
                d[e.v] = du + e.w;
                q.push({d[e.v], e.v});
            }
        }
    }
    return d;
}

//2.Bellman‑Ford:允许负边权求单源最短路
pair<vector<i64>, vector<int>>BellmanFord(int n, const vector<DEdge>& edge, int s) {
    //返回源点最短路;cycle非空表示存在从s可达的负环,返回其中一组环上顶点
    vector<i64> d(n + 1, INF);
    vector<int> p(n + 1, -1);
    d[s] = 0;
    int x = -1;
    for(int z = 1; z <= n; z++) {
        x = -1;
        for(const auto &[u, v, w] : edge) {
            if(d[u] == INF) continue;
            i64 nd = d[u] + w;
            if(nd < d[v]) {
                d[v] = nd;
                p[v] = u;
                x = v;
            }
        }
    }
    vector<int> cycle;
    if(x != -1) {
        for(int i = 1; i <= n; i++) {
            x = p[x];
        }
        int y = x;
        do {
            cycle.push_back(y);
            y = p[y];
        }while(y != x);
        reverse(cycle.begin(), cycle.end());
    }
    return {d, cycle};
}

//3.SPFA,SLF优化与负环判定/输出
optional<vector<i64>> SPFA(const vector<vector<WEdge>>& g, int s) {
    int n = g.size() - 1;
    vector<i64> d(n + 1, INF);
    //in:是否在队列里面,len:当前最短路经过的边数
    vector<int> in(n + 1), len(n + 1);
    queue<int> q;
    d[s] = 0;
    q.push(s);
    in[s] = 1;
    while(!q.empty()) {
        auto u = q.front(); q.pop();
        in[u] = 0;
        for(const auto &e : g[u]) {
            i64 nd = e.w + d[u];
            if(d[e.v] <= nd) continue;
            d[e.v] = nd;
            len[e.v] = len[u] + 1;
            //超过n-1条边,一定有负环
            if(len[e.v] >= n) return nullopt;
            if(!in[e.v]) {
                q.push(e.v);
                in[e.v] = 1;
            }
        }
    }
    return d;
}