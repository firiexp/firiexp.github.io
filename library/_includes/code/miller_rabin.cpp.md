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


# :warning: _includes/code/miller_rabin.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#b46effe2a00fceb0770301fd2a31d561">_includes/code</a>
* <a href="{{ site.github.repository_url }}/blob/master/_includes/code/miller_rabin.cpp">View this file on GitHub</a>
    - Last commit date: 2019-04-28 22:27:06+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template< class T>
T pow_ (T x, uint64_t n, uint64_t M){
    T u = 1;
    if(n > 0){
        u = pow_(x, n/2, M);
        if (n % 2 == 0) u = (u*u) % M;
        else u = (((u * u)% M) * x) % M;
    }
    return u;
};

bool suspect(__uint128_t a, uint64_t s, uint64_t d, uint64_t n){
    __uint128_t x = pow_(a, d, n);
    if (x == 1) return true;
    for (int r = 0; r < s; ++r) {
        if(x == n-1) return true;
        x = x * x % n;
    }
    return false;
}

template<class T>
bool miller_rabin(T m){
    uint64_t n = m;
    if (n <= 1 || (n > 2 && n % 2 == 0)) return false;
    uint64_t d = n - 1, s = 0;
    while (!(d&1)) {++s; d >>= 1;}
    vector<uint64_t> v = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    if(n <= 4759123141LL) v = {2, 7, 61};
    for (auto &&p : v) {
        if(p >= n) break;
        if(!suspect(p, s, d, n)) return false;
    }
    return true;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "_includes/code/miller_rabin.cpp"
template< class T>
T pow_ (T x, uint64_t n, uint64_t M){
    T u = 1;
    if(n > 0){
        u = pow_(x, n/2, M);
        if (n % 2 == 0) u = (u*u) % M;
        else u = (((u * u)% M) * x) % M;
    }
    return u;
};

bool suspect(__uint128_t a, uint64_t s, uint64_t d, uint64_t n){
    __uint128_t x = pow_(a, d, n);
    if (x == 1) return true;
    for (int r = 0; r < s; ++r) {
        if(x == n-1) return true;
        x = x * x % n;
    }
    return false;
}

template<class T>
bool miller_rabin(T m){
    uint64_t n = m;
    if (n <= 1 || (n > 2 && n % 2 == 0)) return false;
    uint64_t d = n - 1, s = 0;
    while (!(d&1)) {++s; d >>= 1;}
    vector<uint64_t> v = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    if(n <= 4759123141LL) v = {2, 7, 61};
    for (auto &&p : v) {
        if(p >= n) break;
        if(!suspect(p, s, d, n)) return false;
    }
    return true;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

