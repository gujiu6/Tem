/*
1.浮点误差与精确整数几何
2.Point / Vector
3.点积、叉积、长度、夹角、旋转
*/
#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using i64 = long long;
constexpr ld eps = 1e-12;

//1.浮点误差与精确整数几何
namespace {

template <class T> int sgn(T x) {
    // x 是整数;返回 -1、0、1 表示负、零、正.
    return (x > 0) - (x < 0);
}

int sgn(ld x) {
    // x 表示待判断的浮点数；返回 -1、0、1 表示负、近似零、正。
    ld t = eps * max<ld>(1, fabsl(x));
    return (x > t) - (x < -t);
}

template <class T> bool eq(T x, T y) {
    // x、y 是整数;返回二者是否相等.
    return x == y;
}

bool eq(ld x, ld y) {
    // x、y 表示两个浮点数;使用相对误差判断它们是否近似相等.
    return fabsl(x - y) <= eps * max<ld>(1, max(fabsl(x), fabsl(y)));
}

}

//2.Point / Vector
template <class T> struct Point {
    T x, y;
    Point(const T &x = 0, const T &y = 0) : x(x), y(y) {}

    template <class U> explicit operator Point<U>() const {
        // U 表示目标坐标类型；返回逐坐标 C 风格转换后的点.
        return Point<U>((U)x, (U)y);
    }

    Point &operator+=(const Point &p) {
        // p 表示另一个向量;把 p 加到当前向量并返回自身.
        x += p.x;
        y += p.y;
        return *this;
    }

    Point &operator-=(const Point &p) {
        // p 表示另一个向量;从当前向量减去 p 并返回自身.
        x -= p.x;
        y -= p.y;
        return *this;
    }

    Point &operator*=(const T &k) {
        // k 表示缩放倍数;原地数乘并返回自身.
        x *= k;
        y *= k;
        return *this;
    }

    Point &operator/=(const T &k) {
        // k 表示非零除数;原地除法并返回自身.
        assert(k != T(0));
        x /= k;
        y /= k;
        return *this;
    }

    Point operator-() const {
        // 无参数;返回反向向量.
        return {-x, -y};
    }

    friend Point operator+(Point a, const Point &b) {
        // a、b 表示两个向量;返回逐坐标之和。
        return a += b;
    }

    friend Point operator-(Point a, const Point &b) {
        // a、b 表示两个点或向量;返回 a-b.
        return a -= b;
    }

    friend Point operator*(Point a, const T &k) {
        // a 表示向量,k 表示倍数;返回缩放后的向量.
        return a *= k;
    }

    friend Point operator*(const T &k, Point a) {
        // k 表示倍数,a 表示向量;返回缩放后的向量.
        return a *= k;
    }

    friend Point operator/(Point a, const T &k) {
        // a 表示向量,k 表示非零除数;返回缩放后的向量.
        return a /= k;
    }

    friend bool operator<(const Point &a, const Point &b) {
        // a、b 表示两个点;返回按 x、y 的字典序比较结果.
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    }

    friend bool operator==(const Point &a, const Point &b) {
        // a、b 表示两个点;返回坐标是否精确相等.
        return a.x == b.x && a.y == b.y;
    }
};

template <class T> bool eq(Point<T> a, Point<T> b) {
    // a、b 表示两个点;整数坐标精确比较,浮点坐标按统一误差比较.
    return eq(a.x, b.x) && eq(a.y, b.y);
}

//3.点积、叉积、长度、夹角、旋转