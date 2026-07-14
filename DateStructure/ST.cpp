#include <bits/stdc++.h>
using namespace std;
const int INF=1e9+7;

namespace ST1 {

template <typename T , typename F>
class ST {
private:
    int n;
    vector<T> lg2;
    vector<vector<T>> st;
    F op;
public:
    ST(vector<T>&arr, int n, F f) : n(n), op(f) {
        int LIMIT = log2(n) + 1;
        st.assign(n + 1, vector<T>(LIMIT + 1));
        lg2.assign(n + 1, 0);
        lg2[0] = -1;
        for(int i = 1; i <= n; i++){
            lg2[i] = lg2[i >> 1] + 1;
            st[i][0] = arr[i];
        }
        for(int p = 1; p <= lg2[n]; p++){
            for(int i = 1; i + (1LL << p) - 1 <= n; i++){
                st[i][p] = op(st[i][p - 1], st[i + (1LL << (p - 1))][p - 1]);
            }
        }
    }

    T qry(int l, int r){
        if(l > r) return -INF;
        int p = lg2[r - l + 1];
        int ans = op(st[l][p], st[r - (1LL << p) + 1][p]);
        return ans;
    }
};

}

namespace ST2 {

template<typename T , typename F> 
class ST {
private:
    int n, m;
    vector<int> lg2, lgy;
    vector<vector<vector<vector<T>>>> st;
    F op;
public:
    ST(const vector<vector<T>>& arr, F f) : op(f), n(arr.size() - 1), m(arr[1].size() - 1) {
        int mx = max(m, n);
        lg2.assign(mx + 1, 0);
        lg2[0] = -1;
        for(int i = 1; i <= mx; i++) 
            lg2[i] = lg2[i >> 1] + 1;
        int LIMIT_x = lg2[n] + 1, LIMIT_y = lg2[m] + 1;
        st.assign(n + 1, vector<vector<vector<T>>>(m + 1, vector<vector<T>>(LIMIT_x, vector<T>(LIMIT_y))));
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                st[i][j][0][0] = arr[i][j];
            }
        }
        for(int py = 1; py < LIMIT_y; py++) {
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j + (1LL << py) - 1 <= m; j++) {
                    st[i][j][0][py] = op(st[i][j][0][py - 1], st[i][j + (1LL << (py - 1))][0][py - 1]);
                }
            }
        }
        for(int px = 1; px < LIMIT_x; px++) {
            for(int py = 0; py < LIMIT_y; py++) {
                for(int i = 1; i + (1LL << px) - 1 <= n; i++) {
                    for(int j = 1; j + (1LL << py) - 1 <= m; j++) {
                        st[i][j][px][py] = op(st[i][j][px - 1][py], st[i + (1LL << (px - 1))][j][px - 1][py]);
                    }
                }
            }
        }
    }
    
    T qry(int x1, int y1, int x2, int y2) {
        int px = lg2[x2 - x1 + 1];
        int py = lg2[y2 - y1 + 1];
        return op(op(st[x1][y1][px][py], st[x1][y2 - (1LL << py) + 1][px][py]), op(st[x2 - (1LL << px) + 1][y1][px][py], st[x2 - (1LL << px) + 1][y2 - (1LL << py) + 1][px][py]));
    }
};

}

