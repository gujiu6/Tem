/*
1.快速幂
2.exgcd
3.求逆元(费马小, exgcd)
*/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using i64 = long long;
using i128 = __int128;
const int MOD = 1e9+7;

i64 mulMod(i64 a, i64 b, i64 mod = MOD) {
    return (i128)((a % mod + mod) % mod) * ((b % mod + mod) % mod) % mod;
}
//1.快速幂
i64 pow(i64 a, i64 b, i64 mod = MOD) {
    assert(mod > 0);
	i64 ans = 1 % mod;
    a = (a % mod + mod) % mod;
	while(b > 0) {
		if(b & 1) ans = mulMod(ans, a, mod);
		a = mulMod(a, a, mod);
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