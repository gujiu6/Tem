//树剖
#include <bits/stdc++.h>
using namespace std;

//重链
namespace {

class HLD {
private:
    int n, tim = 0;
    vector<int> fa, dep, sz, son, top, in, rev;
public:
    HLD(const vector<vector<int>>& g, int root = 1): n(g.size() - 1), fa(n + 1), sz(n + 1, 1), son(n + 1), top(n + 1), in(n + 1), rev(n + 1) {
        sz[0] = 0;
        vector<int> ord{0, root};
        for(int i = 1; i < ord.size(); i++) {
            int u = ord[i];
            for(int v : g[u]) {
                if(v == fa[u]) continue;
                fa[v] = u;
                dep[v] = dep[u] + 1;
                ord.push_back(v);
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
            rev[tim] = u;
            in[u] = tim++;
            if(son[u] > 0) {
                self(self, son[u], h);
            }
            for(int v : g[u]) {
                if(v != fa[u] && v != son[u]) {
                    self(self, v, v);
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
        return {in[u], in[u] + sz[u]};
    }

};

}