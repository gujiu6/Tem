/*
1.Andrew 静态凸包
*/
#include <bits/stdc++.h>
#include "Basic.cpp"
using namespace std;

// 1.Andrew 静态凸包(严格凸包的直径平方;输入需逆时针且无共线邻边)
template <class T> vector<Point<T>> hull(vector<Point<T>> a) {
    // a 是点集;返回删除边上共线中间点后的逆时针凸包.
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    if (a.size() <= 1) {
        return a;
    }
    vector<Point<T>> h;
    for (int t = 0; t < 2; t++) {
        int z = h.size();
        for (auto p : a) {
            while ((int)h.size() >= z + 2 && sgn(cross(h.back() - h[h.size() - 2], p - h.back())) <= 0) {
                h.pop_back();
            }
            h.push_back(p);
        }
        h.pop_back();
        reverse(a.begin(), a.end());
    }
    return h;
}
// 