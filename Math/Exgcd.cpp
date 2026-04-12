#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;







ll exgcd(ll a,ll b,ll &x,ll &y){
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    ll res=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return res;
}



