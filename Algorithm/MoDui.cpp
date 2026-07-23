#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 1e5+10, MAXM = 1e5+10;

namespace Common {

int n, m;
array<int, MAXN> a;
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
	int x = a[i];
}

void del(int i) {
	int x = a[i];
}

inline void solve() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	sz = max(1, (int)(n / sqrt(m)));

	for(int i = 1; i <= m; i++) {
		cin >> q[i].l >> q[i].r;
		q[i].id = i;
	}
	sort(q + 1, q + m + 1);

	int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        while (l > q[i].l) add(--l);
        while (r < q[i].r) add(++r);
        while (l < q[i].l) del(l++);
        while (r > q[i].r) del(r--);
        ans[q[i].id] = cur_ans;
    }

	for(int i = 1; i <= m; i++) {
		cout << ans[i] << endl;
	}
}

}


