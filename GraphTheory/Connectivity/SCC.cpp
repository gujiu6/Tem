/*                                     时间复杂度        空间复杂度
1.Tarjan 强连通分量                      O(n+m)          O(n)
2.Kosaraju 强连通分量                    O(n+m)          O(n+m)
3.Bitset 优化 Kosaraju                  O(n^3/64)       O(n^2/64)
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using ui64 = unsigned long long;
struct WEdge {int v;i64 w = 0;};struct DEdge {int u, v;i64 w = 0;};struct Edge {int v;};

//1.Tarjan 强连通分量
vector<int> TarjanSCC(const vector<vector<Edge>>& g) {
    int n = g.size() - 1;
    int tim = 0, cc = 0;//时间戳,SCC编号
    vector<int> dfn(n + 1), st;
    vector<int> low(n + 1);//从u出发,能够回到的最小dfn编号
    vector<int> bel(n + 1, -1);//答案数组
    vector<bool> on(n + 1);//当前节点是否还在 Tarjan 栈里面
    auto dfs = [&](auto &&self, int u)->void {
        dfn[u] = low[u] = ++tim;
        st.push_back(u);
        on[u] = true;
        for(const auto &e : g[u]) {
            if(!dfn[e.v]) {
                self(self, e.v);
                low[u] = min(low[u], low[e.v]);
            }
            else if(on[e.v]) {
                low[u] = min(low[u], dfn[e.v]);
            }
        }
        if(low[u] != dfn[u]) return;
        cc++;
        while(true) {
            int v = st.back();st.pop_back();
            on[v] = false;
            bel[v] = cc;
            if(v == u) break;
        }
    };
    for(int u = 1; u <= n; u++) {
        if(!dfn[u]) {
            dfs(dfs, u);
        }
    }
    return bel;
}

//2.Kosaraju 强连通分量
vector<int> KosarajuSCC(const vector<vector<Edge>>& g) {
    int n = g.size() - 1;
    int cc = 0;
    vector<vector<Edge>> rg(n + 1);//建反图
    for(int u = 1; u <= n; u++) {
        for(const auto &e : g[u]) {
            rg[e.v].push_back({u});
        }
    }
    vector<int> ord;//保存DFS完成顺序,不是访问顺序
    vector<int> bel(n + 1, -1);
    vector<bool> vis(n + 1);
    //第一遍DFS求结束序
    auto dfs1 = [&](auto &&self, int u)->void {
        vis[u] = true;
        for(const auto &e : g[u]) {
            if(!vis[e.v]) {
                self(self, e.v);
            }
        }
        ord.push_back(u);
    };
    //第二遍DFS在反图找SCC
    auto dfs2 = [&](auto &&self, int u)->void {
        bel[u] = cc;
        for(const auto &e : rg[u]) {
            if(bel[e.v] == -1) {
                self(self, e.v);
            }
        }
    };
    //原图DFS
    for(int u = 1; u <= n; u++) {
        if(!vis[u]) {
            dfs1(dfs1, u);
        }
    }
    //逆序
    reverse(ord.begin(),ord.end());
    for(const auto& u : ord) {
        if(bel[u] == -1) {
            cc++;
            dfs2(dfs2, u);
        }
    }
    return bel;
}

//3.Bitset 优化 Kosaraju
vector<int> BitsetSCC(const vector<vector<Edge>>& g) {
    int n = g.size() - 1;
    int w = (n + 64 - 1) / 64;//w表示需要多少个64位整数保存一行bitset(向上取整)
    vector<vector<ui64>> reach(n + 1, vector<ui64>(w));
    for(int u = 1; u <= n; u++) {
        reach[u][(u - 1) / 64] |= 1ULL << ((u - 1) % 64);
        for(const auto &e : g[u]) {
            reach[u][(e.v - 1) / 64] |= 1ULL << ((e.v - 1) % 64);
        }
    }
    //Floyd思想求传递闭包
    for(int k = 1; k <= n; k++) {
        for(int u = 1; u <= n; u++) {
            if(!(reach[u][(k - 1) / 64] >> ((k - 1) % 64) & 1ULL)) {
                continue;
            }
            for(int b = 0; b < w; b++) {
                reach[u][b] |= reach[k][b];
            }
        }
    }
    vector<int> bel(n + 1, -1);
    int cc = 1;
    for(int u = 1; u <= n; u++) {
        if(bel[u] != -1) continue;
        for(int v = u; v <= n; v++) {
            bool uv = (reach[u][(v - 1) / 64] >> ((v - 1) % 64) & 1ULL);//u是否可以到v
            bool vu = (reach[v][(u - 1) / 64] >> ((u - 1) % 64) & 1ULL);//v是否可以到u
            if(uv && vu) bel[v] = cc;
        }
        cc++;
    }
    return bel;
}