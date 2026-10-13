/*                                       时间复杂度      空间复杂度
4.DSU on Tree
5.长链
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct WEdge {int v;i64 w = 0;};struct DEdge {int u, v;i64 w = 0;};struct Edge {int v;};




//4.DSU on Tree:离线回答每个子树的"频率型"询问
class DsuOnTree {
public:
    int n;
    vector<vector<Edge>> g;
    vector<int> fa, sz, son, dep;
    DsuOnTree(const vector<vector<Edge>>& g): n(g.size() - 1), g(g), fa(n + 1), sz(n + 1),dep(n + 1), son(n + 1, -1) {}
private:
    void prepare(int u, int f) {
        fa[u] = f;
        sz[u] = 1;
        dep[u] = dep[f] + 1;
        for (const auto &e : g[u]) {
            if (e.v == f) continue;
            prepare(e.v, u);
            sz[u] += sz[e.v];
            if (son[u] == -1 || sz[e.v] > sz[son[u]]) {
                son[u] = e.v;
            }
        }
    }
    //遍历u的整棵子树,对每个节点调用callback
    template <class Callback>
    void visitSubtree(int u, int p, Callback& callback) const {
        callback(u);
        for (const auto &e : g[u]) {
            if (e.v == p) continue;
            visitSubtree(e.v, u, callback);
        }
    }
    template <class Add, class Del, class Ans>
    void dfs(int u, bool keep, Add& add, Del& del, Ans& ans) {
        //先处理所有轻儿子，并清除贡献
        for (const auto &e : g[u]) {
            if (e.v == fa[u] || e.v == son[u]) continue;
            dfs(e.v, false, add, del, ans);
        }
        //再处理重儿子，并保留贡献
        if (son[u] != -1) {
            dfs(son[u], true, add, del, ans);
        }
        //把所有轻儿子的贡献重新加入
        for (const auto &e : g[u]) {
            if (e.v == fa[u] || e.v == son[u]) continue;
            visitSubtree(e.v, u, add);
        }
        //加入自己
        add(u);
        //此时当前状态就是 subtree(u)
        ans(u);
        //如果不需要保留，则清除整棵子树
        if (!keep) {
            visitSubtree(u, fa[u], del);
        }
    }
public:
    template <class Add, class Del, class Ans>
    void run(Add& add, Del& del, Ans& ans, int root = 1) {
        prepare(root, root);
        dfs(root, false, add, del, ans);
    }
};

//5.长链 + O(1)k级祖先
class LCD {
public:
    int n, lg2, tim = 0;
    vector<int> fa, dep, top, len, son, in;
    vector<vector<int>> stjump;
    vector<int> up, down;
    LCD(const vector<vector<Edge>>& g, const int& root = 1): n(g.size() - 1), lg2(bit_width(unsigned(max(1, n)))), fa(n + 1), dep(n + 1), top(n + 1), len(n + 1), son(n + 1), in(n + 1), stjump(lg2, vector<int>(n + 1)), up(n + 1), down(n + 1) {
        vector<int> ord{root};
        for(int i = 0; i < ord.size(); i++) {
            int u = ord[i];
            stjump[0][u] = fa[u];
            for(int p = 1; p < lg2; p++) {
                stjump[p][u] = stjump[p - 1][stjump[p - 1][u]];
            }
            for(const auto &e : g[u]) {
                if(e.v == fa[u]) continue;
                fa[e.v] = u;
                dep[e.v] = dep[u] + 1;
                ord.push_back(e.v);
            }
        }
        len[0] = 0;
        for(int i = n - 1; i >= 0; i--) {
            int u = ord[i];
            for(const auto &e : g[u]) {
                if(e.v == fa[u]) continue;
                if(len[e.v] > len[son[u]]) {
                    son[u] = e.v;
                }
            }
            len[u] = len[son[u]] + 1;
        }
        auto dfs = [&](auto &&self, int u, int h)->void {
            top[u] = h;
            in[u] = ++tim;
            if(son[u]) {
                self(self, son[u], h);
            }
            for(const auto &e : g[u]) {
                if(e.v != fa[u] && e.v != son[u]) {
                    self(self, e.v, e.v);
                }
            }
        };
        if(n) dfs(dfs, root, root);
        for(int u = 1; u <= n; u++) {
            if(top[u] != u) continue;
            for(int i = 0, a = u, b = u; i < len[u]; i++, a = fa[a], b = son[b]) {
                up[in[u] + i] = a;
                down[in[u] + i] = b;
            }
        }
    }
    //O(1)返回x的k级祖先
    int KthAncestor(int u, int k) {
        if(k == 0) return u;
        if(k > dep[u]) return 0;
        int p = __lg(k);
        if(k == (1 << p)) return stjump[p][u];
        u = stjump[p][u];
        k -= 1 << p;
        k -= dep[u] - dep[top[u]];
        u = top[u];
        return k >= 0 ? up[in[u] + k] : down[in[u] - k];
    }
};