#include <bits/stdc++.h>
#include <functional>
#include <queue>
#include <vector>
using namespace std;



template <typename T=int>
class DualHeap{
private:
    priority_queue<T>lo;
    priority_queue<T,vector<T>,greater<T>>hi;
    int _k=0,sz=0;
    void balance(){
        while(lo.size()<_k){lo.push(hi.top());hi.pop();}
        while(lo.size()>_k){hi.push(lo.top());lo.pop();}
    }
public:
    DualHeap()=default;
    DualHeap(int k):_k(k){}
    void insert(T x){
        if(!lo.empty()&&x<=lo.top())lo.push(x);
        else hi.push(x);
        sz++;
        balance();
    }
    void set_k(int k){_k=k;balance();}
    T qry() const{return lo.top();}
    
};








