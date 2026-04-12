#include <bits/stdc++.h>
using namespace std;
const int INF=1e9+7;



template <typename T=int>
class ST{
private:
    int n;
    vector<T>lg2;
    vector<vector<T>>st;
    T (*op)(T,T);
public:
    ST(vector<T>&arr,int n,T (*operation)(T,T)):n(n),op(operation){
        int LIMIT=log2(n)+1;
        st.assign(n+1,vector<T>(LIMIT+1));
        lg2.assign(n+1,0);
        lg2[0]=-1;
        for(int i=1;i<=n;i++){
            lg2[i]=lg2[i>>1]+1;
            st[i][0]=arr[i];
        }
        for(int p=1;p<=lg2[n];p++){
            for(int i=1;i+(1LL<<p)-1<=n;i++){
                st[i][p]=op(st[i][p-1],st[i+(1LL<<(p-1))][p-1]);
            }
        }
    }

    T qry(int l,int r){
        if(l>r) return -INF;
        int p=lg2[r-l+1];
        int ans=op(st[l][p],st[r-(1LL<<p)+1][p]);
        return ans;
    }
};



