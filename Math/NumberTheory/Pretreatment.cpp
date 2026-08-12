#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int MAXX=2e5;







namespace Prime{

vector<int> prime, minp;
//欧拉筛素数
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
//区间筛素数[l, r]
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

namespace Euler {

//求n的欧拉函数
i64 get_phi(i64 n) {
    i64 ans = n;
    for(i64 i = 2; i * i <= n; i++){
        if(n % i == 0) {
            ans = ans / i * (i - 1);
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1) ans = ans / n * (n - 1);
    return ans;
}
//欧拉筛欧拉函数
vector<i64> prime, phi;
void get_phis(i64 n) {
    phi.assign(n + 1, 0);
    vector<bool> vis(n + 1);
    phi[1] = 1;
    for(i64 i = 2; i <= n; i++) {
        if(!vis[i]) {
            prime.push_back(i);
            phi[i] = i - 1;
        }
        for(int j = 0; j < prime.size() && 1LL * i * prime[j] <= n; j++) {
            int p = prime[j];
            vis[i * p] = 1;
            if(i % p ==0) {
                phi[i * p] = phi[i] * p;
                break;
            }
            else {
                phi[i * p] = phi[i] * (p - 1);
            }
        }
    }
}
//区间筛欧拉函数
void get_segement_phi(i64 l, i64 r) {
    int n = r - l + 1;
    Prime::Prime_Euler(sqrt(r));
    phi.assign(n, 0);
    vector<i64> v(n);
    for(int i = 0; i < n; i++) {
        phi[i] = l + i;
        v[i] = l + i;
    }
    for(int i = 0; i < prime.size() && 1LL * prime[i] * prime[i] <= r; i++) {
        i64 p = prime[i];
        i64 start = max(p * p, (p + l - 1) / p * p);
        for(i64 j = start; j <= r; j += p) {
            int idx = j - l;
            if(v[idx] % p == 0) {
                phi[idx] = phi[idx] / p * (p - 1);
                while(v[idx] % p == 0) 
                    v[idx] /= p;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        if(v[i] > 1) {
            phi[i] = phi[i] / v[i] * (v[i] - 1);
        }
    }
}




}

namespace Mobius {

//欧拉筛莫比乌斯函数
vector<i64> mu, prime;
void get_mu(i64 n) {
    mu.assign(n + 1, 0);
    mu[1] = 1;
    vector<bool> vis(n + 1);
    for(i64 i = 2; i <= n; i++) {
        if(!vis[i]) {
            prime.push_back(i);
            mu[i] = -1;
        }
        for(int j = 0; j < prime.size() && i * prime[j] <= n; j++) {
            int p = prime[j];
            vis[i * p] = 1;
            if(i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            else {
                mu[i * p] = -mu[i];
            }
        }
    }
}


}
