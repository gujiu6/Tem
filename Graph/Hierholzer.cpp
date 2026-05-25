//欧拉路径
#include <bits/stdc++.h>
#define all(A, i) A.begin() + i, A.end()
using namespace std;
const int MAXN = 5e5 + 10, MAXM = 5e5 + 10;

//有向图
namespace Euler1 {
    array<int, MAXN> h, inDeg, outDeg, Deg, cur;
    array<int, MAXM> to, nxt;
    array<int, MAXM << 1> path;
    int cnt, cntp;

    void build(int n) {
        cnt = 1;
        cntp = 0;
        fill(h.begin(), h.begin() + n + 1, 0);
        fill(inDeg.begin(), inDeg.begin() + n + 1, 0);
        fill(outDeg.begin(), outDeg.begin() + n + 1, 0);
    }

    void addEdge(int u, int v) {
        nxt[cnt] = h[u];
        to[cnt] = v;
        h[u] = cnt++;
        inDeg[v]++;
        outDeg[u]++;
    }

    int directedStart(int n) {
        int start = -1, end = -1;
        for(int i = 1; i <= n; i++) {
            int v = outDeg[i] - inDeg[i];
            if(abs(v) > 1 || (v == 1 && start != -1) || (v == -1 && end != -1))
                return -1;
            if(v == 1) start = i;
            if(v == -1) end = i;
        }
        if((start == -1) ^ (end == -1)) 
            return -1;
        if(start != -1) 
            return start;
        for(int i = 1; i <= n; i++) {
            if(outDeg[i] > 0)
                return i;
        }
        return -1;
    }
    void euler(int u) {
        for(int ei = cur[u]; ei > 0; ei = cur[u]) {
            cur[u] = nxt[ei];
            euler(to[ei]);
        }
        path[++cntp] = u;
    }
};

//无向图
namespace Euler2 {
    array<int, MAXN> h, Deg, cur;
    array<int, MAXM> to, nxt;
    array<int, MAXM << 1> path, vis, eid;
    int cnt, cntp;

    void build(int n) {
        cnt = 1;
        cntp = 0;
        fill(h.begin(), h.begin() + n + 1, 0);
        fill(Deg.begin(), Deg.begin() + n + 1, 0);
    }
    void addEdge(int u, int v, int id) {
        nxt[cnt] = h[u];
        to[cnt] = v;
        Deg[u]++;
        eid[cnt] = id;
        h[u] = cnt++;
    }
    //保证最小字典序
    void init(vector<array<int,3>>& edge) {
        int m = edge.size();
        sort(all(edge, 0), [](auto x, auto y){
            if(x[0] == y[0]) return x[1] > y[1];
            return x[0] < y[0];
        });
        for(int i = 0; i < m; i++) {
            auto [u, v, id] = edge[i];
            addEdge(u, v, id);
        }
    }

    int undirectedStart(int n) {
        int odd = 0;
        for(int i = 1; i <= n; i++) {
            if(Deg[i] & 1)
                odd++;
        }
        if(odd !=0 && odd != 2)
            return -1;
        for(int i = 1; i <= n; i++) {
            if(odd == 0 && Deg[i] >0)
                return i;
            if(odd == 2 && (Deg[i] & 1)) 
                return i;
        }
        return -1;
    }

    void uneuler(int u) {
        for(int ei = cur[u]; ei > 0; ei = cur[u]) {
            cur[u] = nxt[ei];
            if(!vis[eid[ei]]) {
                vis[eid[ei]] = 1;
                uneuler(to[ei]);
            }
        }
        path[++cntp] = u;
    }
};



