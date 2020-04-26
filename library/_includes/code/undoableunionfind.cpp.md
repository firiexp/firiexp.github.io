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


# :warning: _includes/code/undoableunionfind.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#b46effe2a00fceb0770301fd2a31d561">_includes/code</a>
* <a href="{{ site.github.repository_url }}/blob/master/_includes/code/undoableunionfind.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-26 23:24:02+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
class UndoableUnionFind {
    stack<pair<int, int>> hist;
    int forest_size;
public:
    vector<int> uni;
    explicit UndoableUnionFind(int sz) : uni(sz, -1), forest_size(sz) {}

    int root(int a){
        if(uni[a] < 0) return a;
        return root(uni[a]);
    }

    bool unite(int a, int b){
        a = root(a), b = root(b);
        hist.emplace(a, uni[a]);
        hist.emplace(b, uni[b]);
        if(a == b) return false;
        if(uni[a] > uni[b]) swap(a, b);
        uni[a] += uni[b];
        uni[b] = a;
        forest_size--;
        return true;
    }

    int size(){ return forest_size; }
    int size(int i){ return -uni[root(i)]; }

    void undo(){
        uni[hist.top().first] = hist.top().second;
        hist.pop();
        uni[hist.top().first] = hist.top().second;
        hist.pop();
    }

    void snapshot(){ while(!hist.empty()) hist.pop(); }
    void rollback(){ while(!hist.empty()) undo(); }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "_includes/code/undoableunionfind.cpp"
class UndoableUnionFind {
    stack<pair<int, int>> hist;
    int forest_size;
public:
    vector<int> uni;
    explicit UndoableUnionFind(int sz) : uni(sz, -1), forest_size(sz) {}

    int root(int a){
        if(uni[a] < 0) return a;
        return root(uni[a]);
    }

    bool unite(int a, int b){
        a = root(a), b = root(b);
        hist.emplace(a, uni[a]);
        hist.emplace(b, uni[b]);
        if(a == b) return false;
        if(uni[a] > uni[b]) swap(a, b);
        uni[a] += uni[b];
        uni[b] = a;
        forest_size--;
        return true;
    }

    int size(){ return forest_size; }
    int size(int i){ return -uni[root(i)]; }

    void undo(){
        uni[hist.top().first] = hist.top().second;
        hist.pop();
        uni[hist.top().first] = hist.top().second;
        hist.pop();
    }

    void snapshot(){ while(!hist.empty()) hist.pop(); }
    void rollback(){ while(!hist.empty()) undo(); }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

