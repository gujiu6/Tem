/*                                 时间复杂度             空间复杂度
1.匈牙利算法                         O(VE)                O(V+E)
2.bitset优化匈牙利                   O(n^2m/64)           O(nm)
3.Hopcroft‑Karp                    O(E*sqrt(V))         O(V+E)
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using ui64 = unsigned long long;
struct WEdge {int v;i64 w = 0;};struct DEdge {int u, v;i64 w = 0;};struct Edge {int v;};


//1.匈牙利算法
tuple<int, vector<int>, vector<int>> Hungarian(const vector<vector<Edge>>& g, int nl, int nr) {
    vector<int> ml(nl + 1, -1), mr(nr + 1, -1), vis(nr + 1);
    int tim = 0;
    auto dfs = [&](auto &&self, int u)->bool {
        //u是尝试增广的左点;找到增广路并改写匹配时返回true
        for(const auto &e : g[u]) {
            if(vis[e.v] == tim) continue;
            vis[e.v] = tim;
            if(mr[e.v] == -1 || self(self, mr[e.v])) {
                ml[u] = e.v;
                mr[e.v] = u;
                return true;
            }
        }
        return false;
    };
    int ans = 0;
    for(int u = 1; u <= nl; u++) {
        ++tim;
        if(dfs(dfs, u)) {
            ans++;
        }
    }
    return {ans, ml, mr};
}

//2.bitset优化匈牙利
//建图g[u][(v-1)/64]|=1ULL<<((v-1)%64);
tuple<int, vector<int>, vector<int>> BitsetHungarian(const vector<vector<ui64>>& g, int nl, int nr) {
    int w = (nr + 64 - 1) / 64;
    vector<int> ml(nl + 1, -1), mr(nr + 1, -1);
    vector<ui64> vis(w);
    auto dfs = [&](auto &&self, int u)->bool {
        for(int b = 0; b < w; b++) {
            auto x = g[u][b] & ~vis[b];
            while(x) {
                int k = countr_zero(x);
                x &= x - 1;
                int v = b * 64 + k + 1;
                if(v > nr) continue;
                vis[b] |= 1ULL << k;
                if(mr[v] == -1 || self(self, mr[v])) {
                    ml[u] = v;
                    mr[v] = u;
                    return true;
                }
            }
        }
        return false;
    };
    int ans = 0;
    for(int u = 1; u <= nl; u++) {
        fill(vis.begin(), vis.end(), 0);
        if(dfs(dfs, u)) {
            ans++;
        }
    }
    return {ans, ml, mr};
}

//3.Hopcroft‑Karp
tuple<int, vector<int>, vector<int>> HopcroftKarp(const vector<vector<Edge>>& g, int nl, int nr) {
    vector<int> ml(nl + 1, -1), mr(nr + 1, -1), dep(nl + 1, -1);
    // 对交替图分层，寻找最短增广路
    auto bfs = [&]()->bool {
        queue<int> q;
        fill(dep.begin(), dep.end(), -1);
        // 所有未匹配左点作为 BFS 起点
        for(int u = 1; u <= nl; u++) {
            if(ml[u] == -1) {
                dep[u] = 0;
                q.push(u);
            }
        }
        bool ok = false;
        while(!q.empty()) {
            auto u = q.front();q.pop();
            for(const auto &e : g[u]) {
                int x = mr[e.v];
                // v 是未匹配右点
                if(x == -1) ok = true;
                else if(dep[x] == -1) {
                    dep[x] = dep[u] + 1;
                    q.push(x);
                }

            }
        }
        return ok;
    };
     //沿BFS分出的层次寻找最短增广路
    auto dfs = [&](auto &&self, int u)->bool {
        for(const auto &e : g[u]) {
            int x = mr[e.v];
            // v 未匹配, 或者可以沿着下一层继续寻找
            if(x == -1 || (dep[x] == dep[u] + 1 && self(self, x))) {
                ml[u] = e.v;
                mr[e.v] = u;
                return true;
            }
        }
        // 当前点无法继续找到增广路
        dep[u] = -1;
        return false;
    };
    int ans = 0;
    while(bfs()) {
        for(int u = 1; u <= nl; u++) {
            if(ml[u] == -1 && dfs(dfs, u)) {
                ans++;
            }
        }
    }
    return {ans, ml, mr};
}