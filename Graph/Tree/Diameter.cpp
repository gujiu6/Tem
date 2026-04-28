#include <bits/stdc++.h>
using namespace std;
const int MAXN=5e5+10,MAXM=5e5+10,INF=1e9+10;


array<int,MAXN>h,last,dist;
array<int,MAXM<<1>to,nxt,wei;
int n,cnt,ans;
void build(){
    cnt=1;
    ans=0;
    fill(h.begin(),h.begin()+n+1,0);
}
void addEdge(int u,int v,int w){
    nxt[cnt]=h[u];
    to[cnt]=v;
    wei[cnt]=w;
    h[u]=cnt++;
}

//两遍dfs版本
void dfs(int u,int f,int w){
    last[u]=f;
    dist[u]=dist[f]+w;
    for(int ei=h[u],v;ei>0;ei=nxt[ei]){
        v=to[ei];
        if(v!=f){
            dfs(v,u,wei[ei]);
        }
    }
}
array<int,3> road(){
    dfs(1,0,0);
    int st=1,ed=1,dis;
    for(int i=2;i<=n;i++){
        if(dist[i]>dist[st]){
            st=i;
        }
    }
    dfs(st,0,0);
    for(int i=2;i<=n;i++){
        if(dist[i]>dist[ed]){
            ed=i;
        }
    }
    dis=dist[ed];
    return {st,ed,dis};
}

//树上dp
void dp(int u,int f){
    for(int ei=h[u],v;ei>0;ei=nxt[ei]){
        v=to[ei];
        if(v!=f){
            dp(v,u);
        }
    }
    for(int ei=h[u],v;ei>0;ei=nxt[ei]){
        v=to[ei];
        if(v!=f){
            ans=max(ans,dist[u]+dist[v]+wei[ei]);
            dist[u]=max(dist[u],dist[v]+wei[ei]);
        }
    }
}
