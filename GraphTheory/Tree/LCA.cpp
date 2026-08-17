/*                  预处理复杂度       LCA复杂度       空间复杂度
1.倍增LCA            O(nlogn)         O(logn)        O(nlogn)
2.ST表/RMQ 求LCA     O(nlogn)         O(1)           O(nlogn)
3.Tarjan离线LCA      O(n+qα(n))                      O(n+q)
*/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using i64 = long long;
const int MAXX = 5e5+10, LIMIT = 20;
struct WEdge {int v;i64 w = 0;};struct DEdge {int u, v;i64 w = 0;};struct Edge {int v;};

//1.倍增LCA
class LCA {
public:
    int n, lg2, tim = 0;
    vector<int> dep, in, out, sz;
    vector<vector<int>> up;
    vector<i64> dis;
    LCA(const vector<vector<WEdge>>& g, int root = 1)
    : n(g.size() - 1), lg2(bit_width((unsigned)max(1, n))), dep(n + 1), in(n + 1), out(n + 1), dis(n + 1), sz(n + 1), up(lg2, vector<int>(n + 1)) {
        auto dfs = [&](auto &&self, int u, int f)->void {
            in[u] = ++tim;
            dep[u] = dep[f] + 1;
            up[0][u] = f;
            sz[u] = 1;
            for(int p = 1; p < lg2; p++) {
                up[p][u] = up[p - 1][up[p - 1][u]];
            }
            for(const auto &e : g[u]) {
                if(e.v == f) continue;
                dis[e.v] = dis[u] + e.w;
                self(self, e.v, u);
                sz[u] += sz[e.v];
            }
            out[u] = tim;
        };
        if(n) dfs(dfs, root, root);
    }
    //u是否为v的祖先
    bool ancestor(int u, int v) const {
        return in[u] <= in[v] && out[v] <= out[u];
    }
    //u向上跳k层
    int jump(int u, int k) const {
        if(k >= dep[u]) return -1;
        for(int p = 0; k; p++, k >>= 1) {
            if(k & 1) {
                u = up[p][u];
            }
        }
        return u;
    }
    //lca
    int lca(int u, int v) const {
        if(ancestor(u, v)) return u;
        if(ancestor(v, u)) return v;
        for(int p = lg2 - 1; p >= 0; p--) {
            if(!ancestor(up[p][u], v)) {
                u = up[p][u];
            }
        }
        return up[0][u];
    }
    //u到v的距离(边数)
    int dist(int u, int v) const {
        int f = lca(u, v);
        return dep[u] + dep[v] - 2 * dep[f];
    }
    //u到v的边权和(边数)
    i64 distW(int u, int v) const {
        int f = lca(u, v);
        return dis[u] + dis[v] - 2 * dis[f];
    }
    // 路径u->v上的第k(0-base)个节点
    int pathKth(int u, int v, int k) const {
        int p = lca(u, v);
        int a = dep[u] - dep[p];
        int b = dep[v] - dep[p];
        if(k < 0 || k > a + b) return -1;
        if(k <= a) return jump(u, k);
        return jump(v, a + b - k);
    }
};

//2.ST表/RMQ 求LCA
namespace {

template <class T , class F>
class ST1 {
public:
    int n, lg2;
    vector<vector<T>> st;
    F op;
    ST1(const vector<T>& a, F f = {}): n(a.size() - 1), op(f) {
        lg2 = n ? bit_width(unsigned(n)) : 0;
        st.assign(lg2 + 1, vector<T>(n + 1));
        if(!n) return;
        st[0] = a;
        for(int p = 1; p <= lg2; p++) {
            for(int i = 1; i + (1LL << p) - 1 <= n; i++) {
                st[p][i] = op(st[p - 1][i], st[p - 1][i + (1LL << (p - 1))]);
            }
        }
    }

    T qry(int l, int r) const {
        assert(1 <= l && l <= r && r <= n);
        int p = bit_width(unsigned(r - l + 1)) - 1;
        T ans = op(st[p][l], st[p][r - (1LL << p) + 1]);
        return ans;
    }
};
class LCARMQ {
private:
    using pii = pair<int, int>;
    struct MinDepth {
        pii operator() (pii a, pii b) const {
            return min(a, b);
        }
    };
public:
    vector<int> first;
    ST1 <pii, MinDepth> st;
    static pair<vector<int>, vector<pii>> tour(const vector<vector<Edge>>& g, int root) {
        vector<int> first(g.size(), -1);
        vector<pii> euler(1);
        auto dfs = [&](auto &&self, int u, int f, int dep)->void {
            if(first[u] == -1) {
                first[u] = euler.size();
            }
            euler.push_back({dep, u});
            for(const auto &e : g[u]) {
                if(e.v == f) continue;
                self(self, e.v, u, dep + 1);
                euler.push_back({dep, u});
            }
        };
        dfs(dfs, root, 0, 0);
        return {first, euler};
    }
    LCARMQ(const vector<vector<Edge>>& g, int root = 1): LCARMQ(tour(g, root)){}
    int lca(int u, int v) const {
        int l = first[u], r = first[v];
        if(l > r) swap(l, r);
        return st.qry(l, r).second;
    } 
private:
    LCARMQ(pair<vector<int>, vector<pii>> p): first(move(p.first)), st(move(p.second), MinDepth{}){}
};

}

//3.Tarjan离线LCA
vector<int> TarjanLCA(const vector<vector<Edge>>& g, const vector<pair<int, int>> &q, int root = 1) {
    //q:按输入顺序给出的节点对询问;按输入询问顺序返回每对节点的最近公共祖先
    int n = g.size() - 1, m = q.size();
    vector<vector<pair<int, int>>> ask(n + 1);
    for(int i = 0; i < m; i++) {
        auto &[u, v] = q[i];
        ask[u].push_back({v, i});
        ask[v].push_back({u, i});
    }
    vector<int> fa(n + 1), sz(n + 1, 1);
    vector<int> ans(m, -1);
    vector<int> anc(n + 1);
    //0:未访问;1:正在DFS;2:子树处理完成
    vector<int> col(n + 1);
    iota(fa.begin(), fa.end(), 0);
    auto find = [&](auto &&self, int i)->int {
        if(i != fa[i]) {
            fa[i] = self(self, fa[i]);
        }
        return fa[i];
    };
    auto merge = [&](int x, int y)->bool {
        x = find(find, x), y = find(find, y);
        if(x == y) return false;
        if(sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
        return true;
    };
    auto dfs = [&](auto &&self, int u, int f)->void {
        anc[u] = u;
        col[u] = 1;
        for(const auto &e : g[u]) {
            if(e.v == f) continue;
            self(self, e.v, u);
            merge(u, e.v);
            anc[find(find, u)] = u;
        }
        col[u] = 2;
        for(const auto &[v, id] : ask[u]) {
            if(col[v] == 2) {
                ans[id] = anc[find(find, v)];
            }
        }
    };
    dfs(dfs, root, 0);
    return ans;
}
