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
 