template<int W, int start>
class AhoCorasick {
public:
    struct Node {
        array<int, W> to;
        int fail;
    };
    explicit AhoCorasick() : v(1) {}
    vector<Node> v;

    int add(string &s, int cur = 0){
        for (auto &&i : s) {
            if(!v[cur].to[i-start]) v[cur].to[i-start] = v.size(), v.emplace_back();
            cur = v[cur].to[i-start];
        }
        return cur;
    }

    void build() {
        v[0].fail = -1;
        queue<int> Q; Q.emplace(0);
        while(!Q.empty()){
            int i = Q.front(); Q.pop();
            for (int c = 0; c < W; ++c) {
                if(!v[i].to[c]) continue;
                int to = v[i].to[c];
                v[to].fail = (v[i].fail == -1 ? 0 : v[v[i].fail].to[c]);
                Q.emplace(to);
            }
            if(i != 0){
                for (int c = 0; c < W; ++c) {
                    if(!v[i].to[c]) v[i].to[c] = v[v[i].fail].to[c];
                }
            }
        }
        v[0].fail = 0;
    }
    inline int next(int x, char c){ return v[x].to[c-start]; }
};