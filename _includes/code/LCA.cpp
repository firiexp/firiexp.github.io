template <class M>
struct SegmentTree{
    using T = typename M::T;
    int sz;
    vector<T> seg;
    explicit SegmentTree(int n) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2*sz, M::e());
    }
 
    void set(int k, const T &x){ seg[k + sz] = x; }
 
    void build(){
        for (int i = sz-1; i > 0; --i) seg[i] = M::f(seg[2*i], seg[2*i+1]);
    }
 
    void update(int k, const T &x){
        k += sz;
        seg[k] = x;
        while (k >>= 1) seg[k] = M::f(seg[2*k], seg[2*k+1]);
    }
 
    T query(int a, int b){
        T l = M::e(), r = M::e();
        for(a += sz, b += sz; a < b; a >>=1, b>>=1){
            if(a & 1) l = M::f(l, seg[a++]);
            if(b & 1) r = M::f(seg[--b], r);
        }
        return M::f(l, r);
    }
 
    T operator[](const int &k) const { return seg[k + sz]; }
};
 
struct Monoid{
    using T = pair<int, int>;
    static T f(T a, T b) { return min(a, b); }
    static T e() { return T(INF<int>, -1); }
};
 
class Graph {
    void dfs_euler(int v, int p, int d, int &k){
        id[v] = k;
        vs[k] = v;
        depth[k++] = d;
        for (auto &&u : G[v]) {
            if(u != p){
                dfs_euler(u, v, d+1, k);
                vs[k] = v;
                depth[k++] = d;
            }
        }
    }
public:
    int n;
    vector<vector<int>> G;
    vector<int> vs, depth, id;
    explicit Graph(int n) : n(n), G(n), vs(2*n-1), depth(2*n-1), id(n) {};
    void add_edge(int a, int b){
        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }
 
    void eulertour(int root) {
        int k = 0;
        dfs_euler(root, -1, 0, k);
    }
};
 
class LCA {
    Graph G;
    SegmentTree<Monoid> seg;
public:
    explicit LCA(Graph G) : G(G), seg(2*G.n-1) {
        int n = G.n;
        for (int i = 0; i < 2*n-1; ++i) {
            seg.set(i, pair<int, int>(G.depth[i], i));
        }
        seg.build();
    };
 
    int lca(int u, int v){
        if(G.id[u] > G.id[v]) swap(u, v);
        return seg.query(G.id[u], G.id[v]+1).second;
    }
};