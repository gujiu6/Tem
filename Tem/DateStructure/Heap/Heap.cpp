#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;
typedef array<int,2> pii;






array<pii,MAXX>heap;
array<int,MAXX>where;//-1:未进  -2:弹出  >=0:位置
int heapSize;

void swap1(int i,int j){
	int a=heap[i][0];
	int b=heap[j][0];
	where[a]=j;
	where[b]=i;
	swap(heap[i],heap[j]);
}

void heapInsert(int i){
	while(heap[i][1]<heap[(i-1)/2][1]){
		swap1(i,(i-1)/2);
		i=(i-1)/2;
	}
}

void heapify(int i){
	int l=i*2+1;
	while(l<heapSize){
		int best=l+1<heapSize&&heap[l+1][1]<heap[l][1]?l+1:l;
		best=heap[best][1]<heap[i][1]?best:i;
		if(best==i) break;
		swap1(best,i);
		i=best;
		l=i*2+1;
	}
}

bool isEmpty(){
	return heapSize==0;
}

pii pop(){
	auto ans=heap[0];
	swap1(0,--heapSize);
	heapify(0);
	where[ans[1]]=-2;
	return ans;
}

void build(){
	heapSize=0;
	where.fill(-1);
}

