#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;








array<int,MAXX>fa,sz;

void build(int n){
	for(int i=1;i<=n;i++){
		fa[i]=i;
		sz[i]=1;
	}
}

int find(int i){
	if(fa[i]!=i){
		fa[i]=find(fa[i]);
	}
	return fa[i];
}

bool issame(int x,int y){
	return find(x)==find(y);
}

void merge(int x,int y){
	int fx=find(x);
	int fy=find(y);
	if(fx!=fy){
		if(sz[fx]>=sz[fy]){
			sz[fx]+=sz[fy];
			fa[fy]=fx;
		}
		else{
			sz[fy]+=sz[fx];
			fa[fx]=fy;
		}
	}
}



