#include <bits/stdc++.h>
using namespace std;
const int MAXN=1005,MAXM=2e5+10;
typedef long long ll;







int cnt;
array<int,MAXN>h;
array<int,MAXM>nxt,to,wei;

void build(){
    cnt=1;
    h.fill(0);
}

void addEdge(int u,int v,int w){
    nxt[cnt]=h[u];
    to[cnt]=v;
    wei[cnt]=w;
    h[u]=cnt++;
}




