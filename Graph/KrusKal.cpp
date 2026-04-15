#include <bits/stdc++.h>
#define all(A,i) A.begin()+i, A.end()
using namespace std;
const int MAXN=2e5+10,MAXM=5e5+10;
using ll=long long;

template <typename T = int>
class DSU{
private:
    int n;
    int row,col;
    vector<T>fa,sz;
public:
    DSU(int n):n(n),row(0),col(0),fa(n+1),sz(n+1,1){
        iota(fa.begin(),fa.end(),0);
    }
    DSU(int r,int c):n(r*c),row(r),col(c),fa(r*c+1),sz(r*c+1,1){
        iota(fa.begin(),fa.end(),0);
    }

    T find(T i){
        if(fa[i]!=i){
            fa[i]=find(fa[i]);
        }
        return fa[i];
    }

    bool issame(T x,T y){
        return find(x)==find(y);
    }

    bool merge(T x,T y){
        int fx=find(x);
        int fy=find(y);
        if(fx!=fy){
            if(sz[fx]>=sz[fy]){
                sz[fx]+=sz[fy];
                fa[fy]=fx;
            }
            else{
                sz[fy]+=sz[fx];
                fa[fx]=fy;
            }
            return 1;
        }
        return 0;
    }

    T size(T x){
        return sz[find(x)];
    }
    int id(int i,int j){
        return i*col+j;
    }
};
int cnt;
array<int,MAXN>h;
array<int,MAXM<<1>nxt,to,wei;
DSU dsu(MAXN);




void build(int n){
    cnt=1;
    h.fill(0);
    dsu=DSU(n);
}

void addEdge(int u,int v,int w=0){
    nxt[cnt]=h[u];
    to[cnt]=v;
    wei[cnt]=w;
    h[u]=cnt++;
}





int KrusKal(vector<array<int,3>>edge,int n){
    int m=edge.size(),cnt=0;
    ll ans=0;
    sort(all(edge,0),[](const auto x,const auto y){
        return x[2]<y[2];
    });
    for(int i=0;i<m;i++){
        if(dsu.merge(edge[i][0],edge[i][1])){
            ans+=edge[i][2];
            cnt++;
            addEdge(edge[i][1],edge[i][0],edge[i][2]);
            addEdge(edge[i][0],edge[i][1],edge[i][2]);
        }
    }
    if(cnt==n-1) return ans;
    return -1;
    
}



