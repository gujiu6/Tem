/*
1.单点修改线段树
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;


//1.单点修改线段树
struct Sum {
    i64 val = 0;
    Sum() = default;
    Sum(i64 x): val(x) {}
    friend Sum operator+ (const Sum& a, const Sum& b) {
        return Sum(a.val + b.val);
    }
};
template <class Info>
struct Seg {
    int n;
    vector<Info>  tr;
    Seg(int n = 0): n(n), 
};