#include <bits/stdc++.h>
using namespace std;
vector<int> tarjanSCC(const vector<vector<int>> &g)
{
    int n = g.size();
    int ti = 0; // 时间戳
    int cc = 0; // SCC编号
    vector<int> dfn(n), low(n);
    vector<int> st;
    vector<int> bel(n, -1);
    vector<bool> on(n);
    auto dfs = [&](auto self, int u) -> void {
        dfn[u] = low[u] = ++ti;
        st.push_back(u);
        on[u] = true;
        for (auto v : g[u]){
            if (!dfn[v]) {
                self(self, v);
                low[u] = min(low[u], low[v]);
            }
            else if (on[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        // u 是 SCC 根
        if (low[u] != dfn[u]) {
            return;
        }
        while (true) {
            int v = st.back();
            st.pop_back();
            on[v] = false;
            bel[v] = cc;
            if (v == u)
                break;
        }
        cc++;
    };
    for (int u = 0; u < n; u++) {
        if (!dfn[u])
            dfs(dfs, u);
    }
    return bel;
}