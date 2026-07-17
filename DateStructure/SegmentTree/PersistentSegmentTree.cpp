#include <bits/stdc++.h>
using namespace std;
const int MAXX = 1e6+10;


//单点修改 单点查询
class PersistentSegmentTree1 {
private:
    vector<int> root, ls, rs, value;
    int cnt, n;
    int build(vector<int>& arr, int l, int r) {
        int rt = ++cnt;
        if(l == r) {
            value[rt] = arr[l];
        }
        else {
            int mid = (l + r) >> 1;
            ls[rt] = build(arr, l, mid);
            rs[rt] = build(arr, mid + 1, r);
        }
        return rt;
    }
    int update(int jobi, int jobv, int l, int r, int i) {
        int rt = ++cnt;
        ls[rt] = ls[i];
        rs[rt] = rs[i];
        value[rt] = value[i];
        if(l == r) {
            value[rt] = jobv;
        }
        else {
            int mid = (l + r) >> 1;
            if(jobi <= mid) {
                ls[rt] = update(jobi, jobv, l, mid, ls[rt]);
            }
            else {
                rs[rt] = update(jobi, jobv, mid + 1, r, rs[rt]);
            }
        }
        return rt;
    }
    int qry(int jobi, int l, int r, int i) {
        if(l == r) {
            return value[i];
        }
        int mid = (l + r) >> 1;
        if(jobi <= mid)
            return qry(jobi, l, mid, ls[i]);
        else
            return qry(jobi, mid + 1, r, rs[i]);
    }
public:
    PersistentSegmentTree1(vector<int>& arr): cnt(0), n(arr.size() - 1), root(MAXX), ls(MAXX * 23), rs(MAXX * 23), value(MAXX * 32) {
        root[0] = build(arr, 1, n);
    }
    void update(int version_past, int version_now, int jobi, int jobv) {
        root[version_now] = update(jobi, jobv, 1, n, root[version_past]);
    }
    int qry(int version_past, int version_now, int jobi) {
        root[version_now] = root[version_past]; 
        return qry(jobi, 1, n, root[version_past]);
    }
};

//单点修改 范围查询
class PersistentSegmentTree2 {
private:
    vector<int> sorted, root, ls, rs, sz; 
    int cnt, n;
    int rank(int x) {
        return lower_bound(sorted.begin() + 1, sorted.end(), x) - sorted.begin();
    }
    int build(int l, int r) {
        int rt = ++cnt;
        sz[rt] = 0;
        if(l < r) {
            int mid = (l + r) >> 1;
            ls[rt] = build(l, mid);
            rs[rt] = build(mid + 1, r);
        }
        return rt;
    }
    int insert(int jobi, int l, int r, int i) {
        int rt = ++cnt;
        ls[rt] = ls[i];
        rs[rt] = rs[i];
        sz[rt] = sz[i] + 1;
        if(l < r) {
            int mid = (l + r) >> 1;
            if(jobi <= mid) {
                ls[rt] = insert(jobi, l, mid, ls[rt]);
            }
            else {
                rs[rt] = insert(jobi, mid + 1, r, rs[rt]);
            }
        }
        return rt;
    }
    int qry(int jobk, int l, int r, int u, int v) {
        if(l == r) {
            return l;
        }
        int lsz = sz[ls[v]] - sz[ls[u]];
        int mid = (l + r) >> 1;
        if(lsz >= jobk) {
            return qry(jobk, l, mid, ls[u], ls[v]);
        }
        else {
            return qry(jobk - lsz, mid + 1, r, rs[u], rs[v]);
        }
    }
public:
    PersistentSegmentTree2(vector<int> arr): cnt(0), sorted(arr), ls(MAXX * 23), rs(MAXX * 23), sz(MAXX * 23) {
        int mx = arr.size() - 1;
        sort(sorted.begin() + 1, sorted.end());
        sorted.erase(unique(sorted.begin() + 1, sorted.end()), sorted.end());
        n = sorted.size() - 1;
        root.resize(mx + 1);
        root[0] = build(1, n);
        for(int i = 1, rk; i <= mx; i++) {
            rk = rank(arr[i]);
            root[i] = insert(rk, 1, n, root[i - 1]);
        }
    }
    int qry(int l, int r, int k) {
        return sorted[qry(k, 1, n, root[l - 1], root[r])];
    }
};