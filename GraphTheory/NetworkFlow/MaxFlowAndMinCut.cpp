/*                      时间复杂度       空间复杂度
1.Dinic最大流最小割       O(V^2E)        O(V+E)
2.SPFA最小费用最大流
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

//1.Dinic最大流最小割
template <class T = i64>
class Flow {
public:
    struct E {
        int v, rev;//v:转移目标状态;rev:反向边编号
        T cap;//剩余容量
    };
    int n;
    vector<vector<E>> edges;
    vector<int> h, cur;//h:Dinic层次图中的距离标号,cur:每个点尚未尝试的第一条残量边下标
    Flow(int n = 0): n(n), edges(n + 1), h(n + 1), cur(n + 1) {}
    //添加有向边u->v,容量c
    int add(int u, int v, T c) {
        int id = edges[u].size();
        edges[u].push_back({v, (int)edges[v].size(), c});
        edges[v].push_back({u, id, 0});
        return id;
    }
    //BFS建立层次图
    bool bfs(int s, int t) {
        fill(h.begin(), h.end(), -1);
        queue<int> q;
        h[s] = 0;
        q.push(s);
        while(!q.empty()) {
            auto u = q.front(); q.pop();
            for(const auto &e : edges[u]) {
                if(e.cap > 0 && h[e.v] == -1) {
                    h[e.v] = h[u] + 1;
                    q.push(e.v);
                }
            }
        }
        return h[t] != -1;
    }
    //DFS增广
    T dfs(int u, int t, T f) {
        if(u == t) return f;
        T ans = 0;
        for(int &i = cur[u]; i < edges[u].size(); i++) {
            auto &e = edges[u][i];
            if(e.cap == 0 || h[e.v] != h[u] + 1) {
                continue;
            }
            T d = dfs(e.v, t, min(f - ans, e.cap));
            e.cap -= d;
            edges[e.v][e.rev].cap += d;
            ans += d;
            if(ans == f) break;
        }
        return ans;
    }
    //最大流
    T flow(int s, int t, T lim = numeric_limits<T>::max()) {
        T ans = 0;
        while(ans < lim && bfs(s, t)) {
            fill(cur.begin(), cur.end(), 0);
            ans += dfs(s, t, lim - ans);
        }
        return ans;
    }
    //最大流结束后,返回残量网络中从s可达的点集,即最小割的源点
    vector<bool> cut(int s) const {
        vector<bool> vis(n + 1);
        queue<int> q;
        vis[s] = true;
        q.push(s);
        while(!q.empty()) {
            auto u = q.front(); q.pop();
            for(const auto &e : edges[u]) {
                if(e.cap > 0 && !vis[e.v]) {
                    vis[e.v] = true;
                    q.push(e.v);
                }
            }
        }
        return vis;
    }
};

//2.SPFA最小费用最大流
template <class T = i64, class Cost = i64>
struct SpfaCostFlow {
    struct E {
        int v, rev;
        T cap;
        Cost cost;     // 单位流量费用
    };
    int n;
    vector<vector<E>> edges;
    vector<optional<Cost>> d;// 是本轮从源点出发的最短距离,空值表示不可达
    vector<int> in, cur, vis;

    SpfaCostFlow(int n = 0) : n(n + 1), edges(n + 1), d(n + 1), in(n + 1), cur(n + 1), vis(n + 1) {}
    void add(int u, int v, T cap, Cost cost) {
        int id = edges[u].size();
        int rev = edges[v].size() + (u == v);
        edges[u].push_back({v, rev, cap, cost});
        edges[v].push_back({u, id, 0, -cost});
    }

    bool shortest(int s, int t) {
        fill(d.begin(), d.end(), nullopt);
        fill(in.begin(), in.end(), 0);
        queue<int> q;
        d[s] = 0;
        q.push(s);
        in[s] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            in[u] = 0;
            for (const auto &e : edges[u]) {
                if (e.cap == 0) {
                    continue;
                }
                auto nd = *d[u] + e.cost;
                if (!d[e.v].has_value() || nd < *d[e.v]) {
                    d[e.v] = nd;
                    if (!in[e.v]) {
                        q.push(e.v);
                        in[e.v] = 1;
                    }
                }
            }
        }
        return d[t].has_value();
    }

    T dfs(int u, int t, T lim) {
        if (u == t) {
            return lim;
        }
        vis[u] = 1;
        T f = 0;
        for (int &i = cur[u]; i < (int)edges[u].size() && f < lim; i++) {
            auto &e = edges[u][i];
            if (e.cap == 0 || vis[e.v] || !d[e.v].has_value() || *d[u] + e.cost != *d[e.v]) {
                continue;
            }
            T x = dfs(e.v, t, min(lim - f, e.cap));
            e.cap -= x;
            edges[e.to][e.rev].cap += x;
            f += x;
        }
        vis[u] = 0;
        return f;
    }

    pair<T, Cost> flow(int s, int t, T lim = numeric_limits<T>::max()) {
        // s、t 是源汇点,lim 是最多发送的流量,返回实际流量与最小费用.
        if (s == t) {
            return {0, 0};
        }
        T f = 0;
        Cost cost = 0;
        while (f < lim && shortest(s, t)) {
            fill(cur.begin(), cur.end(), 0);
            fill(vis.begin(), vis.end(), 0);
            T x = dfs(s, t, lim - f);
            if (x == 0) break;
            f += x;
            cost += (Cost)x * (*d[t]);
        }
        return {f, cost};
    }
};