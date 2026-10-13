/*
1.欧拉筛素数
2.区间筛素数[l, r]
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int MAXX=2e5;







namespace Prime{
//1.欧拉筛素数
vector<int> prime, minp;
void Prime_Euler(int n){
    minp.assign(n + 1, 0);
    for(int i = 2; i <= n; i++){
        if(!minp[i]) {
            minp[i] = i;
            prime.emplace_back(i);
        }
        for(int j = 0;j < prime.size() && i * prime[j] <= n; j++){
            minp[i * prime[j]] = prime[j];
            if(i % prime[j] == 0) break;
        }
    }
}
//2.区间筛素数[l, r]
vector<i64> SegmentPrimes(i64 l, i64 r) {
    l = max(l, 2LL);
    if(l > r) return {};
    int n = sqrtl(r) + 1;
    vector<bool> a(n + 1, true);
    vector<bool> b(r - l + 1, true);
    vector<int> p;
    for(int i = 2; i <= n; i++) {
        if(!a[i]) continue;
        p.emplace_back(i);
        if(1LL * i * i <= n) {
            for(int j = i * i; j <= n; j += i) {
                a[j] = false;
            }
        }
    }
    for (i64 x : p) {
        i64 s = max(x * x, (l + x - 1) / x * x);
        for (i64 y = s; y <= r; y += x) {
            b[y - l] = false;
        }
    }
    vector<i64> ans;
    for(i64 x = l; x <= r; x++) {
        if(b[x - l]) {
            ans.emplace_back(x);
        }
    }
    return ans;
}

}




