#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;







ll n,m;
array<int,MAXX>tree;

void build(){
	tree.fill(0);
}

ll low_bit(ll &i){
    return i&-i;
}

void add(ll i,ll v){
    while(i<=n){
        tree[i]+=v;
        i+=low_bit(i);
    }
}

ll sum(ll i){
    ll ans=0;
    while(i>=1){
        ans+=tree[i];
        i-=low_bit(i);
    }
    return ans;
}

ll rangesum(ll left,ll right){
    return sum(right)-sum(left-1);
}




