#include <bits/stdc++.h>
using namespace std;
using i64 = long long;


template <class T = int>
class Flow {
public:
    struct E {
        int to, rev;//to:转移目标状态;rev:反向边编号
        T cap;//剩余容量
    };
    int n;//残量网络点数
    vector<vector<E>> e;//每个点发出的残量边
    vector<int> h, cur;//h:Dinic层次图中的距离标号,cur:每个点尚未尝试的第一条残量边下标
    Flow(int n = 0): n(n), e(n + 1), h(n + 1), cur(n + 1) {}
    //添加有向边u->v,容量c
    int add(int u, int v, T c) {
        int id = e[u].size();
        e[u].push_back({v, (int)e[v].size(), c});
        e[v].push_back({u, id, 0});
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
            for(const auto &[v, r, c] : e[u]) {
                if(c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    q.push(v);
                }
            }
        }
        return h[t] != -1;
    }
    //DFS增广
    T dfs(int u, int t, T f) {
        if(u == t) return f;
        T ans = 0;
        for(int &i = cur[u]; i < e[u].size(); i++) {
            auto &a = e[u][i];
            if(a.cap == 0 || h[a.to] != h[u] + 1) {
                continue;
            }
            T d = dfs(a.to, t, min(f - ans, a.cap));
            a.cap -= d;
            e[a.to][a.rev].cap += d;
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
            for(const auto &[v, r, c] : e[u]) {
                if(c > 0 && !vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        return vis;
    }
};