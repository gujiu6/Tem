#include <bits/stdc++.h>
using namespace std;
const int MOD=1e9+7 ,MAXX=2e5;
typedef long long ll;




//组合数
namespace CC1{

class CC{
private:
    vector<ll>f, inv;
    int mod;
public:
    ll power(ll a, ll b){
        ll ans = 1;
        a %= mod;
        while(b > 0){
            if(b & 1) ans = (ans * a) % mod;
            a = (a * a) % mod;
            b >>= 1;
        }
        return ans;
    }
    CC(int n, int mod) : f(n + 1, 1), inv(n + 1, 0), mod(mod){
        for(int i = 1; i <= n; i++){
            f[i] = f[i-1] * i % mod;
        }
        inv[n] = power(f[n], mod - 2);
        for(int i = n - 1; i >= 0; i--){
            inv[i] = inv[i + 1] * (i + 1) % mod;
        }
    }
    ll C(int n, int m){
        if(m < 0 || m > n) return 0;
        return f[n] * inv[m] % mod * inv[n - m] % mod;
    }
    ll P(int n, int m){
        if(m < 0 || m > n) return 0;
        return f[n] * inv[n - m] % mod;
    }
    ll prefix_sum_C(int n, int m) {
        if (m < 0) return 0;
        if (m >= n) return power(2,n);
        ll sum = 0;
        for (int k = 0; k <= m; k++) {
            sum = (sum + C(n, k)) % mod;
        }
        return sum;
    }
};

}

namespace CC2{

class CC{
private:
    vector<ll>f, inv;
    int mod;
public:
    ll power(ll a, ll b){
        ll ans = 1;
        a %= mod;
        while(b > 0){
            if(b & 1) ans = (ans * a) % mod;
            a = (a * a) % mod;
            b >>= 1;
        }
        return ans;
    }
    CC(int mod) : f(mod + 1, 1), inv(mod + 1, 0), mod(mod){
        for(int i = 1; i < mod; i++){
            f[i] = f[i-1] * i % mod;
        }
        inv[mod - 1] = power(f[mod], mod - 2);
        for(int i = mod - 2; i >= 0; i--){
            inv[i] = inv[i + 1] * (i + 1) % mod;
        }
    }
    ll C(int n, int m){
        if(m < 0 || m > n) return 0;
        return f[n] * inv[m] % mod * inv[n - m] % mod;
    }
    int lucas(int n, int m) {
    if(m == 0) return 1;
        return lucas(n / mod, m / mod) * C(n % mod, m % mod) % mod;
    }
    ll prefix_sum_C(int n, int m) {
        if (m < 0) return 0;
        if (m >= n) return power(2,n);
        ll sum = 0;
        for (int k = 0; k <= m; k++) {
            sum = (sum + C(n, k)) % mod;
        }
        return sum;
    }
};

}



//预处理11
array<array<ll, MAXX+1>, MAXX+1> C, pre;
void init(){
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





