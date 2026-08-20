/*                                时间复杂度           空间复杂度
1.最小生成树  
    KrusKal                       O(mlogm)           O(n+m)
    Prim                          O((n+m)logn)       O(n+m)  
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int MAXX = 2e5+10;
constexpr i64 INF = 1e18;
struct WEdge {int v;i64 w = 0;};struct DEdge {int u, v;i64 w = 0;};struct Edge {int v;};


//1.最小生成树
namespace MinSpanningTree {
class DSU {
private:
    int n;
    vector<int> fa,sz;
public:
    DSU(int n) : n(n), fa(n + 1), sz(n + 1, 1) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int i){
        if(fa[i] != i){
            fa[i] = find(fa[i]);
        }
        return fa[i];
    }

    bool same(int x, int y){
        return find(x) == find(y);
    }

    bool merge(int x, int y){
        x = find(x), y = find(y);
        if(x == y) return false;
        if(sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
        return true;
    }
    int size(int x){
        return sz[find(x)];
    }
};
//1.1 KrusKal
template <class T = i64>
optional<pair<T, vector<DEdge>>> KrusKal(vector<DEdge> edge, int n) {
    sort(edge.begin(), edge.end(), [](const DEdge& a, const DEdge& b){
        return a.w < b.w;
    });
    DSU d(n);
    vector<DEdge> use;
    T ans = 0;
    for(const auto &e : edge) {
        if(!d.merge(e.u, e.v)) continue;
        ans += e.w;
        use.push_back(e);
        if(use.size() == n - 1) break;
    }
    if(use.size() + 1 != n && n) {
        return nullopt;
    }
    return pair{ans, use};
}
//1.2 Prim
template <class T = i64>
optional<T> Prim(const vector<vector<WEdge>>& g) {
    int n = g.size() - 1;
    vector<T> d(n + 1, INF);
    vector<bool> vis(n + 1);
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> q;
    d[1] = 0;
    q.push({0, 1});
    i64 ans = 0;
    int cnt = 0;
    while(!q.empty()) {
        auto [w, u] = q.top();
        q.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        cnt++;
        ans += w;
        for(const auto &e : g[u]) {
            if(!vis[e.v] && e.w < d[e.v]) {
                d[e.v] = e.w;
                q.push({e.w, e.v});
            }
        }
    }
    if(cnt != n) {
        return nullopt;
    }
    return ans;
}
}




