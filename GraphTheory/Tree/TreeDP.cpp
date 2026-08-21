/*                                   时间复杂度         空间复杂度                             
1.树上背包基础版                       O(nk²)             O(nk)
2.单调队列优化树上背包
3.长链剖分 DP 合并                     O(n)              O(n)
4.树上依赖背包:         
    4.1普通版本                       O(nk²)             O(nk)
    4.2 dfn序最优                     O(nk)              O(nk)
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
vector<int> depthMode(const vector<vector<Edge>>& g, int root = 1){
    int n = (int)g.size() - 1;
    vector<int> len(n + 1, 1), son(n + 1);
    vector<int> at1(n + 1), dp1(n + 1);
    vector<int> at2(n + 1), dp2(2 * n + 5);
    vector<int> ans(n + 1);//u的子树中,距离u为多少的节点最多,并且如果有多个深度节点数相同,取最小的那个深度
    //求最长链
    auto dfs1 = [&](auto&& self, int u, int f) -> void{
        for (const auto &e : g[u]) {
            if (e.v == f)
                continue;
            self(self, e.v, u);
            if (len[e.v] + 1 > len[u]) {
                len[u] = len[e.v] + 1;
                son[u] = e.v;
            }
        }
    };
    dfs1(dfs1, root, 0);
    //给轻儿子分配 DP 空间
    int ptr1 = len[root]; at1[root] = 0;
    int ptr2 = len[root] - 1; at2[root] = len[root] - 1;
    //DP
    auto dfs2 = [&](auto&& self, int u, int f) -> void {
        int h = son[u];
        //长儿子直接复用 u 的 DP 数组
        if (h != 0) {
            at1[h] = at1[u] + 1;
            at2[h] = at2[u] - 1;
            self(self, h, u);
            //长儿子的答案转换成 u 的相对深度
            ans[u] = ans[h] + 1;
        }
        dp1[at1[u]] = 1;//u自己,距离u为 0
        //如果当前最大值只有1,最小深度显然是0
        if (dp1[at1[u] + ans[u]] == 1) {
            ans[u] = 0;
        }
        //合并轻儿子
        for (const auto &e : g[u]){
            if (e.v == f || e.v == h) continue;
            //给轻儿子单独分配空间
            at1[e.v] = ptr1; ptr1 += len[e.v];
            at2[e.v] = ptr2; ptr2 += len[e.v] + 1;
            self(self, e.v, u);
            // dp1[u][d] += dp1[v][d - 1]
            for (int d = 1; d <= len[e.v]; d++) {
                dp1[at1[u] + d] += dp1[at1[e.v] + d - 1];
                int cur = dp1[at1[u] + d];
                int best = dp1[at1[u] + ans[u]];
                //次数更多,或者次数相同但深度更小
                if (cur > best || (cur == best && d < ans[u])){
                    ans[u] = d;
                }
            }
            // dp2[u][d] += dp2[v][d + 1]
            for(int d = 0; d < len[e.v]; d++) {
                dp2[at2[u] + d] += dp2[at2[e.v] + d + 1];
            }
        }
    };
    dfs2(dfs2, root, 0);
    return ans;
}

//4.树上依赖背包:每件物品有父子依赖,选任一非根物品前必须先选其父物品
//4.1普通版本
template <class T = i64>
vector<T> TreeDepPack(const vector<int>& w, const vector<T>& val, const vector<int>& p, int cap) {
    // p[i]=0: i 是根节点, 返回:总容量恰好为 c 时的最大价值。
    int n = w.size() - 1;
    vector<vector<Edge>> son(n + 1);
    for(int u = 1; u <= n; u++) {
        assert(w[u] > 0);
        assert(0 <= p[u] && p[u] <= n);
        son[p[u]].push_back({u});
    }
    auto dfs = [&](auto &&self, int u)->vector<T> {
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
        for(const auto &e : son[u]) {
            auto h = self(self, e.v);
            //不选这个儿子
            auto ndp = dp;
            for(int i = 0; i <= cap; i++){
                if(dp[i] == -INF) continue;
                for(int j = 1; i + j <= cap; j++) {
                    if(h[j] == -INF) continue;
                    ndp[i + j] = max(ndp[i + j], dp[i] + h[j]);
                }
            }
            dp = move(ndp);
        }
        return dp;
    };
    return dfs(dfs, 0);
}
//4.2 dfn序最优
template <class T = i64>
T TreeDepPack(const vector<int>& w, const vector<T>& val, const vector<int>& p, int cap) {
    int n = w.size() - 1;
    vector<vector<Edge>> son(n + 1);
    for(int u = 1; u <= n; u++) {
        son[p[u]].push_back({u});
    }
    vector<int> dfn(n + 1), dfn_w(n + 2), dfn_sz(n + 2);
    vector<T> dfn_val(n + 2);
    int tim = 0;
    auto dfs = [&](auto &&self, int u)->void {
        dfn[u] = ++tim;
        dfn_w[dfn[u]] = w[u];
        dfn_val[dfn[u]] = val[u];
        dfn_sz[dfn[u]] = 1;
        for(const auto &e : son[u]) {
            self(self, e.v);
            dfn_sz[dfn[u]] += dfn_sz[dfn[e.v]]; 
        }
    };
    dfs(dfs, 0);
    vector<vector<T>> dp(n + 3, vector<T>(cap + 1));
    for(int i = n + 1; i >= 2; i--) {
        for(int j = 0; j <= cap; j++) {
            //不选当前节点
            dp[i][j] = dp[i + dfn_sz[i]][j];
            //选当前节点
            if(j >= dfn_w[i]) {
                dp[i][j] = max(dp[i][j], dp[i + 1][j - dfn_w[i]] + dfn_val[i]);
            }
        }
    }
    return dfn_val[1] + dp[2][cap];
}
