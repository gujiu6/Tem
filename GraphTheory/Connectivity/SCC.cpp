/*
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct WEdge {int v;i64 w = 0;};struct DEdge {int u, v;i64 w = 0;};struct Edge {int v;};

//1.Tarjan 强连通分量
vector<int> TarjanSCC(const vector<vector<Edge>>& g) {
    int n = g.size() - 1;
    int tim = 0, scc = 0;//时间戳,SCC编号
    vector<int> dfn(n + 1), st;
    vector<int> low(n + 1);//从u出发,能够回到的最小dfn编号
    vector<int> bel(n + 1, -1);//答案数组
    vector<bool> on(n + 1);//当前节点是否还在 Tarjan 栈里面

}