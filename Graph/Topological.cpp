#include <bits/stdc++.h>
using namespace std;
const int MAXX=1000;
typedef long long ll;


optional<vector<int>> TopSort(vector<vector<int>>& g, vector<int> inDeg) {
    int n = g.size() - 1;
    vector<int> ans;
    priority_queue<int, vector<int>, greater<int>> q;
    for(int i = 1; i <= n; i++) {
        if(inDeg[i] == 0) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        auto u = q.top();q.pop();
        ans.push_back(u);
        for(int v : g[u]) {
            if(--inDeg[v] == 0) {
                q.push(v);
            }
        }
    }
    if(ans.size() != n) return nullopt;
    return ans;
}



