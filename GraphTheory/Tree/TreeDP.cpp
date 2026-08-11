/*
1.树上背包基础版
2.单调队列优化树上背包
3.长链剖分 DP 合并
4.树上依赖背包:每件物品有父子依赖，选任一非根物品前必须先选其父物品
*/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using i64 = long long;
const i64 INF = 1e18;
struct WEdge {int v;i64 w = 0;};struct DEdge {int u, v;i64 w = 0;};struct Edge {int v;};


//1.树上背包基础版(没有依赖)
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

//2.单调队列优化树上背包


//3.长链剖分 DP 合并

//4.树上依赖背包:每件物品有父子依赖，选任一非根物品前必须先选其父物品
template <class T = i64>
vector<T> TreeDepPack(const vector<int>& w, const vector<T>& val, const vector<int>& p, int cap) {
    // p[i]=0: i 是根节点, 返回:总容量恰好为 c 时的最大价值。
    int n = w.size() - 1;
    vector<vector<int>> son(n + 1);
    for(int u = 1; u <= n; u++) {
        assert(w[u] > 0);
        assert(0 <= p[u] && p[u] <= n);
        son[p[u]].push_back(u);
    }
    auto dfs = [&](auto &&self, int u)->vector<int> {
        vector<T> dp(cap + 1, -INF);
        //虚根
        if(u == 0) {
            dp[0] = 0;
        }
        else {
            //只选择当前节点
            if(w[u] <= cap) 
                dp[w[u]] = val[u];
        }
        for(int &v : son[u]) {
            auto h = self(self, v);
            //不选这个儿子
            auto ndp = dp;
            for(int i = 0; i <= cap; i++){
                if(dp[i] == -INF) continue;
                for(int j = 1; i + j <= cap; j++) {
                    if(h[j] == -INF) continue;
                    ndp[i + j] = max(dp[i + j], dp[i] + h[j]);
                }
            }
            dp = move(ndp);
        }
        return dp;
    };
    return dfs(dfs, 0);
}