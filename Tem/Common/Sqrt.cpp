#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;







ll my_sqrt(ll a)
{
    ll l=0,r=5e9+10;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        if(1ll*mid*mid<=a)l=mid;
        else r=mid;
    }
    return l;
}


