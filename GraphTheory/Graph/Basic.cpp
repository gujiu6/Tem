/*                                                 时间复杂度       空间复杂度
1.拓扑排序(字典序)                                   O(n+m)logn      O(n)
2.判定二分图                                        O(n+m)          O(n)
3.DAG(有向无环图)最长路                              O(n+m)          O(n)
4.DAG(有向无环图)删点最长路:删除某个点后剩下图的最长路    O(n+m+nlogn)    O(n+m)
5.差分约束:多组不等式Xv - Xu <= w                    O(nm)           O(n)
6.DAG判断是否半连通(是否任意两点间都有可达路径)         O(n+m)           O(n)
*/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using i64 = long long;
constexpr int MAXX = 1000;
constexpr i64 INF = 1e18;
struct WEdge {int v;i64 w = 0;};struct DEdge {int u, v;i64 w = 0;};struct Edge {int v;};

//1.拓扑排序(字典序)
optional<vector<int>> TopSort(vector<vector<WEdge>>& g, vector<int> inDeg) {
    int n = g.size() - 1;
    vector<int> ord{0};
    priority_queue<int, vector<int>, greater<int>> q;
    for(int i = 1; i <= n; i++) {
        if(inDeg[i] == 0) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        auto u = q.top();q.pop();
        ord.push_back(u);
        for(const auto &e : g[u]) {
            if(--inDeg[e.v] == 0) {
                q.push(e.v);
            }
        }
    }
    if(ord.size() - 1 != n) return nullopt;
    return ord;
}

//2.判定二分图
optional<vector<int>> bipartite(const vector<vector<WEdge>>& g) {
    //返回每个点的 0/1 颜色,存在奇环时返回空
    int n = g.size() - 1;
    vector<int> col(n + 1, -1);
    for(int s = 1; s <= n; s++) {
        if(col[s] != -1) continue;
        queue<int> q;
        col[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(const auto &e : g[u]) {
                if(col[e.v] == -1) {
                    col[e.v] = col[u] ^ 1;
                    q.push(e.v);
                }
                else if(col[e.v] == col[u]) {
                    return nullopt;
                }
            }
        }
    }
    return col;
}

//3.DAG(有向无环图)最长路
optional<vector<i64>> DAGLongest(const vector<vector<WEdge>>& g, vector<int> inDeg, int s = -1) {
    //g[u]:终点和边权;s:起点,s=-1时允许从任意点开始;图有环时返回空
    int n = g.size() - 1;
    vector<int> ord{0};
    queue<int> q;
    for(int i = 1; i <= n; i++) {
        if(inDeg[i] == 0) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        int u = q.front(); q.pop();
        ord.push_back(u);
        for(const auto &e : g[u]) {
            if(--inDeg[e.v] == 0) {
                q.push(e.v);
            }
        }
    }
    if(ord.size() - 1 != n) return nullopt;
    vector<i64> d(n + 1, s == -1 ? 0 : -INF);
    if(s != -1) d[s] = 0;
    for(int i = 1; i <= n; i++) {
        int u = ord[i];
        if(d[u] == -INF) continue;
        for(const auto &e : g[u]) {
            d[e.v] = max(d[e.v], d[u] + e.w);
        }
    }
    return d;
}

//4.DAG(有向无环图)删点最长路:删除某个点后剩下图的最长路
vector<i64> DelDAG(const vector<vector<WEdge>>& g, vector<int> inDeg) {
    int n = g.size() - 1;
    queue<int> q;
    for(int i = 1; i <= n; i++) {
        if(inDeg[i] == 0) {
            q.push(i);
        }
    }
    vector<int> ord{0};
    while(!q.empty()) {
        int u = q.front();q.pop();
        ord.push_back(u);
        for(const auto &e : g[u]) {
            if(--inDeg[e.v] == 0) {
                q.push(e.v);
            }
        }
    }
    assert(ord.size() - 1 == n);
    vector<int> pos(n + 1);//pos[u]:u在拓扑序中的位置
    for(int i = 1; i <= n; i++) {
        pos[ord[i]] = i;
    }
    vector<i64> left(n + 1);//以u结尾的最长路径长度
    for(int i = 1; i <= n; i++) {
        int u = ord[i];
        for(const auto &e : g[u]) {
            left[e.v] = max(left[e.v], left[u] + e.w);
        }
    }
    vector<i64> right(n + 1);//以u开头的最长路径长度
    for(int i = n; i >= 1; i--) {
        int u = ord[i];
        for(auto &e : g[u]) {
            right[u] = max(right[u], right[e.v] + e.w);
        }
    }
    vector<vector<pair<i64, int>>> starts(n + 1);//删除拓扑位置i的点时,哪些跨越边开始生效
    for(int u = 1; u <= n; u++) {
        for(auto &e : g[u]) {
            int l = pos[u] + 1;
            int r = pos[e.v] - 1;
            if(l <= r) {//区间[l, r]
                i64 value = left[u] + e.w + right[e.v];
                starts[l].push_back({value, r});
            }
        }
    }
    vector<i64> pre(n + 2), suf(n + 2);
    for(int i = 1; i <= n; i++) {
        pre[i] = max(pre[i - 1], left[ord[i]]);
    }
    for(int i = n; i >= 1; i--) {
        suf[i] = max(suf[i + 1], right[ord[i]]);
    }
    priority_queue<pair<i64, int>> active;//first:跨越边贡献;second:该边最后有效的删除位置
    vector<i64> ans(n + 1);
    for(int i = 1; i <= n; i++) {
        //从i开始生效的跨越边
        for(const auto &[value, r] : starts[i]) {
            active.push({value, r});
        }
        //闭区间[l,r],r<i时失效
        while(!active.empty() && active.top().second < i) {
            active.pop();
        }
        //完全在左边:pre[i-1];完全在右边:suf[i+1]
        ans[ord[i]] = max(pre[i - 1], suf[i + 1]);
        //左->右跨越
        if(!active.empty()) {
            ans[ord[i]] = max(ans[ord[i]], active.top().first);
        }
    }
    return ans;
}

//5.差分约束:多组不等式Xv - Xu <= w
//5.1 Bellman-Ford
optional<vector<int>> DiffConstraints(int n, const vector<tuple<int, int, int>>& a) {
    vector<int> x(n + 1);
    for(int k = 1; k <= n; k++) {
        bool ok = true;
        for(int i = 1; i < a.size(); i++) {
            auto &[u, v, w] = a[i];
            assert(1 <= u && u <= n && 1 <= v && v <= n);
            if(x[v] > x[u] + w) {
                x[v] = x[u] + w;
                ok = false;
            }
            if(ok) {
                return x;
            }
        }
    }
    return nullopt;
}
//5.2 SPFA+SLF
optional<vector<i64>> DiffConstraints(const vector<vector<WEdge>>& g) {
    int n = g.size() - 1;
    vector<i64> d(n + 1, 0);
    vector<int> in(n + 1), len(n + 1);//in:是否在队列里面,len:当前最短路经过的边数
    deque<int> q;
    for(int i = 1; i <= n; i++) {
        q.push_back(i);
        in[i] = 1;
    }
    while(!q.empty()) {
        auto u = q.front(); q.pop_front();
        in[u] = 0;
        for(const auto &e : g[u]) {
            i64 nd = e.w + d[u];
            if(d[e.v] <= nd) continue;
            d[e.v] = nd;
            len[e.v] = len[u] + 1;
            //超过n-1条边,一定有负环
            if(len[e.v] >= n) return nullopt;
            if(!in[e.v]) {
                //SLF优化
                if(!q.empty() && d[e.v] < d[q.front()]) {
                    q.push_front(e.v);
                }
                else {
                    q.push_back(e.v);
                }
                in[e.v] = 1;
            }
        }
    }
    return d;
}

//6.DAG判断是否半连通(是否任意两点间都有可达路径)
bool pd(const vector<vector<Edge>>& g, vector<int> inDeg) {
    int n = g.size() - 1;
    queue<int> q;
    for(int i = 1; i <= n; i++) {
        if(inDeg[i] == 0) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        if(q.size() > 1) return false;
        auto u = q.front();q.pop();
        for(const auto &e : g[u]) {
            if(--inDeg[e.v] == 0) {
                q.push(e.v);
            }
        }
    }
    return true;
}