#include <bits/stdc++.h>
using namespace std;
const int MAXN=1000,MAXM=2e5+10;
typedef long long ll;








array<int,MAXN>head,inDeg,outDeg;
array<int,MAXM<<1>nxt,to;
int cnt;
priority_queue<int,vector<int>,greater<int>>q;

void build(){
    cnt=1;
    head.fill(0);
    inDeg.fill(0);
    outDeg.fill(0);
}

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
    inDeg[v]++;
    outDeg[u]++;
}

vector<int>topsort(int n){//字典序
    int cur;
    vector<int>ans;
    for(int i=1;i<=n;i++){
        if(inDeg[i]==0)
            q.push(i);
    }
    while(!q.empty()){
        cur=q.top();
        ans.push_back(cur);
        q.pop();
        for(int ei=head[cur];ei!=0;ei=nxt[ei]){
            if(--inDeg[to[ei]]==0) q.push(to[ei]);
        }
    }
    return ans;
}



