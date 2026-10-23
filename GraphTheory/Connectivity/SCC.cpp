/*                                     时间复杂度        空间复杂度
1.Tarjan 强连通分量                      O(n+m)          O(n)
2.Kosaraju 强连通分量                    O(n+m)          O(n+m)
3.Bitset 优化 Kosaraju                  O(n^3/64)       O(n^2/64)
4.割边与边双连通分量
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using ui64 = unsigned long long;
struct WEdge {int v;i64 w = 0;};struct DEdge {int u, v;i64 w = 0;};struct Edge {int v;};

// 1.Tarjan 强连通分量
pair<int, vector<int>> TarjanSCC(const vector<vector<Edge>>& g) {
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
    return {cc, bel};
}

// 2.Kosaraju 强连通分量
pair<int, vector<int>> KosarajuSCC(const vector<vector<Edge>>& g) {
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
    return {cc, bel};
}

// 3.Bitset 优化 Kosaraju
pair<int, vector<int>> BitsetSCC(const vector<vector<Edge>>& g) {
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
    int cc = 0;
    for(int u = 1; u <= n; u++) {
        if(bel[u] != -1) continue;
        cc++;
        for(int v = u; v <= n; v++) {
            bool uv = (reach[u][(v - 1) / 64] >> ((v - 1) % 64) & 1ULL);//u是否可以到v
            bool vu = (reach[v][(u - 1) / 64] >> ((u - 1) % 64) & 1ULL);//v是否可以到u
            if(uv && vu) bel[v] = cc;
        }
    }
    return {cc, bel};
}

// 4.割边与边双连通分量
class EdgeBCC {
public:
    int n, tim = 0;
    vector<array<int, 2>> edges;
    vector<vector<array<int, 2>>> g;
    vector<int> dfn, low; // dfn[u] 是进入时间，low[u] 是不经过父边能到达的最早时间
    vector<bool> bridge; // bridge[i] 标记第 i 条边是否为桥
private:
    void dfs(int u, int pe) {
        // u 是当前点,pe 是进入 u 的边编号,计算 low 并标记桥，无返回值
        dfn[u] = low[u] = ++tim;
        for(const auto &[v, id] : g[u]) {
            if(id == pe) {
                continue;
            }
            if(!dfn[v]) {
                dfs(v, id);
                low[u] = min(low[u], low[v]);
                if(low[v] > dfn[u]) {
                    bridge[id] = true;
                }
            }
            else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
public:
    EdgeBCC(int n) : n(n), g(n + 1), dfn(n + 1), low(n + 1) {}
    int addEdge(int u, int v) {
        int id = edges.size();
        edges.push_back({u, v});
        g[u].push_back({v, id});
        g[v].push_back({u, id});
        return id;
    }

    void build() {
        // 无参数,重新计算全部桥,无返回值.
        tim = 0;
        fill(dfn.begin(), dfn.end(), 0);
        fill(low.begin(), low.end(), 0);
        bridge.assign(edges.size(), false);
        for(int u = 1; u <= n; u++) {
            if (!dfn[u]) {
                dfs(u, -1);
            }
        }
    }

    const vector<bool> &bridges() const {
        return bridge;
    }

    pair<int, vector<int>> comps() const {
        // 无参数,返回删除全部桥后每个点的边双连通分量编号.
        vector<int> bel(n + 1, -1);
        int cc = 0;
        for(int s = 1; s <= n; s++) {
            if(bel[s] != -1) {
                continue;
            }
            queue<int> q;
            q.push(s);
            bel[s] = ++cc;
            while(!q.empty()) {
                auto u = q.front(); q.pop();
                for(const auto &[v, id] : g[u]) {
                    if (!bridge[id] && bel[v] == -1) {
                        bel[v] = bel[u];
                        q.push(v);
                    }
                }
            }
        }
        return {cc, bel};
    }
};

// 5.割点与点双连通分量
class VertexBCC {
public:
    int n, tim = 0;
    vector<array<int, 2>> ed;
    vector<vector<array<int, 2>>> g;
    vector<int> dfn, low, st;
    vector<bool> cut;
    vector<vector<int>> bcc;
private:
    void dfs(int u, int pe) {
        dfn[u] = low[u] = ++tim;
        int son = 0;
        for (const auto &[v, id] : g[u]) {
            if (id == pe) {
                continue;
            }
            if (!dfn[v]) {
                son++;
                st.push_back(id);
                dfs(v, id);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    if (pe != -1 || son > 1) {
                        cut[u] = true;
                    }
                    vector<int> cur;
                    while (true) {
                        int x = st.back();
                        st.pop_back();
                        cur.push_back(ed[x][0]);
                        cur.push_back(ed[x][1]);
                        if (x == id) {
                            break;
                        }
                    }
                    bcc.push_back(move(cur));
                }
            }
            else if (dfn[v] < dfn[u]) {
                st.push_back(id);
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (pe == -1 && son == 0) {
            bcc.push_back({u});
        }
    }

public:
    VertexBCC(int n) : n(n), g(n + 1), dfn(n + 1), low(n + 1), cut(n + 1) {}

    int addEdge(int u, int v) {
        int id = ed.size();
        ed.push_back({u, v});
        g[u].push_back({v, id});
        g[v].push_back({u, id});
        return id;
    }

    void build() {
        tim = 0;
        fill(dfn.begin(), dfn.end(), 0);
        fill(low.begin(), low.end(), 0);
        fill(cut.begin(), cut.end(), false);
        st.clear();
        bcc.clear();

        for (int u = 1; u <= n; u++) {
            if (!dfn[u]) {
                dfs(u, -1);
            }
        }

        vector<int> head(n + 1, -1);
        vector<array<int, 2>> link;
        link.reserve(n + ed.size());
        for (int i = 0; i < (int)bcc.size(); i++) {
            for (int u : bcc[i]) {
                if (head[u] != -1 && link[head[u]][0] == i) {
                    continue;
                }
                link.push_back({i, head[u]});
                head[u] = (int)link.size() - 1;
            }
            bcc[i].clear();
        }

        for (int u = 1; u <= n; u++) {
            for (int j = head[u]; j != -1; j = link[j][1]) {
                bcc[link[j][0]].push_back(u);
            }
        }
    }

    const vector<bool> &cutVertices() const {
        return cut;
    }

    const vector<vector<int>> &comps() const {
        return bcc;
    }
};