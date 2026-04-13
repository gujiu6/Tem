#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5+10,MAXM=2e5+10;
const int INF=1e9+7;


int cnt;
array<int,MAXM>to,wei,nxt;
array<int,MAXN>h;

array<int,MAXN>heap;
array<int,MAXN>where,dis;//-1:未进  -2:弹出  >=0:位置
int heapSize;

void build(){
    cnt=1;
    heapSize=0;
    h.fill(0);
    where.fill(-1);
    dis.fill(INF);
}

void addEdge(int u,int v,int w){
    nxt[cnt]=h[u];
    to[cnt]=v;
    wei[cnt]=w;
    h[u]=cnt++;
}


void swap1(int i,int j){
	swap(heap[i],heap[j]);
    where[heap[i]]=i;
    where[heap[j]]=j;
}

void heapInsert(int i){
	while(dis[heap[i]]<dis[heap[(i-1)/2]]){
		swap1(i,(i-1)/2);
		i=(i-1)/2;
	}
}

void heapify(int i){
	int l=i*2+1;
	while(l<heapSize){
		int best=l+1<heapSize&&dis[heap[l+1]]<dis[heap[l]]?l+1:l;
		best=dis[heap[best]]<dis[heap[i]]?best:i;
		if(best==i) break;
		swap1(best,i);
		i=best;
		l=i*2+1;
	}
}

bool isEmpty(){
	return heapSize==0;
}

int pop(){
    int ans=heap[0];
	swap1(0,--heapSize);
	heapify(0);
	where[ans]=-2;
	return ans;
}


void addOrUpdateOrIgnore(int v,int c){
	if(where[v]==-1){
		heap[heapSize]=v;
		where[v]=heapSize++;
        dis[v]=c;
		heapInsert(where[v]);
	}
	else if(where[v]>=0){
		dis[v]=min(dis[v],c);
		heapInsert(where[v]);
	}
}








int Dijkstra(){
    int n,m;cin>>n>>m;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addEdge(u,v,w);
    }

}





