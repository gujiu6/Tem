/*
注:逆时针:叉乘 > 0 : 凸点;叉乘 < 0 : 凹点;
1.浮点误差与精确整数几何
2.Point / Vector
3.点积、叉积、长度、夹角、旋转
4.极角排序与象限分类
5.Line(直线) / Ray(射线) / Segment(线段)
6.平行、垂直、共线、同侧/异侧
7.直线交点、投影、对称点
8.点到 直线/线段 距离
*/
#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using i64 = long long;
constexpr ld eps = 1e-12;

// 1.浮点误差与精确整数几何
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

// 2.Point / Vector
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

// 3.点积、叉积、长度、夹角、旋转
namespace {

template <class T> T dot(const Point<T> &a, const Point<T> &b) {
    // a、b 表示两个向量;返回点积.
    return a.x * b.x + a.y * b.y;
}

template <class T> T cross(const Point<T> &a, const Point<T> &b) {
    // a、b 表示两个向量;返回有向叉积.
    return a.x * b.y - a.y * b.x;
}

template <class T> T cross(const Point<T> &a, const Point<T> &b, const Point<T> &c){
    // a、b、c 表示三个点;返回三角形 abc 的有向面积两倍.
    return cross(b - a, c - a);
}

template <class T> T square(const Point<T> &a) {
    // a 表示向量;返回模长平方.
    return dot(a, a);
}

template <class T> ld abs(const Point<T> &a) {
    // a 表示向量;返回其欧氏模长.
    return sqrtl((ld)square(a));
}

template <class T> ld angle(const Point<T> &a, const Point<T> &b) {
    // a、b 是非零向量;返回 a 到 b 的有向夹角,范围为 (-pi,pi].
    return atan2l(cross(a, b), dot(a, b));
}

template <class T> Point<ld> rotate(const Point<T> &a, ld t) {
    // a 表示向量,t 表示逆时针旋转弧度;返回旋转后的浮点向量.
    return {a.x * cosl(t) - a.y * sinl(t), a.x * sinl(t) + a.y * cosl(t)};
}

template <class T> Point<T> rot(const Point<T> &a) {
    // a 表示向量;返回逆时针旋转 90 度后的向量.
    return {-a.y, a.x};
}

}

// 4.极角排序与象限分类
namespace {

template <class T> int half(Point<T> p) {
    // p 是向量;返回其所在的极角半平面编号.
    return p.y < 0 || (p.y == 0 && p.x < 0);
}

// 以原点为极点，按 [-pi, pi) 逆时针排序；同射线按距离升序。
template <class T> bool polarCmp(Point<T> a, Point<T> b) {
    // a、b 是相对同一原点的向量;返回 a 是否应排在 b 前面.
    int x = half(a);
    int y = half(b);
    if (x != y) {
        return x < y;
    }
    auto c = cross(a, b);
    return c ? c > 0 : square(a) < square(b);
}

// 绕极点 o 排序。
template <class T> void polarSort(vector<Point<T>> &a, Point<T> o = {0, 0}) {
    // 参数 a 表示 要原地按极角排序的点或向量序列;o 表示 极角排序使用的原点;以 o 为原点原地按极角排序点集，无返回值.
    sort(a.begin(), a.end(), [&](Point<T> x, Point<T> y) {
        return polarCmp(x - o, y - o);
    });
}

}

// 5.Line(直线) / Ray(射线) / Segment(线段)
namespace {

template <class T> struct Line {
    Point<T> a; // a 保存直线、射线或线段的起点.
    Point<T> b; // b 保存直线上的第二点;作为射线时方向为 b-a.

    Line(Point<T> a = {}, Point<T> b = {}) : a(a), b(b) {}
};

struct DirLine {
    Point<ld> p; // p 保存直线上一点.
    Point<ld> v; // v 保存非零方向向量.

    Point<ld> at(ld t) const {
        // t 表示方向参数;返回 p+v*t.
        return p + v * t;
    }
};

template <class T> DirLine toDir(const Line<T> &l) {
    // l 表示端点式直线;返回供浮点算法使用的点方向式直线.
    auto v = l.b - l.a;
    return {(Point<ld>)l.a, (Point<ld>)v};
}

}

// 6.平行、垂直、共线、同侧/异侧
namespace {

template <class T> bool parallel(const Line<T> &a, const Line<T> &b) {
    // a、b 表示两条端点式直线;返回方向是否平行.
    return sgn(cross(a.b - a.a, b.b - b.a)) == 0;
}

template <class T> bool perp(const Line<T> &a, const Line<T> &b) {
    // a、b 表示两条端点式直线;返回方向是否垂直.
    return sgn(dot(a.b - a.a, b.b - b.a)) == 0;
}

template <class T> int side(const Line<T> &l, const Point<T> &p) {
    // l 表示有向直线,p 表示查询点;返回叉积符号,正数在左侧.
    return sgn(cross(l.b - l.a, p - l.a));
}

bool parallel(DirLine a, DirLine b) {
    // a、b 表示两条点方向式直线；返回方向是否平行.
    return sgn(cross(a.v, b.v)) == 0;
}

}

// 7.直线交点、投影、对称点
namespace {

template <class T> Point<ld> lineMeet(const Line<T> &a, const Line<T> &b) {
    // a、b 表示两条不平行直线;返回唯一交点.
    auto u = (Point<ld>)a.a;
    auto v = (Point<ld>)(a.b - a.a);
    auto p = (Point<ld>)b.a;
    auto q = (Point<ld>)(b.b - b.a);
    return u + v * (cross(p - u, q) / cross(v, q));
}

template <class T> Point<ld> projection(const Line<T> &l, const Point<T> &p) {
    // l 表示非退化直线,p 表示查询点;返回 p 在直线上的正交投影.
    auto a = (Point<ld>)l.a;
    auto v = (Point<ld>)(l.b - l.a);
    auto q = (Point<ld>)p;
    return a + v * (dot(q - a, v) / square(v));
}

template <class T> Point<ld> reflection(const Line<T> &l, const Point<T> &p) {
    // l 表示非退化直线,p 表示查询点;返回 p 关于直线的对称点.
    return projection(l, p) * 2 - (Point<ld>)p;
}

Point<ld> isect(DirLine a, DirLine b) {
    // a、b 表示两条不平行的点方向式直线;返回唯一交点.
    return a.at(cross(b.p - a.p, b.v) / cross(a.v, b.v));
}

Point<ld> proj(DirLine l, Point<ld> p) {
    // l 表示非退化点方向式直线,p 表示查询点;返回正交投影.
    return l.at(dot(p - l.p, l.v) / square(l.v));
}

Point<ld> refl(DirLine l, Point<ld> p) {
    // l 表示非退化点方向式直线,p 表示查询点;返回关于直线的对称点.
    return proj(l, p) * 2 - p;
}

ld dis(DirLine l, Point<ld> p) {
    // l 表示非退化点方向式直线,p 表示查询点;返回点到直线距离.
    return fabsl(cross(l.v, p - l.p)) / abs(l.v);
}

}

// 8.点到 直线/线段 距离
namespace {

template <class T> ld distancePL(const Point<T> &p, const Line<T> &l) {
    // p 表示点,l 表示非退化直线;返回点到无限直线的距离.
    return fabsl((ld)cross(l.b - l.a, p - l.a)) / abs(l.b - l.a);
}

template <class T> ld distancePS(const Point<T> &p, const Line<T> &l) {
    // p 表示点,l 表示线段;返回点到闭线段的最短距离.
    if (l.a == l.b) {
        return abs(p - l.a);
    }
    if (dot(p - l.a, l.b - l.a) <= 0) {
        return abs(p - l.a);
    }
    if (dot(p - l.b, l.a - l.b) <= 0) {
        return abs(p - l.b);
    }
    return distancePL(p, l);
}

}