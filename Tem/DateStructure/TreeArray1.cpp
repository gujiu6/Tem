#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;





template <typename T=ll>
class BIT{
private:
    int n;
    vector<T> tree;

    inline int low_bit(int i){
        return i&-i;
    }
public:
    BIT(int n):n(n),tree(n+1,0){}
    BIT(vector<T>& arr,int n):BIT(n){
        for(int i=1; i<=n;i++) {
            tree[i]+=arr[i];
            int j=i+low_bit(i);
            if(j<=n) tree[j]+=tree[i];
        }
    }
    void add(int i,T v){
        while(i<=n){
            tree[i]+=v;
            i+=low_bit(i);
        }
    }

    T qry(int i){
        T ans=0;
        while(i>0){
            ans+=tree[i];
            i-=low_bit(i);
        }
        return ans;
    }

    T range_qry(int left,int right){
        return qry(right)-qry(left-1);
    }

    void clear(){
        fill(tree.begin(),tree.end(),0);
    }
};




