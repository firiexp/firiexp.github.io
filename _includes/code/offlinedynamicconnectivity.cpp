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

class OfflineDynamicConnectivity {
    UndoableUnionFind uf;
    int n;
    vector<vector<pair<int, int>>> seg;
    vector<pair<pair<int, int>, pair<int, int>>> pend;
    map<pair<int, int>, int> cnt, appear;
    void add(int a, int b, const pair<int ,int> &e){
        for (int l = a+sz, r = b+sz; l < r; l >>= 1, r >>= 1) {
            if(l&1) seg[l++].emplace_back(e);
            if(r&1) seg[--r].emplace_back(e);
        }
    }
public:
    int sz;
    OfflineDynamicConnectivity(int n, int q) : uf(n), n(n){
        sz = 1;
        while(sz < q) sz <<= 1;
        seg.resize(2*sz);
    }

    void insert(int t, int a, int b){
        auto e = minmax(a, b);
        if(cnt[e]++ == 0) appear[e] = t;
    }

    void erase(int t, int a, int b){
        auto e = minmax(a, b);
        if(--cnt[e] == 0) pend.emplace_back(make_pair(appear[e], t), e)
    }

    void build(){
        for (auto &&i : cnt) {
            if(!i.second) continue;
            pend.emplace_back(make_pair(appear[i.first], q), i.first);
        }
        for (auto &&i : pend) {
            add(i.first.first, i.first.second, i.second);
        }
    }

    template<typename F>
    void run(const F &f, int k = 1){
        for (auto &&i : seg[k]) uf.unite(i.first, i.second);
        if(k < sz){
            run(f, (k << 1) | 0);
            run(f, (k << 1) | 1);
        }else f(k-sz);
        for (auto &&i : seg[k]) uf.undo();
    }
};
