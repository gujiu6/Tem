#include <bits/stdc++.h>
using namespace std;
const int MOD=1e9+7 ,MAXX=2e5;
typedef long long ll;





class CC{
private:
    vector<ll>f, inv;
public:
    ll power(ll a,ll b){
        ll ans = 1;
        a %= MOD;
        while(b > 0){
            if(b & 1) ans = (ans * a) % MOD;
            a = (a * a) % MOD;
            b >>= 1;
        }
        return ans;
    }
    CC(int n) : f(n + 1, 1), inv(n + 1, 0){
        for(int i = 1; i <= n; i++){
            f[i] = f[i-1] * i % MOD;
        }
        inv[n] = power(f[n], MOD - 2);
        for(int i = n - 1; i >= 0; i--){
            inv[i] = inv[i + 1] * (i + 1) % MOD;
        }
    }
    ll C(int n, int m){
        if(m < 0 || m > n) return 0;
        return f[n] * inv[m] % MOD * inv[n-m] % MOD;
    }
    ll P(int n, int m){
        if(m < 0 || m > n) return 0;
        return f[n] * inv[n - m] % MOD;
    }
    ll prefix_sum_C(int n, int m) {
        if (m < 0) return 0;
        if (m >= n) return power(2,n);
        ll sum = 0;
        for (int k = 0; k <= m; k++) {
            sum = (sum + C(n, k)) % MOD;
        }
        return sum;
    }
};



//预处理11
array<array<ll, MAXX+1>, MAXX+1> C, pre;
void CC(){
	for(int n = 0;n <= MAXX;n++){
		C[n][0]=C[n][n]=1;
		for(int k = 1; k < n; k++){
			C[n][k] = (C[n-1][k-1] + C[n-1][k]) % MOD;
		}
		pre[n][0] = C[n][0];
		for(int k = 1; k <= n; k++){
			pre[n][k] = (pre[n][k-1] + C[n][k]) % MOD;
		}
	}
}





