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


# :warning: _includes/code/z-algorithm.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#b46effe2a00fceb0770301fd2a31d561">_includes/code</a>
* <a href="{{ site.github.repository_url }}/blob/master/_includes/code/z-algorithm.cpp">View this file on GitHub</a>
    - Last commit date: 2019-08-15 21:58:00+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
vector<int> Z_algorithm(const string &s){
    vector<int> res(s.size());
    res.front() = s.size();
    for (int i = 1, j = 0; i < s.size(); ++i) {
        if(i + res[i-j] < j + res[j]) res[i] = res[i-j];
        else {
            int k = max(0, j + res[j]-i);
            while(i + k < s.size() && s[k] == s[i+k]) ++k;
            res[i] = k;
            j = i;
        }
    }
    return res;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "_includes/code/z-algorithm.cpp"
vector<int> Z_algorithm(const string &s){
    vector<int> res(s.size());
    res.front() = s.size();
    for (int i = 1, j = 0; i < s.size(); ++i) {
        if(i + res[i-j] < j + res[j]) res[i] = res[i-j];
        else {
            int k = max(0, j + res[j]-i);
            while(i + k < s.size() && s[k] == s[i+k]) ++k;
            res[i] = k;
            j = i;
        }
    }
    return res;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

