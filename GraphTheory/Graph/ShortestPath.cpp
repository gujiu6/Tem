/*
1.Dijkstra:非负边权图的单源最短路
2.Bellman‑Ford:允许负边权求单源最短路
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
