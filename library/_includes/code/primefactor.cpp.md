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


# :warning: _includes/code/primefactor.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#b46effe2a00fceb0770301fd2a31d561">_includes/code</a>
* <a href="{{ site.github.repository_url }}/blob/master/_includes/code/primefactor.cpp">View this file on GitHub</a>
    - Last commit date: 2019-05-01 18:38:59+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
vector<int> get_prime(int n){
    if(n <= 1) return vector<int>();
    vector<bool> is_prime(n+1, true);
    vector<int> prime;
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i <= n; ++i) {
        if(is_prime[i]) prime.emplace_back(i);
        for (auto &&j : prime){
            if(i*j > n) break;
            is_prime[i*j] = false;
            if(i % j == 0) break;
        }
    }
    return prime;
}
const auto primes = get_prime(65535);

template<class T>
vector<T> prime_factor(T n){
    vector<T> res;
    for (auto &&i : primes) {
        while (n % i == 0){
            res.emplace_back(i);
            n /= i;
        }
    }
    if(n != 1) res.emplace_back(n);
    return res;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "_includes/code/primefactor.cpp"
vector<int> get_prime(int n){
    if(n <= 1) return vector<int>();
    vector<bool> is_prime(n+1, true);
    vector<int> prime;
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i <= n; ++i) {
        if(is_prime[i]) prime.emplace_back(i);
        for (auto &&j : prime){
            if(i*j > n) break;
            is_prime[i*j] = false;
            if(i % j == 0) break;
        }
    }
    return prime;
}
const auto primes = get_prime(65535);

template<class T>
vector<T> prime_factor(T n){
    vector<T> res;
    for (auto &&i : primes) {
        while (n % i == 0){
            res.emplace_back(i);
            n /= i;
        }
    }
    if(n != 1) res.emplace_back(n);
    return res;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

