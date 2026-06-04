#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9+7;




//普通DSU
template <typename T = int>
class DSU {
private:
    int n;
    vector<int> fa,sz;
    vector<T> value;
public:
    DSU(int n) : n(n), fa(n + 1), sz(n + 1, 1), value(n + 1, 0) {
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
        int fx = find(x), fy = find(y);
        if(fx != fy){
            if(sz[fx] >= sz[fy]){
                sz[fx] += sz[fy];
                fa[fy] = fx;
            }
            else{
                sz[fy] += sz[fx];
                fa[fx] = fy;
            }
            return 1;
        }
        return 0;
    }
    T findV(int x){
        return value[find(x)];
    }
    int size(int x){
        return sz[find(x)];
    }
};

//带权DSU
class DSU_Wei {
private:
    int n;
    vector<int> fa, dist, sz;
public:
    DSU_Wei(int n) : fa(n + 1, 0), dist(n + 1, 0), sz(n + 1, 1) {
        iota(fa.begin(), fa.begin() + n + 1, 0);
    }
    int find(int i) {
        if(i != fa[i]) {
            int tmp = fa[i];
            fa[i] = find(fa[i]);
            dist[i] += dist[tmp];
        }
        return fa[i];
    }
    bool merge(int l, int r, int v) {
        int lf = find(l), rf = find(r);
        if(lf != rf) {
            fa[lf] = rf;
            dist[lf] = v + dist[r] - dist[l];
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
            return dist[l] - dist[r];
        } 
        return INF;
    }
};


