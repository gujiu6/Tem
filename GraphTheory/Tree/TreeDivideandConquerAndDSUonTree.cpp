/*                                       时间复杂度      空间复杂度
4.DSU on Tree
5.长链剖分 + O(1)第k级祖先 + 子树深度众数
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

//5.长链剖分 + O(1)第k级祖先 + 子树深度众数
class TreeInfo {
public:
    int n;
    vector<int> fa, dep, len, son, top, in, rev;//长链剖分
    vector<int> up, upStart;
    TreeInfo(const vector<vector<Edge>>& g, const int root = 1): n(g.size() - 1), fa(n + 1), dep(n + 1), len(n + 1, 1), son(n + 1), top(n + 1), in(n + 1), rev(n + 1), up(n), upStart(n + 1) {
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
            int u = ord[i];
            int f = fa[u];
            if(len[u] + 1 > len[f]) {
                len[f] = len[u] + 1;
                son[f] = u;
            }
        }
        //rev[top[u]][in[u]]可以得到链上的节点
        int tim = 0;
        auto dfs = [&](auto&& self, int u, int h)->void {
            top[u] = h;
            in[u] = ++tim;
            rev[tim] = u;
            if(son[u]) {
                self(self, son[u], h);
            }
            for(const auto &e : g[u]) {
                if(e.v == fa[u] || e.v == son[u]) continue;
                self(self, e.v, e.v);
            }
        };
        if(n) dfs(dfs, root, root);
        int total = 0;
        for(int h = 1; h <= n; h++) {
            if(top[h] != h) continue;
            upStart[h] = total;
            total += len[h];
        }
        for(int h = 1; h <= n; h++) {
            if(top[h] != h) continue;
            int f = h;
            for(int i = 0; i < len[h]; i++) {
                up[upStart[h] + i] = f;
                f = fa[f];
            }
        }
    }
    //O(1)求第k级祖先,不存在返回0
    int kthAncestor(int u, int k) const {
        if(k > dep[u]) return 0;
        int h = top[u];
        //u到当前长链顶部的距离
        int d = dep[u] - dep[h];
        //祖先仍在当前长链上
        if(k <= d) {
            return rev[in[u] - k];
        }
        //跳出当前长链
        k -= d;
        return up[upStart[h] + k];
    }
    //子树中出现次数最多的相对深度
    //ans[u]=d:
    //u的子树中，与u距离为d的节点数量最多
    //若数量相同，取最小d
    vector<int> depthMode(const vector<vector<int>>& g, const int root = 1) const {
        vector<int> at(n + 1), ans(n + 1);
        //最大下标最多n
        vector<int> f(n + 1);
        int ptr = len[root];
        auto dfs = [&](auto&& self, int u, int p)->void {
            int h = son[u];
            //重儿子
            if(h) {
                at[h] = at[u] + 1;
                self(self, h, u);
                ans[u] = ans[h] + 1;
            }
            //u自身
            f[at[u]] = 1;
            if(f[at[u] + ans[u]] <= 1) {
                ans[u] = 0;
            }
            //轻儿子
            for(int v : g[u]) {
                if(v == p || v == h) continue;
                at[v] = ptr;
                ptr += len[v];
                self(self, v, u);
                for(int d = 0; d < len[v]; d++) {
                    f[at[u] + d + 1] += f[at[v] + d];
                    int x = f[at[u] + d + 1];
                    int y = f[at[u] + ans[u]];
                    if(x > y || (x == y && d + 1 < ans[u])) {
                        ans[u] = d + 1;
                    }
                }
            }
        };
        dfs(dfs, root, 0);
        return ans;
    }
};