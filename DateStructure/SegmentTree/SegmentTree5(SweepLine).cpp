//扫描线(矩阵面积并)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXX=2e5+10;






array<int, MAXX> len, times, cover;
vector<int> arr;

int init() {
    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), arr.end());
    arr.insert(arr.begin(), 0);
    return arr.size() - 2;
}
int find(int x) {
    return lower_bound(arr.begin() + 1, arr.end(), x) - arr.begin();
}

void up(int l, int r, int i) {
    if(times[i] > 0) {
        cover[i] = len[i];
    }
    else if(l == r) {
        cover[i] = 0;
    }
    else {
        cover[i] = cover[i << 1] + cover[i << 1 | 1];
    }
}

void build(int l, int r, int i) {
    if(l < r) {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
    }
    len[i] = arr[r + 1] - arr[l];
    times[i] = cover[i] = 0;
}

void adds(int jobl, int jobr, int jobv, int l, int r, int i) {
    if(jobl <= l && r <= jobr) {
        times[i] += jobv;
    }
    else {
        int mid = (l + r) >> 1;
        if(jobl <= mid) adds(jobl, jobr, jobv, l, mid, i << 1);
        if(jobr > mid) adds(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
    }
    up(l, r, i);
}

int calc(vector<array<int, 4>>& rec, int n) {
    vector<array<int, 4>> line;
    for(int i = 1; i <= n; i++) {
        auto [x1, y1, x2, y2] = rec[i];
        arr.push_back(y1);arr.push_back(y2);
        line.push_back({x1, y1, y2, 1});
        line.push_back({x2, y1, y2, -1});
    }
    int m = init();
    n <<= 1;
    build(1, m, 1);
    sort(line.begin(), line.end());
    int ans = 0;
    for(int i = 0, pre = line[0][0]; i < n; i++) {
        auto [x, y1, y2, v] = line[i];
        ans += cover[1] * (x - pre);
        pre = x;
        int l = find(y1), r = find(y2);
        if(l > r) swap(l, r);
        adds(l, r - 1, v, 1, m, 1);
    }
    return ans;
}





