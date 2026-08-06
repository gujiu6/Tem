#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using i64 = long long;

//二维前缀和
template <class T = i64>
class Prefix {
    int n, m;
    vector<vector<T>> s;
    Prefix(const vector<vector<T>>& a): n(a.size() - 1), m(a[0].size() - 1), s(n + 1, vector<T>(m + 1)) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
            }
        }
    }
    T sum(int x1, int y1, int x2, int y2)const {
        return s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1];
    }
};

template <class T = i64>
class Diff {
    int n, m;
    vector<vector<T>> d;
    Diff(int n, int m): n(n), m(m), d(n + 2, vector<T>(m + 2)) {}
    void add(int x1, int y1, int x2, int y2, T v) {
        assert(0 <= x1 && x1 <= x2 && x2 <= n);
        assert(0 <= y1 && y1 <= y2 && y2 <= n);
        d[x1][y1] += v;
        d[x2 + 1][y1] -= v;
        d[x1][y2 + 1] -= v;
        d[x2 + 1][y2 + 1] += v;
    }
    vector<vector<T>> qry() const {
        vector<vector<T>> a(n + 1, vector<T>(m + 1));
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                a[i][j] = d[i][j] + d[i][j - 1] + d[i - 1][j] - d[i - 1][j - 1];
            }
        }
        return a;
    }
};