#include <bits/stdc++.h>
using namespace std;
const int MAXN=1000,MAXM=2e5+10;
typedef long long ll;








array<int,MAXN>head;
array<int,MAXM>nxt,to,indegree,outdegree;
int cnt;
priority_queue<int,vector<int>,greater<int>>q;

void build(){
    cnt=1;
    head.fill(0);
    indegree.fill(0);
    outdegree.fill(0);
}

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
    indegree[v]++;
    outdegree[u]++;
}

vector<int>topsort(int n){//字典序
    int cur;
    vector<int>ans;
    for(int i=1;i<=n;i++){
        if(indegree[i]==0)
            q.push(i);
    }
    while(!q.empty()){
        cur=q.top();
        ans.push_back(cur);
        q.pop();
        for(int ei=head[cur];ei!=0;ei=nxt[ei]){
            if(--indegree[to[ei]]==0) q.push(to[ei]);
        }
    }
    return ans;
}



