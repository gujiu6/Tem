#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9+7;
using i64 = long long;



//1.普通DSU
class DSU {
    int n;
    vector<int> fa,sz;
    DSU(int n): n(n), fa(n + 1), sz(n + 1, 1) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int i){
        if(fa[i] != i){
            fa[i] = find(fa[i]);
        }
        return fa[i];
    }
    bool merge(int x, int y){
        x = find(x), y = find(y);
        if(x == y) return false;
        if(sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
        return true;
    }
    bool same(int x, int y){
        return find(x) == find(y);
    }
    int size(int x){
        return sz[find(x)];
    }
};

//2.带权DSU
template <typename T = i64>
class WDSU {
    int n;
    vector<int> fa, sz;
    vector<T> w;
    WDSU(int n): n(n), fa(n + 1, 0), w(n + 1, 0), sz(n + 1, 1) {
        iota(fa.begin(), fa.begin() + n + 1, 0);
    }
    int find(int i) {
        if(i != fa[i]) {
            int f = fa[i];
            fa[i] = find(fa[i]);
            w[i] += w[f];
        }
        return fa[i];
    }
    bool merge(int x, int y, T d) {
        int fx = find(x), fy = find(y);
        T v = d + w[x] - w[y];
        if(fx == fy) {
            return v == T{};
        }
        if(sz[fx] < sz[fy]) {
            fa[fx] = fy;
            w[fx] = -v;
            sz[fy] += sz[fx];
        }
        else {
            fa[fy] = fx;
            w[fy] = v;
            sz[fx] += sz[fy];
        }
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int qry(int x, int y) {
        assert(same(x, y));
        return w[y] - w[x];
    }
};


