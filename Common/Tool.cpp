/*

*/
#include <bits/stdc++.h>
using namespace std;
const int MAXX = 2e5, MOD = 1e9+7;
using i64 = long long;






//快速幂
i64 power(i64 a, i64 b, i64 mod = MOD) {
	i64 ans = 1;
	a = (a % mod + mod) % mod;
	while(b > 0) {
		if(b & 1) ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}
//费马小
i64 getinv(int n, int mod = MOD){
    return power(n, mod - 2, mod);
}

//矩阵快速幂
vector<vector<i64>> mul(const vector<vector<i64>>& a,const vector<vector<i64>>& b) {
    //a : n * k, b : n * m
    int n = a.size();
    int k = a[0].size();
    int m = b[0].size();
    vector<vector<i64>> ans(n, vector<i64>(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            for(int c = 0; c < k; c++){
                ans[i][j] = (ans[i][j] + 1LL * a[i][c] * b[c][j]) % MOD;
            }
        }
    }
    return ans;
}
vector<vector<i64>> power(vector<vector<i64>> A,int p,const vector<vector<i64>>& f) {
    //f : 初始矩阵
    vector<vector<i64>>ans = f;
    while(p > 0) {
        if(p & 1) ans = mul(A, ans);
        A = mul(A, A);
        p >>= 1;
    }
    return ans;
}


//整数开方
i64 my_sqrt(i64 a)
{
    i64 l = 0, r = 5e9+10;
    while(r - l > 1)
    {
        i64 mid = (l + r) / 2;
        if(1ll * mid * mid <= a)l = mid;
        else r = mid;
    }
    return l;
}

//快读
i64 read(){
    bool flag = false;
    i64 ans = 0;
    char c = getchar();
    while(c < '0' || c > '9') {
        if(c == '-') flag = true;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return flag ? -ans : ans;
}
//快写
void write(i64 x){
    if(x == 0){
        putchar('0');
        return;
    }
    if(x < 0){
        putchar('-');
        x = -x;
    }
    char ch[50];
    int index = 0;
    while(x){
        ch[index++] = x % 10 + '0';
        x /= 10;
    }
    for(int i = index - 1; i >= 0; i--) {
        putchar(ch[i]);
    }
}