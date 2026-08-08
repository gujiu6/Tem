#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int MAXX = 5e5+10, INF = 1e9+7;

//1.树的直径、重心、中心
struct Dia {
    //dist:最短距离或当前路径长度,path:当前首选路径的聚合和
    i64 dist;
    vector<int> path;
};
struct MEdge {
    int v;
    i64 w = 0;
};
//1.1直径:树上最远的两个点
Dia treeDiameter(const vector<vector<MEdge>>& g) {
    //返回树直径长度及路径
    int n = g.size() - 1;
    if(n <= 0) {
        return {0, {}};
    }
    auto far = [&](int s) {
        vector<int> p(n + 1, -1), st{s};
        vector<i64> d(n + 1, -1);
        d[s] = 0;
        while(!st.empty()) {
            int u = st.back();
            st.pop_back();
            for(auto &e : g[u]) {
                if(e.v == p[u]) continue;
                p[e.v] = u;
                d[e.v] = d[u] + e.w;
                st.push_back(e.v);
            }
        }
        int u = max_element(d.begin() + 1, d.end()) - d.begin();
        return tuple{u, move(p), move(d)};
    };
    auto [s, p0, d0] = far(1);
    auto [t, p, d] = far(s);
    vector<int> path;
    for(int u = t; u != -1; u = p[u]) {
        path.push_back(u);
    }
    reverse(path.begin(), path.end());
    return {d[t], path};
}
//1.2重心:删除后最大块最小
vector<int> treeCentroids(const vector<vector<MEdge>>& g) {
    //返回树的一个或两个重心编号
    int n = g.size() - 1;
    vector<int> sz(n + 1), ans;
    auto dfs = [&](auto &&self, int u, int f)->void {
        sz[u] = 1;
        int mx = 0;
        for(auto &e: g[u]) {
            if(e.v == f) continue;
            self(self, e.v, u);
            sz[u] += sz[e.v];
            mx = max(mx, sz[e.v]);
        }
        mx = max(mx, n - sz[u]);
        if(2 * mx <= n) {
            ans.push_back(u);
        }
    };
    if(n) dfs(dfs, 1, 0);
    return ans;
}
//1.3中心:离所有点距离最均衡
vector<int> treeCenters(const vector<vector<MEdge>>& g) {
    int n = g.size() - 1;
    if(n <= 2) {
        vector<int> ans;
        for(int i = 1; i <= n; i++) {
            ans.push_back(i);
        }
        return ans;
    }
    vector<int> deg(n + 1);
    queue<int> q;
    for(int i = 1; i <= n; i++) {
        deg[i] = g[i].size();
        if(deg[i] == 1) {
            q.push(i);
        }
    }
    int left = n;
    while(left > 2) {
        int sz = q.size();
        left -= sz;
        while(sz--) {
            int u = q.front(); q.pop();
            for(auto &e : g[u]) {
                if(--deg[e.v] == 1) {
                    q.push(e.v);
                }
            }
        }
    }
    vector<int> ans;
    while(!q.empty()) {
        ans.push_back(q.front());
        q.pop();
    }
    return ans;
}
