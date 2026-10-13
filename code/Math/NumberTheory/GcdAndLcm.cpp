/*
1.快速幂
2.exgcd
3.求逆元(费马小, exgcd)
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
const int MOD = 1e9+7;

//1.快速幂
i64 pow(i64 a, i64 b, i64 mod = MOD) {
	i64 ans = 1 % mod;
    a = (a % mod + mod) % mod;
	while(b > 0) {
		if(b & 1) ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}
//2.exgcd
tuple<int, int, int> exgcd(i64 a, i64 b) {
    //返回:{gcd(a,b), x, y},满足a*x+b*y=gcd(a,b);gcd取非负
    if(!b) return {abs(a), a < 0 ? -1 : 1, 0};
    auto [g, x, y] = exgcd(b, a % b);
    return {g, y, x - a / b * y};
}
//3.求逆元(费马小)
i64 getinv(i64 a, i64 mod = MOD) {
    return pow(a, mod - 2, mod);
}
//3.求逆元(exgcd)
optional<i64> invMod(i64 a, i64 mod = MOD) {
    auto [g, x, y] = exgcd(a, mod);
    if(g != 1) return nullopt;
    return (x % mod + mod) % mod;
}
//4.CRT
// x ≡ a[0] (mod a[1])
optional<array<i64, 2>> crt(array<i64, 2> a, array<i64, 2> b) {
    auto [g, x, y] = exgcd(a[1], b[1]);
    i128 d = b[0] - a[0];
    if(d % g) {
        return nullopt;
    }
    i64 q = b[1] / g;
    i128 k = 0;
    if(q > 1) {
        k = ((i128)d / g * x % q + q) % q;
    }
    i64 m = (i128)a[1] / g * b[1] ;
    i64 r = (((i128)a[1] * k + a[0]) % m + m) % m;
    return array{r, m};
}