/*
1.欧拉函数
2.莫比乌斯函数
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;





//1.欧拉函数
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
vector<int> prime, phi, minp;
void phiTable(int n) {
    phi.assign(n + 1, 0);
    minp.assign(n + 1, 0);
    phi[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(!minp[i]) {
            minp[i] = i;
            phi[i] = i - 1;
            prime.emplace_back(i);
        }
        for(int j = 0; j < prime.size() && i * prime[j] <= n; j++) {
            int p = prime[j];
            minp[i * p] = p;
            if(i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
        }
    }
}
//区间筛欧拉函数
void get_segement_phi(i64 l, i64 r) {
    if(l > r) return;
    int n = r - l + 1, m = sqrtl(r);
    vector<bool> is_prime(m + 1);
    for(int i = 2; i <= m; i++){
        if(!is_prime[i]) {
            is_prime[i] = 1;
            prime.emplace_back(i);
        }
        for(int j = i * i; j <= m; j += i) {
            is_prime[j] = 1;
        }
    }
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

//2.莫比乌斯函数
namespace Mobius {

//欧拉筛莫比乌斯函数
vector<int> mu, prime, minp;
void get_mu(int n) {
    mu.assign(n + 1, 0);
    minp.assign(n + 1, 0);
    mu[1] = 1;
    for(i64 i = 2; i <= n; i++) {
        if(!minp[i]) {
            minp[i] = i;
            prime.emplace_back(i);
            mu[i] = -1;
        }
        for(int j = 0; j < prime.size() && i * prime[j] <= n; j++) {
            int p = prime[j];
            minp[i * p] = p;
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