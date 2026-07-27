#include <bits/stdc++.h>
using namespace std;
const int MAXX = 2e5+10;
using ll=long long;

namespace KrusKal {

int cnt, n;
array<int, MAXX> h, fa, sz;
array<int, MAXX << 1> nxt, to, wei;
void build(){
    cnt = 1;
    fill(h.begin(), h.begin() + n + 1, 0);
    iota(fa.begin(), fa.begin() + n + 1, 0);
    fill(sz.begin(), sz.begin() + n + 1, 1);
}

int find(int i) {
    if(i != fa[i]) {
        fa[i] = find(fa[i]);
    }
    return fa[i];
}
bool merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if(fx != fy) {
        if(sz[fx] >= sz[fy]) {
            sz[fx] += sz[fy];
            fa[fy] = fx;
        }
        else {
            sz[fy] += sz[fx];
            fa[fx] = fy;
        }
        return true;
    }
    return false;
}

void addEdge(int u, int v, int w=0){
    nxt[cnt] = h[u];
    to[cnt] = v;
    wei[cnt] = w;
    h[u] = cnt++;
}
int KrusKal(vector<array<int, 3>> edge, int n){
    int m = edge.size(), cnt=0;
    ll ans=0;
    sort(edge.begin(), edge.end(), [](const auto x, const auto y){
        return x[2] < y[2];
    });
    for(int i = 0; i < m; i++){
        if(merge(edge[i][0], edge[i][1])){
            ans += edge[i][2];
            cnt++;
            addEdge(edge[i][1], edge[i][0], edge[i][2]);
            addEdge(edge[i][0], edge[i][1], edge[i][2]);
        }
    }
    if(cnt == n-1) return ans;
    return -1;
}

}




