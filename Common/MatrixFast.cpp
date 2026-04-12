#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
const int MOD=1e9+7;
typedef long long ll;





vector<vector<ll>>mul(const vector<vector<ll>>&a,const vector<vector<ll>>&b){
    int n=a.size();
    int k=a[0].size();
    int m=b[0].size();
    vector<vector<ll>>ans(n,vector<ll>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int c=0;c<k;c++){
                ans[i][j]+=a[i][c]*b[c][j];
            }
            ans[i][j]%=MOD;
        }
    }
    return ans;
}

vector<vector<ll>>power(vector<vector<ll>>a,int p,const vector<vector<ll>>&f){
    vector<vector<ll>>ans=f;
    while(p>0){
        if(p&1) ans=mul(a,ans);
        a=mul(a,a);
        p>>=1;
    }
    return ans;
}



