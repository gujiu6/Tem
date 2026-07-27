#include <bits/stdc++.h>
using namespace std;
const int MAXX = 2e5+10;
using ll=long long;

namespace KrusKal {

int cnt, n;
array<int, MAXX> h, fa, sz;
array<int, MAXX << 1> nxt, to, wei;
void build(){
    cnt = 1;
    fill(h.begin(), h.begin() + n + 1, 0);
    iota(fa.begin(), fa.begin() + n + 1, 0);
    fill(sz.begin(), sz.begin() + n + 1, 1);
}

int find(int i) {
    if(i != fa[i]) {
        fa[i] = find(fa[i]);
    }
    return fa[i];
}
bool merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if(fx != fy) {
        if(sz[fx] >= sz[fy]) {
            sz[fx] += sz[fy];
            fa[fy] = fx;
        }
        else {
            sz[fy] += sz[fx];
            fa[fx] = fy;
        }
        return true;
    }
    return false;
}

void addEdge(int u, int v, int w=0){
    nxt[cnt] = h[u];
    to[cnt] = v;
    wei[cnt] = w;
    h[u] = cnt++;
}
int KrusKal(vector<array<int, 3>> edge, int n){
    int m = edge.size(), cnt=0;
    ll ans=0;
    sort(edge.begin(), edge.end(), [](const auto x, const auto y){
        return x[2] < y[2];
    });
    for(int i = 0; i < m; i++){
        if(merge(edge[i][0], edge[i][1])){
            ans += edge[i][2];
            cnt++;
            addEdge(edge[i][1], edge[i][0], edge[i][2]);
            addEdge(edge[i][0], edge[i][1], edge[i][2]);
        }
    }
    if(cnt == n-1) return ans;
    return -1;
}

}

namespace Prim {

int cnt, nodeCnt, n;
array<int, MAXX> h;
array<int, MAXX << 1> nxt, to, wei;

array<array<int,2>,MAXX>heap;
array<int,MAXX>where;//-1:未进  -2:弹出  >=0:位置
int heapSize;

void build(){
    cnt = 1;
    heapSize = 0;
    nodeCnt = 0;
    fill(h.begin(), h.begin() + n + 1, 0);
    where.fill(-1);
}

void addEdge(int u, int v, int w = 0){
    nxt[cnt] = h[u];
    to[cnt] = v;
    wei[cnt] = w;
    h[u] = cnt++;
}

void swap1(int i, int j){
	int a = heap[i][0];
	int b = heap[j][0];
	where[a] = j;
	where[b] = i;
	swap(heap[i], heap[j]);
}

void heapInsert(int i){
	while(heap[i][1] < heap[(i - 1) / 2][1]){
		swap1(i, (i - 1) / 2);
		i = (i - 1) / 2;
	}
}

void heapify(int i){
	int l = i * 2 + 1;
	while(l < heapSize){
		int best = l + 1 < heapSize && heap[l + 1][1] < heap[l][1] ? l + 1 : l;
		best = heap[best][1] < heap[i][1] ? best : i;
		if(best == i) break;
		swap1(best, i);
		i = best;
		l = i*2+1;
	}
}

bool isEmpty(){
	return heapSize == 0;
}

array<int,2> pop(){
    int u,w;
	u = heap[0][0];
	w = heap[0][1];
	swap1(0, --heapSize);
	heapify(0);
	where[u] = -2;
	nodeCnt++;
    return {u, w};
}

void addOrUpdateOrIgnore(int ei){
	int v = to[ei];
	int w = wei[ei];
	if(where[v] == -1){
		heap[heapSize][0] = v;
		heap[heapSize][1] = w;
		where[v] = heapSize++;
		heapInsert(where[v]);
	}
	else if(where[v] >= 0){
		heap[where[v]][1] = min(heap[where[v]][1], w);
		heapInsert(where[v]);
	}
}

int Prim(){
	nodeCnt = 1;
	where[1] = -2;
	for(int ei = h[1]; ei > 0; ei = nxt[ei]){
		addOrUpdateOrIgnore(ei);
	}
	int ans = 0;
	while(!isEmpty()){
		auto [u, w] = pop();
		ans += w;
		for(int ei = h[u]; ei > 0; ei = nxt[ei]){
			addOrUpdateOrIgnore(ei);
		}
	}
	return ans;
}

}



