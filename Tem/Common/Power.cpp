#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
const int MOD=1e9+7;
typedef long long ll;







ll power(ll a,ll b){
	ll ans=1;
	a%=MOD;
	while(b>0){
		if(b&1) ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		b>>=1;
	}
	return ans;
}

ll getinv(int n){
    return power(n,MOD-2);
}

