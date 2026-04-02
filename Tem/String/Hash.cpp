#include <bits/stdc++.h>
using namespace std;
const int MOD=1e9+7;
typedef long long ll;







class Hash{
private:
    vector<ll>h,p;
    const ll B=131;
public:
    Hash(const string& s){
        int n=s.size();
        h.resize(n+1,0);
        p.resize(n+1,1);
        for(int i=0;i<n;i++){
            p[i+1]=p[i]*B%MOD;
            h[i+1]=(h[i]*B+s[i])%MOD;
        }
    }
    ll get(int l,int r){
        ll v=h[r]-h[l-1]*p[r-l+1]%MOD;
        return (v%MOD+MOD)%MOD;
    }
};







