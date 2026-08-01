#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9+7;




//普通DSU
template <typename T = int>
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

    bool is_same(int x, int y){
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

//带权DSU
class WDSU {
private:
    int n;
    vector<int> fa, w, sz;
public:
    WDSU(int n) : n(n), fa(n + 1, 0), w(n + 1, 0), sz(n + 1, 1) {
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
    bool merge(int l, int r, int v) {
        int lf = find(l), rf = find(r);
        if(lf != rf) {
            fa[lf] = rf;
            w[lf] = v + w[r] - w[l];
            sz[rf] += sz[lf]; 
            return true;
        }
        return false;
    }
    bool is_same(int l, int r) {
        return find(l) == find(r);
    }
    int query(int l, int r) {
        if(is_same(l, r)) {
            return w[l] - w[r];
        } 
        return INF;
    }
};


