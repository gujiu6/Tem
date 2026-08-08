/*                                    时间复杂度       空间复杂度
1.Dijkstra:非负边权图的单源最短路        O((n+m)logn)    O(n+m)      
2.Bellman‑Ford:允许负边权求单源最短路    O(nm)           O(n+m)
3.SPFA,SLF优化与负环判定/输出           O(m)            O(n+m)
4.Floyd与最小环                       O(n^3)          O(n^2)
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

//3.SPFA+SLF优化与负环判定/输出
optional<vector<i64>> SPFA(const vector<vector<WEdge>>& g, int s) {
    //存在在源点可达负环时返回空
    int n = g.size() - 1;
    vector<i64> d(n + 1, INF);
    //in:是否在队列里面,len:当前最短路经过的边数
    vector<int> in(n + 1), len(n + 1);
    deque<int> q;
    d[s] = 0;
    q.push_back(s);
    in[s] = 1;
    while(!q.empty()) {
        auto u = q.front(); q.pop_front();
        in[u] = 0;
        for(const auto &e : g[u]) {
            i64 nd = e.w + d[u];
            if(d[e.v] <= nd) continue;
            d[e.v] = nd;
            len[e.v] = len[u] + 1;
            //超过n-1条边,一定有负环
            if(len[e.v] >= n) return nullopt;
            if(!in[e.v]) {
                //SLF优化
                if(!q.empty() && d[e.v] < d[q.front()]) {
                    q.push_front(e.v);
                }
                else {
                    q.push_back(e.v);
                }
                in[e.v] = 1;
            }
        }
    }
    return d;
}

//4.Floyd与最小环
void Floyd(vector<vector<i64>>& d) {
    //不可达位置为INF
    int n = d.size() - 1;
    for(int k = 1;k <= n; k++){
        for(int i = 1;i <= n; i++){
            if(d[i][k] == INF) continue;
            for(int j = 1; j <= n; j++){
                if(d[k][j] == INF) continue;
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}
//非负无向最小环
i64 minCycle(const vector<vector<i64>> &dis, bool f = 1) {
    //f: 0:有向图, 1: 无向图
    int n = dis.size() - 1;
    i64 ans = INF;
    auto d = dis;
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i < k; i++) {
            if(f) {
                for(int j = i + 1; j < k; j++) {
                    if(d[i][j] != INF && dis[i][k] != INF && dis[k][j] != INF) {
                        ans = min(ans, d[i][j] + dis[i][k] + dis[k][j]);
                    }
                }
            }
            else {
                for(int j = 1; j < k; j++) {
                    if(i == j) continue;
                    if(d[i][j] != INF && dis[j][k] != INF && dis[k][i] != INF) {
                        ans = min(ans, d[i][j] + dis[j][k] + dis[k][i]);
                    }
                }
            }
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(d[i][k] != INF && d[k][j] != INF) {
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }
    return ans;
}