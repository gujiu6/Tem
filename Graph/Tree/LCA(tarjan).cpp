#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e5+10,MAXM=5e5+10;
using pii=array<int,2>;

int cnt;
array<int,MAXN>h,fa,vis;
array<int,MAXM<<1>nxt,to,wei;
vector<vector<pii>>Question(MAXN);
vector<int>lca;

void build(int n){
    cnt=1;
    fill(h.begin(),h.begin()+n+1,0);
    fill(vis.begin(),vis.begin()+n+1,0);
    for(int i=1;i<=n;i++) 
        fa[i]=i;
}

void addEdge(int u,int v,int w=0){
    nxt[cnt]=h[u];
    to[cnt]=v;
    wei[cnt]=w;
    h[u]=cnt++;
}

int find(int i){
    if(i!=fa[i]){
        fa[i]=find(fa[i]);
    }
    return fa[i];
}

void tarjan(int u,int f){
    vis[u]=1;
    for(int ei=h[u],v;ei>0;ei=nxt[ei]){
        v=to[ei];
        if(v!=f){
            tarjan(v,u);
            fa[v]=u;
        }
    }
    for(auto [v,id]:Question[u]){
        if(vis[v]){
            lca[id]=find(v);
        }
    }
}







