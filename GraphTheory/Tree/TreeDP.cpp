/*
1.树上背包基础版
*/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using i64 = long long;
const i64 INF = 1e18;
struct WEdge {int v;i64 w = 0;};struct DEdge {int u, v;i64 w = 0;};struct Edge {int v;};


//1.树上背包基础版
template <class T = i64>
vector<T> TreePack(const vector<vector<Edge>>& g, const vector<T>& val, int k, int root = 1) {
    //val:点权;root:根;k:最多选择点数;返回 dp[j]:全树恰选j点的最大权值
    auto dfs = [&](auto &&self, int u, int f)->vector<T> {
        vector<T> dp(min(1, k) + 1, -INF);
        dp[0] = 0;
        if(k) {
            dp[1] = val[u];
        }
        for(auto &e : g[u]) {
            if(e.v == f) continue;
            auto h = self(self, e.v, u);
            vector<T> ndp(min(k, (int)dp.size() + (int)h.size() - 2) + 1, -INF);
            for(int i = 0; i < dp.size(); i++) {
                if(dp[i] == -INF) continue;
                for(int j = 0; j < h.size() && i + j <= k; j++) {
                    if(h[j] == -INF) continue;
                    ndp[i + j] = max(ndp[i + j], dp[i] + h[j]);
                }
            }
            dp = move(ndp);
        }
        return dp;
    };
    assert(g.size() == val.size() && 0 <= root && root < g.size());
    return dfs(dfs, root, 0);
}