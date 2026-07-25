#include <bits/stdc++.h>
using namespace std;
using ll = long long;



//普通莫队
namespace Common {

const int MAXN = 1e5+10, MAXM = 1e5+10;
int n, m;
array<int, MAXN> arr;
array<ll, MAXM> ans;

int sz;
ll cur_ans;
struct Query {
    int l, r, id;
    bool operator<(const Query &other) const {
        int b1 = l / sz;
        int b2 = other.l / sz;
        if (b1 != b2) return b1 < b2;
        return (b1 & 1) ? (r < other.r) : (r > other.r);
    }
} q[MAXM];

void add(int i) {
	ll x = arr[i];
}

void del(int i) {
	ll x = arr[i];
}

inline void solve() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> arr[i];
	}

	sz = max(1, (int)(n / sqrt(m)));

	for(int i = 1; i <= m; i++) {
		cin >> q[i].l >> q[i].r;
		q[i].id = i;
	}
	sort(q + 1, q + m + 1);

	int l = 1, r = 0;
	cur_ans = 0;
    for (int i = 1; i <= m; i++) {
		int jobl = q[i].l, jobr = q[i].r;
        while (l > jobl) add(--l);
        while (r < jobr) add(++r);
        while (l < jobl) del(l++);
        while (r > jobr) del(r--);
        ans[q[i].id] = cur_ans;
    }

	for(int i = 1; i <= m; i++) {
		cout << ans[i] << endl;
	}
}

}

//带修莫队
namespace Modify {

const int MAXN = 133340, MAXM = 133340;

int n, m;
array<int, MAXN> arr;
array<ll, MAXM> ans;

int sz;
ll cur_ans;

struct Query {
    int l, r;
    int t;
    int id;

    bool operator<(const Query &other) const {
        int bl1 = l / sz;
        int bl2 = other.l / sz;
        if (bl1 != bl2) return bl1 < bl2;

        int br1 = r / sz;
        int br2 = other.r / sz;
        if (br1 != br2) return br1 < br2;

        return t < other.t;
    }
} q[MAXN];

struct Modify {
    int pos;
    int val;
} update[MAXM];

int qcnt = 0;
int ccnt = 0;

void add(int i) {
    int x = arr[i];
}

void del(int i) {
    int x = arr[i];
}

void moveTime(int l, int r, int t){
    int p = update[t].pos;
    int v = update[t].val;
    if(l <= p && p <= r){
        del(p);
        swap(arr[p], update[t].val);
        add(p);
    }else{
        swap(arr[p], update[t].val);
    }
}


inline void solve(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> arr[i];
    sz = max(1, (int)pow(n, 2.0 / 3));
    qcnt = ccnt = 0;
    for(int i = 1; i <= m; i++){
        char op;
        cin >> op;
		//查询
        if(op == 'Q'){
            ++qcnt;
            cin >> q[qcnt].l >> q[qcnt].r;
            if(q[qcnt].l > q[qcnt].r)
                swap(q[qcnt].l, q[qcnt].r);
            q[qcnt].t = ccnt;
            q[qcnt].id = qcnt;
        }
		//修改
        else{
            ++ccnt;
            cin >> update[ccnt].pos >> update[ccnt].val;
        }
    }
    sort(q + 1, q + qcnt + 1);

    int l = 1, r = 0, t = 0;
    cur_ans = 0;
    for(int i = 1; i <= qcnt; i++){
        int jobl = q[i].l, jobr = q[i].r, jobt = q[i].t;
        while(l > jobl) add(--l);
        while(r < jobr) add(++r);
        while(l < jobl) del(l++);
        while(r > jobr) del(r--);

        while(t < jobt)
            moveTime(l, r, ++t);

        while(t > jobt)
            moveTime(l, r, t--);
        ans[q[i].id] = cur_ans;
    }

    for(int i = 1; i <= qcnt; i++)
        cout << ans[i] << endl;
}

}
