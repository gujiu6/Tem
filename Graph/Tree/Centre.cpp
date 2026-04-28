#include <bits/stdc++.h>
using namespace std;
const int MAXN=5e5+10,MAXM=5e5+10,INF=1e9+7;

int n,cnt,best;
array<int,MAXN>h,sz,maxsub;
array<int,MAXM>to,nxt;
vector<int>ans;
void build(){
    cnt=1;
    best=INF;
    fill(h.begin(),h.begin()+n+1,0);
}

void addEdge(int u,int v){
    nxt[cnt]=h[u];
    to[cnt]=v;
    h[u]=cnt++;
}

//第一种求法
void dfs1(int u,int f){
    sz[u]=1;
    maxsub[u]=0;
    for(int ei=h[u],v;ei>0;ei=nxt[ei]){
        v=to[ei];
        if(v!=f){
            dfs1(v,u);
            sz[u]+=sz[v];
            maxsub[u]=max(maxsub[u],sz[v]);
        }
    }
    maxsub[u]=max(maxsub[u],n-sz[u]);
}
void calc(){
    for(int i=1;i<=n;i++){
        if(maxsub[i]<=n/2){
            ans.push_back(i);
        }
    }
}

//第二种求法
void dfs2(int u,int f){
    sz[u]=1;
    int maxsub=0;
    for(int ei=h[u],v;ei>0;ei=nxt[ei]){
        v=to[ei];
        if(v!=f){
            dfs2(v,u);
            sz[u]+=sz[v];
            maxsub=max(maxsub,sz[v]);
        }
    }
    maxsub=max(maxsub,n-sz[u]);
    if(maxsub<best){
        ans.resize(1,u);
    }
    else if(maxsub==best){
        ans.push_back(u);
    }
}


