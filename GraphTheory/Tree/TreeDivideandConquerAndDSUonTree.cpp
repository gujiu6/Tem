/*                          时间复杂度      空间复杂度
4.DSU on Tree
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