/*                                     时间复杂度        空间复杂度
1.Tarjan 强连通分量                      O(n+m)          O(n)
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct WEdge {int v;i64 w = 0;};struct DEdge {int u, v;i64 w = 0;};struct Edge {int v;};

//1.Tarjan 强连通分量
vector<int> TarjanSCC(const vector<vector<Edge>>& g) {
    int n = g.size() - 1;
    int tim = 0, cc = 1;//时间戳,SCC编号
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
        while(true) {
            int v = st.back();st.pop_back();
            on[v] = false;
            bel[v] = cc;
            if(v == u) break;
        }
        cc++;
    };
    for(int u = 1; u <= n; u++) {
        if(!dfn[u]) {
            dfs(dfs, u);
        }
    }
    return bel;
}