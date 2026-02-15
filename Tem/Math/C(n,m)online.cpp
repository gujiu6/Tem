#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
const int MOD=1e9+7;
typedef long long ll;







array<ll,MAXX+1>f,inv;

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

void CC(){
	f[0]=1;
	for(int i=1;i<=MAXX;i++){
		f[i]=f[i-1]*i%MOD;
	}
	inv[MAXX]=power(f[MAXX],MOD-2);
	for(int i=MAXX-1;i>=0;i--){
		inv[i]=inv[i+1]*(i+1)%MOD;
	}
}

ll C(int n,int m){
	if(m<0||m>n) return 0;
	return f[n]*inv[m]%MOD*inv[n-m]%MOD;
}

ll P(int n,int m){
    if(m<0||m>n) return 0;
    return f[n]*inv[n-m]%MOD;
}

ll prefix_sum_C(int n,int m) {
    if (m < 0) return 0;
    if (m >= n) return power(2,n);
    ll sum = 0;
    for (int k = 0; k <= m; k++) {
        sum = (sum + C(n, k)) % MOD;
    }
    return sum;
}



