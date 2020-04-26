---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :warning: _includes/code/geometry3d.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#b46effe2a00fceb0770301fd2a31d561">_includes/code</a>
* <a href="{{ site.github.repository_url }}/blob/master/_includes/code/geometry3d.cpp">View this file on GitHub</a>
    - Last commit date: 2019-08-26 16:31:54+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp

using real = double;
static constexpr real EPS = 1e-10;
struct Point3 {
    real x, y, z;
    Point3& operator+=(const Point3 a) { x += a.x; y += a.y; z += a.z;  return *this; }
    Point3& operator-=(const Point3 a) { x -= a.x; y -= a.y; z -= a.z; return *this; }
    Point3& operator*=(const real k) { x *= k; y *= k; z *= k;  return *this; }
    Point3& operator/=(const real k) { x /= k; y /= k; z /= k; return *this; }
    Point3 operator+(const Point3 a) const {return Point3(*this) += a; }
    Point3 operator-(const Point3 a) const {return Point3(*this) -= a; }
    Point3 operator*(const real k) const {return Point3(*this) *= k; }
    Point3 operator/(const real k) const {return Point3(*this) /= k; }
    Point3 (real a = 0, real b = 0, real c = 0) : x(a), y(b), z(c) {};
};

inline real dot(Point3 a, Point3 b){ return a.x*b.x + a.y*b.y + a.z*b.z; }
inline real abs(Point3 a){ return sqrt(dot(a, a)); }
inline Point3 cross(Point3 a, Point3 b){ return {a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x};  }

istream& operator>> (istream& s, Point3& P){
    s >> P.x >> P.y >> P.z;
    return s;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "_includes/code/geometry3d.cpp"

using real = double;
static constexpr real EPS = 1e-10;
struct Point3 {
    real x, y, z;
    Point3& operator+=(const Point3 a) { x += a.x; y += a.y; z += a.z;  return *this; }
    Point3& operator-=(const Point3 a) { x -= a.x; y -= a.y; z -= a.z; return *this; }
    Point3& operator*=(const real k) { x *= k; y *= k; z *= k;  return *this; }
    Point3& operator/=(const real k) { x /= k; y /= k; z /= k; return *this; }
    Point3 operator+(const Point3 a) const {return Point3(*this) += a; }
    Point3 operator-(const Point3 a) const {return Point3(*this) -= a; }
    Point3 operator*(const real k) const {return Point3(*this) *= k; }
    Point3 operator/(const real k) const {return Point3(*this) /= k; }
    Point3 (real a = 0, real b = 0, real c = 0) : x(a), y(b), z(c) {};
};

inline real dot(Point3 a, Point3 b){ return a.x*b.x + a.y*b.y + a.z*b.z; }
inline real abs(Point3 a){ return sqrt(dot(a, a)); }
inline Point3 cross(Point3 a, Point3 b){ return {a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x};  }

istream& operator>> (istream& s, Point3& P){
    s >> P.x >> P.y >> P.z;
    return s;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

