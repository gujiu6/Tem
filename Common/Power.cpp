#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;







ll power(ll a,ll b,ll MOD=1e9+7){
	ll ans=1;
	a%=MOD;
	while(b>0){
		if(b&1) ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		b>>=1;
	}
	return ans;
}

ll getinv(int n,int MOD=1e9+7){
    return power(n,MOD-2,MOD);
}

