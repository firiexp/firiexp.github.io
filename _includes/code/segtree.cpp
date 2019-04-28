template <class T, class F>
struct segment_tree{
    int sz;
    vector<T> seg;
    const F f;
    const T M;
    segment_tree(int n, const F f, const T &M) : f(f), M(M) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2*sz, M);
    }

    void set(int k, const T &x){
        seg[k + sz] = x;
    }

    void build(){
        for (int i = sz-1; i > 0; --i) seg[i] = f(seg[2*i], seg[2*i+1]);
    }

    void update(int k, const T &x){ // 0-indexed
        k += sz;
        seg[k] = x;
        while (k >>= 1){
            seg[k] = f(seg[2*k], seg[2*k+1]);
        }
    }

    T query(int a, int b){ // 0-indexed
        T l = M, r = M;
        for(a += sz, b += sz; a < b; a >>=1, b>>=1){
            if(a & 1) l = f(l, seg[a++]);
            if(b & 1) r = f(seg[--b], r);
        }
        return f(l, r);
    }

    T operator[](const int &k) const { // 0-indexed
        return seg[k + sz];
    }
};
/*
Use this template
auto f = [](int a, int b){ return min(a, b); }
segment_tree<int, decltype(f)> seg(n, f), INF<int>);
 */