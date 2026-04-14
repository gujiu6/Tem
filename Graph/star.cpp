#include <bits/stdc++.h>
using namespace std;
const int MAXN=1005,MAXM=2e5+10;
typedef long long ll;







int cnt;
array<int,MAXN>h;
array<int,MAXM<<1>nxt,to,wei;

void build(){
    cnt=1;
    h.fill(0);
}

void addEdge(int u,int v,int w=0){
    nxt[cnt]=h[u];
    to[cnt]=v;
    wei[cnt]=w;
    h[u]=cnt++;
}




