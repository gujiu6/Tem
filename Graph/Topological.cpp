#include <bits/stdc++.h>
using namespace std;
const int MAXX=1000;
typedef long long ll;


array<int, MAXX> h, inDeg, outDeg;
array<int, MAXX << 1> nxt, to;
int cnt;
priority_queue<int, vector<int>, greater<int>>q;

void build(){
    cnt = 1;
    h.fill(0);
    inDeg.fill(0);
    outDeg.fill(0);
}

void addedge(int u, int v){
    nxt[cnt] = h[u];
    to[cnt] = v;
    h[u] = cnt++;
    inDeg[v]++;
    outDeg[u]++;
}

vector<int>topsort(int n){//字典序
    int cur;
    vector<int> ans;
    for(int i = 1;i <= n; i++){
        if(inDeg[i] == 0)
            q.push(i);
    }
    while(!q.empty()){
        cur = q.top();
        ans.push_back(cur);
        q.pop();
        for(int ei = h[cur]; ei != 0; ei = nxt[ei]){
            if(--inDeg[to[ei]] == 0) q.push(to[ei]);
        }
    }
    return ans;
}



