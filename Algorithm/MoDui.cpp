#include <bits/stdc++.h>
using namespace std;
using ll = long long;



//普通莫队
namespace Common {

struct Query {
    int l, r, t, id;
};
template <class Ans, class AddL, class AddR, class DelL, class DelR, class Get>
vector<Ans> mo(int n, vector<Query> q, AddL addL, AddR addR, DelL delL, DelR delR, Get get) {
    int m = q.size() - 1;
    int sz  = max(1, (int)(n / sqrt(m)));
    sort(q.begin(), q.end(), [&](const Query &x, const Query &y){
        auto xl = x.l / sz, yl = y.l / sz;
        if(xl != yl) return xl < yl;
        return xl & 1 ? x.r > y.r : x.r < x.r;
    });
    vector<Ans> ans(m + 1);
    for(int l = 1, r = 0, i = 1; i <= m; i++) {
        int jobl = q[i].l, jobr = q[i].r, jobid = q[i].id;
        while (l > jobl) addL(--l);
        while (r < jobr) addR(++r);
        while (l < jobl) delL(l++);
        while (r > jobr) delR(r--);
        ans[jobid] = get();
    }
    return ans;
}

}

//带修莫队
namespace Modify {

struct Query {
    int l, r, t, id;
};
//change要交换数组元素和修改元素达到兼容效果
template <class Ans, class Add, class Del, class Change, class Get>
vector<Ans> moModify(int n, vector<Query> q, Add add, Del del, Change change, Get get) {
    int m = q.size() - 1;
    int sz  = max(1, (int)pow(n, 2.0 / 3));
    sort(q.begin(), q.end(), [&](const Query &x, const Query &y){
        auto xl = x.l / sz, yl = y.l / sz;
        if(xl != yl) return xl < yl;
        auto xr = x.r / sz, yr = y.r / sz;
        if(xr != yr) return xl & 1 ? xr > yr : xr < yr;
        return xr & 1 ? x.t > y.t : x.t < y.t;
    });
    vector<Ans> ans(m + 1);
    for(int l = 1, r = 0, t = 0, i = 1; i <= m; i++) {
        int jobl = q[i].l, jobr = q[i].r, jobt = q[i].t, jobid = q[i].id;
        while(t < jobt) change(l, r, ++t);
        while(t > jobt) change(l, r, t--);
        while(l > jobl) add(--l);
        while(r < jobr) add(++r);
        while(l < jobl) del(l++);
        while(r > jobr) del(r--);
        ans[jobid] = get();
    }
}

}
