template<int W, class F> // W -> word size
struct Trie {
    struct Node {
        char c;
        vector<int> nxt, idxs;
        int id;
        explicit Node(char c): c(c), nxt(W, -1), id(-1){}
    };
    vector<Node> v;
    F f;
    explicit Trie(F f, char c = '$') : f(f) {
        v.emplace_back(c);
    }
    void add(const string &s, int x){
        int cur = 0;
        for (auto &&i : s) {
            int k = f(i);
            if(~v[cur].nxt[k]){
                cur = v[cur].nxt[k];
                continue;
            }
            int npos = v.size();
            v[cur].nxt[k] = npos;
            v.emplace_back(i);
            cur =  npos;
        }
        v[cur].id = x;
        v[cur].idxs.emplace_back(x);
    }
    
    int find(const string &s){
        int cur = 0;
        for (auto &&i : s) {
            int k = f(i);
            if(v[cur].nxt[k] < 0) return -1;
            cur = v[cur].nxt[k];
        }
        return cur;
    }
    int find(int cur, char c) {return v[cur].nxt[f(c)]; }
    int id(int cur) { return cur < 0 ? -1 : v[cur].id;}
 
    vector<int> idxs(int cur) { return cur < 0 ? vector<int>() : v[cur].idxs; }
};
 
template<int W, class F>
struct Aho_Corasick : Trie<W+1, F> {
    using TRIE = Trie<W+1, F>;
    using TRIE::TRIE;
    vector<int> cnt;
 
    void build(bool heavy = true){
        auto &v = TRIE::v;
        cnt.resize(v.size());
        for(int i = 0; i < v.size(); ++i) cnt[i] = v[i].idxs.size();
        queue<int> Q;
        for (int i = 0; i < W; ++i) {
            if(~v[0].nxt[i]){
                v[v[0].nxt[i]].nxt[W] = 0;
                Q.emplace(v[0].nxt[i]);
            } else {
                v[0].nxt[i] = 0;
            }
        }
        while(!Q.empty()){
            auto &x = v[Q.front()];
            cnt[Q.front()] += cnt[x.nxt[W]];
            Q.pop();
            for (int i = 0; i < W; ++i) {
                if(x.nxt[i] < 0) continue;
                int to = x.nxt[W];
                while(v[to].nxt[i] < 0) to = v[to].nxt[W];
                v[x.nxt[i]].nxt[W] = v[to].nxt[i];
                if(heavy){
                    auto &idx1 = v[x.nxt[i]].idxs;
                    auto &idx2 = v[v[to].nxt[i]].idxs;
                    vector<int> newidx;
                    set_union(idx1.begin(), idx1.end(), idx2.begin(), idx2.end(), back_inserter(newidx));
                    idx1 = newidx;
                }
                Q.emplace(x.nxt[i]);
            }
        }
    }
 
    vector<int> match(string s, int heavy = true){
        auto &v = TRIE::v;
        vector<int> res(heavy ? TRIE::size() : 1);
        int cur = 0;
        for (auto &&i : s) {
            int k = TRIE::f(i);
            while(v[cur].nxt[k] < 0) cur = v[cur].nxt[W];
            cur = v[cur].nxt[k];
            if(heavy) for(auto &x : v[cur].idxs) res[x]++;
            else res[0] += cnt[cur];
        }
        return res;
    }
    
    int move (int cur, char c){
        auto &v = TRIE::v;
        int k = TRIE::f(c);
        while(v[cur].nxt[k] < 0) cur = v[cur].nxt[W];
        cur = v[cur].nxt[k];
        return cur;
    }
};