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


# :warning: _includes/code/twoedgeconnectedcomponents.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#b46effe2a00fceb0770301fd2a31d561">_includes/code</a>
* <a href="{{ site.github.repository_url }}/blob/master/_includes/code/twoedgeconnectedcomponents.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-25 20:39:20+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
class TwoEdgeConnectedComponents {
    void dfs(int i, int &pos){
        ord[i] = low[i] = pos++;
        int mul = 0;
        for (auto &&j : G[i]) {
            if(j == par[i] && !mul){
                mul = 1;
                continue;
            }
            if(~ord[j]){
                low[i] = min(low[i], ord[j]);
                continue;
            }
            par[j] = i;
            dfs(j, pos);
            size[i] += size[j];
            low[i] = min(low[i], low[j]);
        }
    }

    void dfs2(int i){
        out[bridge[i]].emplace_back(i);
        for (auto &&j : G[i]) {
            if(~bridge[j] || is_bridge(i, j)) continue;
            bridge[j] = bridge[i];
            dfs2(j);
        }
    }
public:
    vector<int> ord, low, par, bridge, size;
    vector<vector<int>> G, out;
    explicit TwoEdgeConnectedComponents(int n): ord(n, -1), low(n), par(n, -1), bridge(n, -1), size(n, 1), G(n){}

    inline bool is_bridge(int i, int j){
        if(ord[i] > ord[j]) swap(i, j);
        return ord[i] < low[j];
    }

    void add_edge(int u, int v){
        if(u != v){
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
    }

    int build(){
        int n = G.size(), pos = 0;
        for (int i = 0; i < n; ++i) {
            if(ord[i] < 0) dfs(i, pos);
        }
        int k = 0;
        for (int i = 0; i < n; ++i) {
            if(!~bridge[i]){
                bridge[i] = k++;
                out.emplace_back();
                dfs2(i);
            }
        }
        return k;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "_includes/code/twoedgeconnectedcomponents.cpp"
class TwoEdgeConnectedComponents {
    void dfs(int i, int &pos){
        ord[i] = low[i] = pos++;
        int mul = 0;
        for (auto &&j : G[i]) {
            if(j == par[i] && !mul){
                mul = 1;
                continue;
            }
            if(~ord[j]){
                low[i] = min(low[i], ord[j]);
                continue;
            }
            par[j] = i;
            dfs(j, pos);
            size[i] += size[j];
            low[i] = min(low[i], low[j]);
        }
    }

    void dfs2(int i){
        out[bridge[i]].emplace_back(i);
        for (auto &&j : G[i]) {
            if(~bridge[j] || is_bridge(i, j)) continue;
            bridge[j] = bridge[i];
            dfs2(j);
        }
    }
public:
    vector<int> ord, low, par, bridge, size;
    vector<vector<int>> G, out;
    explicit TwoEdgeConnectedComponents(int n): ord(n, -1), low(n), par(n, -1), bridge(n, -1), size(n, 1), G(n){}

    inline bool is_bridge(int i, int j){
        if(ord[i] > ord[j]) swap(i, j);
        return ord[i] < low[j];
    }

    void add_edge(int u, int v){
        if(u != v){
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
    }

    int build(){
        int n = G.size(), pos = 0;
        for (int i = 0; i < n; ++i) {
            if(ord[i] < 0) dfs(i, pos);
        }
        int k = 0;
        for (int i = 0; i < n; ++i) {
            if(!~bridge[i]){
                bridge[i] = k++;
                out.emplace_back();
                dfs2(i);
            }
        }
        return k;
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

