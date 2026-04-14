#include <bits/stdc++.h>
using namespace std;
const int MAXN=5e5+10,MAXM=5e5+10,LIMIT=20;


int cnt,lg2;
array<int,MAXN>h,deep;
array<int,MAXM>nxt,to,wei;
array<array<int,LIMIT>,MAXN>stjump;

void build(int n){
    cnt=1;
    lg2=log2(n);
    h.fill(0);
    deep.fill(0);
}

void addEdge(int u,int v,int w=0){
    nxt[cnt]=h[u];
    to[cnt]=v;
    wei[cnt]=w;
    h[u]=cnt++;
}

void dfs(int u,int f){
    deep[u]=deep[f]+1;
    stjump[u][0]=f;
    for(int p=1;p<=deep[u];p++){
        stjump[u][p]=stjump[stjump[u][p-1]][p-1];
    }
    for(int ei=h[u],v;ei>0;ei=nxt[ei]){
        v=to[ei];
        if(v==f) continue;
        dfs(v,u);
    }
}

int lca(int a,int b){
    if(deep[a]<deep[b]){
        swap(a,b);
    }
    for(int p=lg2;p>=0;p--){
        if(deep[stjump[a][p]]>=deep[b]){
            a=stjump[a][p];
        }
    }
    if(a==b) return a;
    for(int p=lg2;p>=0;p--){
        if(stjump[a][p]!=stjump[b][p]){
            a=stjump[a][p];
            b=stjump[b][p];
        }
    }
    return stjump[a][0];
}



