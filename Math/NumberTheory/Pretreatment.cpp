#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;






namespace Prime{

vector<ll>prime;
//埃氏筛素数
void Prime_Eratoasthenes(ll n){
    vector<bool>nums(n+1);
    for(int i=2;i<=n;i++){
        if(!nums[i]) prime.emplace_back(i);
        for(int j=0;j<prime.size()&&i*prime[j]<=n;j++){
            nums[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
}
//欧拉筛素数
void Prime_Euler(ll n){
    vector<bool>nums(n+1);
    for(int i=2;i<=n;i++){
        if(!nums[i]) prime.emplace_back(i);
        for(int j=0;j<prime.size()&&i*prime[j]<=n;j++){
            nums[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
}

}

namespace Euler {

//求n的欧拉函数
ll get_phi(ll n) {
    ll ans = n;
    for(ll i = 2; i * i <= n; i++){
        if(n % i == 0) {
            ans = ans / i *(i - 1);
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1) ans = ans / n * (n - 1);
    return ans;
}
//欧拉筛欧拉函数
vector<int> prime, phi;
void get_phi(int n) {
    phi.assign(n + 1, 0);
    vector<bool> vis(n + 1);
    phi[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(!vis[i]) {
            prime.push_back(i);
            phi[i] = i - 1;
        }
        for(int j = 0; j < prime.size() && i * prime[j] <= n; j++) {
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
//欧拉筛莫比乌斯函数
vector<int> mu;
void get_mu(int n) {
    mu.assign(n + 1, 0);
    mu[1] = 1;
    vector<bool> vis(n + 1);
    for(int i = 2; i <= n; i++) {
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
