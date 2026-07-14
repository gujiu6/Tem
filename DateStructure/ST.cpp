#include <bits/stdc++.h>
using namespace std;
const int INF=1e9+7;


//一维ST
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

//二维ST
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


namespace ST3 {

template <typename T, typename F>
class ST {
private:
    int n, m; 
    vector<int> lg2;
    struct ColST{
        int m;
        int LIMIT_y;
        vector<vector<T>> st;
        vector<int> lg2;
        F op;
        ColST() = default;
        ColST (const vector<T>& row, int m, F f) : m(m), op(f) {
            lg2.assign(m + 1, 0);
            lg2[0] = -1;
            for(int i = 1; i <= m; i++) 
                lg2[i] = lg2[i >> 1] + 1;
            LIMIT_y = lg2[m] + 1;
            st.assign(m + 1, vector<T>(LIMIT_y));
            for(int j = 1; j <= m; j++) {
                st[j][0] = row[j];
            }
            for(int py = 1; py < LIMIT_y; py++) {
                for(int j = 1; j <= m; j++) {
                    st[j][py] = op(st[j][py - 1], st[j + (1LL << (py - 1))][py - 1]);
                }
            }
        }

        void merge(ColST& a, ColST& b) {
            m = a.m;
            LIMIT_y = a.LIMIT_y;
            lg2 = a.lg2;
            st.assign(m + 1, vector<T>(LIMIT_y));
            for(int j = 1; j <= m; j++) {
                st[j][0] = op(a.st[j][0], b.st[j][0]);
            }
            for (int py = 1; py < LIMIT_y; py++) {
                for (int j = 1; j + (1LL << py) - 1 <= m; j++) {
                    st[j][py] = op(st[j][py - 1], st[j + (1LL << (py - 1))][py - 1]);
                }
            }
                
        }

        T qry(int l, int r) {
            int py = lg2[r - l + 1];
            return op(st[l][py], st[r - (1LL << py) + 1][py]);
        }
    };
    F op;
    vector<vector<ColST>> st;

public:
    ST(const vector<vector<T>>& arr, F f): op(f), n(arr.size() - 1), m(arr[1].size() - 1) {
        lg2.assign(n + 1, 0);
        lg2[0] = -1;
        for(int i = 1; i <= n; i++) 
            lg2[i] = lg2[i >> 1] + 1;
        int LIMIT_x = lg2[n] + 1;
        st.assign(n + 1, vector<ColST>(LIMIT_x));
        for (int px = 1; px < LIMIT_x; px++) {
            for (int i = 1; i + (1LL << px) - 1 <= n; i++) {
                st[px][i].merge(st[px - 1][i], st[px - 1][i + (1LL << (px - 1))]);
            }
        }
    }

    T qry(int x1, int y1, int x2, int y2) {
        int px = lg2[x2 - x1 + 1];
        return op(st[x1][px].qry(y1, y2), st[x2 - (1LL << px) + 1][px].qry(y1, y2));
    }
};


}


//分块
namespace ST4 {

template<typename T>
class ST {
private:
    int n, m;
    int B;
    vector<vector<T>> arr, block;
public:
    ST(const vector<vector<T>>& a) : arr(a), n(a.size() - 1), m(a[0].size() - 1) {
        B = sqrt(n * m) + 1;
        int bx = (n + B - 1) / B, by = (m + B - 1) / B;
        block.assign(bx + 1, vector<T>(by + 1, -INF));
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                int x = (i - 1) / B, y = (j - 1) / B;
                block[x][y] = max(block[x][y], a[i][j]);
            }
        }
    }
    T qry(int x1, int y1, int x2, int y2) {
        T ans = -INF;
        int bx1 = (x1 - 1) / B, by1 = (y1 - 1) / B;
        int bx2 = (x2 - 1) / B, by2 = (y2 - 1) / B;
        for(int i = bx1; i <= bx2; i++) {
            for(int j = by1; j <= by2; j++) {
                int lx = i * B + 1, ly = j * B + 1;
                int rx = min(n, lx + B - 1), ry = min(m, ly + B - 1);
                if(lx >= x1 && rx <= x2 && ly >= y1 && ry <= y2) {
                    ans = max(ans, block[i][j]);
                }
                else {
                    for(int x = max(x1, lx); x <= min(x2, rx); x++) {
                        for(int y = max(y1, ly); y <= min(y2, ry); y++) {
                            ans = max(ans, arr[x][y]);
                        }
                    }
                }
            }
        }
        return ans;
    }
};

}