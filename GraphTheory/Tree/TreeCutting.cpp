/*树剖                       时间复杂度                           空间复杂度
1.重链(HLD)
        预处理               O(n)                                O(n)
        LCA                 O(logn)                             O(1)
        路径查询path         O(logn)                             O(logn)
        子树查询subtree      O(1)                                O(1)
        HLD+线段树          路径修改:O(log²n), 子树修改O(log n)
2.换根树剖
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct WEdge {int v;i64 w = 0;};struct DEdge {int u, v;i64 w = 0;};struct Edge {int v;};

//1.重链(HLD)
class HLD {
public:
    int n, tim = 0;
    vector<int> fa, dep, sz, son, top, in, rev;
    HLD(const vector<vector<Edge>>& g, const int root = 1): n(g.size() - 1), fa(n + 1), sz(n + 1, 1), son(n + 1), top(n + 1), in(n + 1), rev(n + 1), dep(n + 1) {
        //son:重儿子,top:当前入选的前 k 个元素,in:DFS 进入时间,rev:标记当前辅助子树是否需要翻转
        sz[0] = 0;
        vector<int> ord{0, root};
        for(int i = 1; i < ord.size(); i++) {
            int u = ord[i];
            for(const auto &e : g[u]) {
                if(e.v == fa[u]) continue;
                fa[e.v] = u;
                dep[e.v] = dep[u] + 1;
                ord.push_back(e.v);
            }
        }
        for(int i = n; i >= 1; i--) {
            int u = ord[i], p = fa[u];
            sz[p] += sz[u];
            if(son[p] < 0 || sz[u] > sz[son[p]]) {
                son[p] = u;
            }
        }
        auto dfs = [&](auto &&self, int u, int h)->void {
            top[u] = h;
            in[u] = ++tim;
            rev[tim] = u;
            if(son[u] > 0) {
                self(self, son[u], h);
            }
            for(const auto &e : g[u]) {
                if(e.v != fa[u] && e.v != son[u]) {
                    self(self, e.v, e.v);
                }
            }
        };
        if(n) dfs(dfs, root, root);
    }

    int lca(int u, int v) const {
        while(top[u] != top[v]) {
            if(dep[top[u]] < dep[top[v]]) {
                swap(u, v);
            }
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
    //op(l,r,rev)：区间为 [l,r], rev: 表示沿路径应逆序读取。
    template <typename F> void path(int u, int v, F op, bool edge = false) const {
        vector<pair<int, int>> right;
        while(top[u] != top[v]) {
            if(dep[top[u]] >= dep[top[v]]) {
                op(in[top[u]], in[u], true);
                u = fa[top[u]];
            }
            else {
                right.push_back({in[top[v]], in[v]});
                v = fa[top[v]];
            }
        }
        if(dep[u] >= dep[v]) {
            op(in[v] + edge, in[u], true);
        }
        else {
            right.push_back({in[u] + edge, in[v]});
        }
        reverse(right.begin(), right.end());
        for(auto [l, r] : right) {
            op(l, r, false);
        }
    }
    pair<int, int> subtree(int u) const {
        return {in[u], in[u] + sz[u] - 1};
    }
};

//2.换根树剖
