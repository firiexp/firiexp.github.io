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


# :warning: _includes/code/modinv.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#b46effe2a00fceb0770301fd2a31d561">_includes/code</a>
* <a href="{{ site.github.repository_url }}/blob/master/_includes/code/modinv.cpp">View this file on GitHub</a>
    - Last commit date: 2019-04-28 23:12:10+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<typename T>  
T mod_inv(T x, T M){  
   T u = 1, t = 1, v = 0, s = 0, m = M;  
   while (x) { T q = m/x; swap(s -= q*u, u); swap(t -= q*v, v); swap(m -= q*x, x); }  
   if(s < 0) s += M;  
   return s;  
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "_includes/code/modinv.cpp"
template<typename T>  
T mod_inv(T x, T M){  
   T u = 1, t = 1, v = 0, s = 0, m = M;  
   while (x) { T q = m/x; swap(s -= q*u, u); swap(t -= q*v, v); swap(m -= q*x, x); }  
   if(s < 0) s += M;  
   return s;  
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

