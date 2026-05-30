#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;






//快速幂
ll power(ll a,ll b,ll MOD=1e9+7){
	ll ans=1;
	a%=MOD;
	while(b>0){
		if(b&1) ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		b>>=1;
	}
	return ans;
}

ll getinv(int n,int MOD=1e9+7){
    return power(n,MOD-2,MOD);
}

//整数开方
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

//快读
ll read(){
    bool flag=false;
    ll ans=0;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') flag=true;
        c=getchar();
    }
    while(isdigit(c)){
        ans=ans*10+c-'0';
        c=getchar();
    }
    return flag?-ans:ans;
}
//快写
void write(ll x){
    if(x==0){
        putchar('0');
        return;
    }
    if(x<0){
        putchar('-');
        x=-x;
    }
    char ch[50];
    int index=0;
    while(x){
        ch[index++]=x%10+'0';
        x/=10;
    }
    for(int i=index-1;i>=0;i--){
        putchar(ch[i]);
    }
}