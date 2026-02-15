


const int LIMIT=20;
array<int,MAXX>lg2;
array<array<int,LIMIT>,MAXX>st;//max


void build(vector<int>&arr,int n){
	lg2[0]=-1;
	for(int i=1;i<=n;i++){
		lg2[i]=lg2[i>>1]+1;
		st[i][0]=arr[i];
	}
	for(int p=1;p<=log2[n];p++){
		for(int i=1;i+(1LL<<p)-1<=n;i++){
			st[i][p]=max(st[i][p-1],st[i+(1LL<<(p-1))][p-1]);
		}
	}
}


int qry(int l,int r){
	if(l>r) return -INF;
	int p=lg2[r-l+1];
	int ans=max(st[l][p],st[r-(1LL<<p)+1][p]);
	
	return ans;
}



