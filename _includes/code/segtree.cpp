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
    using T = int;
    static T f(T a, T b) { return min(a, b); }
    static T e() { return INF<int>; }
};