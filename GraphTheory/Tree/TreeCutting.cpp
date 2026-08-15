/*树剖                       时间复杂度                           空间复杂度
1.重链(HLD)
        预处理               O(n)                                O(n)
        LCA                 O(logn)                             O(1)
        路径查询path         O(logn)                             O(logn)
        子树查询subtree      O(1)                                O(1)
        HLD+线段树          路径修改:O(log²n), 子树修改O(log n)
2.换根树剖
3.虚树
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
            if(son[p] <= 0 || sz[u] > sz[son[p]]) {
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
    int dis(int u, int v) const {
        int p = lca(u, v);
        return dep[u] + dep[v] - 2 * dep[p];
    }
    //op(l,r,rev)：区间为 [l,r], rev: 表示沿路径应逆序读取。
    template <class F> void path(int u, int v, F op, bool edge = false) const {
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
        for(auto &[l, r] : right) {
            op(l, r, false);
        }
    }
    //固定初始根下的普通子树
    pair<int, int> subtree(int u) const {
        return {in[u], in[u] + sz[u] - 1};
    }
    //2.换根树剖,当前根为root时的subtree(u)
    vector<pair<int, int>> subtree(int u, int root) const {
        //1.u就是当前根
        if(u == root) return {{1, n}};
        //2.root不在u的原始子树中,换根以后u的子树不发生变化
        if (!(in[u] <= in[root] && in[root] <= in[u] + sz[u] - 1)) {
            return {{in[u], in[u] + sz[u] - 1}};
        }
        //3.root在u的原始子树中,找到u->root路径上紧邻u的儿子
        int child = childOnPath(u, root);
        vector<pair<int, int>> res;
        //整棵树-subtree(child)
        if (in[child] > 1) {
            res.push_back({1, in[child] - 1});
        }
        if (in[child] + sz[child] <= n) {
            res.push_back({in[child] + sz[child], n});
        }
        return res;
    }
private:
    //ancestor是descendant的祖先,返回ancestor->descendant路径上,紧邻ancestor的那个儿子
    int childOnPath(int ancestor, int descendant) const {
        while (top[ancestor] != top[descendant]) {
            if (fa[top[descendant]] == ancestor) {
                return top[descendant];
            }
            descendant = fa[top[descendant]];
        }
        //两者在同一条重链上,ancestor后面的节点就是所求儿子
        return rev[in[ancestor] + 1];
    }
};

//3.虚树
namespace {

class LCA {
public:
    int n, lg2, tim = 0;
    vector<int> dep, in, out;
    vector<vector<int>> up;
    LCA(const vector<vector<Edge>>& g, int root = 1)
    : n(g.size() - 1), lg2(bit_width((unsigned)max(1, n))), dep(n + 1), in(n + 1), out(n + 1), up(lg2, vector<int>(n + 1)) {
        auto dfs = [&](auto &&self, int u, int f)->void {
            in[u] = ++tim;
            dep[u] = dep[f] + 1;
            up[0][u] = f;
            for(int p = 1; p < lg2; p++) {
                up[p][u] = up[p - 1][up[p - 1][u]];
            }
            for(const auto &e : g[u]) {
                if(e.v == f) continue;
                self(self, e.v, u);
            }
            out[u] = tim;
        };
        if(n) dfs(dfs, root, 0);
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
struct VTree {
    int root = -1;
    vector<int> nodes;//节点池或有效节点列表
    vector<DEdge> edges;
};
VTree VirtualTree(vector<int> a, const LCA& lca) {
    if(a.empty()) return {};
    sort(a.begin(), a.end(), [&](auto x, auto y){
        return lca.in[x] < lca.in[y];
    });
    a.erase(unique(a.begin(), a.end()), a.end());
    int n = a.size();
    for(int i = 1; i < n; i++) {
        a.push_back(lca.lca(a[i - 1], a[i]));
    }
    sort(a.begin(), a.end(), [&](auto x, auto y){
        return lca.in[x] < lca.in[y];
    });
    a.erase(unique(a.begin(), a.end()), a.end());
    vector<int> st;
    VTree ans;
    ans.root = a[0];
    ans.nodes = a;
    for(int u : a) {
        while(!st.empty() && !lca.ancestor(st.back(), u)) {
            st.pop_back();
        }
        if(!st.empty()) {
            ans.edges.push_back({st.back(), u});
        }
        st.push_back(u);
    }
    return  ans;
}
}