#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
const int MOD=1e9+7;
typedef long long ll;







array<array<ll,MAXX+1>,MAXX+1>C,pre;


void CC(){
	for(int n=0;n<=MAXX;n++){
		C[n][0]=C[n][n]=1;
		for(int k=1;k<n;k++){
			C[n][k]=(C[n-1][k-1]+C[n-1][k])%MOD;
		}
		pre[n][0]=C[n][0];
		for(int k=1;k<=n;k++){
			pre[n][k]=(pre[n][k-1]+C[n][k])%MOD;
		}
	}
}



