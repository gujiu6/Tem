#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;







vector<ll>prime;

void Prime(ll n){
    vector<bool>nums(n+1);
    for(int i=2;i<=n;i++){
        if(!nums[i]) prime.emplace_back(i);
        for(int j=0;j<prime.size()&&i*prime[j]<=n;j++){
            nums[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
}



