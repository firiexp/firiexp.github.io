struct Node {
    int val;
    Node *l, *r;
    Node() : val(0), l(nullptr), r(nullptr) {}
    static int cnt;
    void *operator new(size_t){
        static Node pool[3200000];
        return pool + cnt++;
    }
};
int Node::cnt = 0;

template<class T, size_t X>
struct Binarytrie {
    Node *root;
    Binarytrie() { root = new Node; }

    void add(const T b, int x = 1){
        Node *p = root;
        for (int i = X-1; i >= 0; --i) {
            bool f = (b >> i) & 1;
            if(!f && !p->l) p->l = new Node;
            if(f && !p->r) p->r = new Node;
            p = (f ? p->r : p->l);
        }
        p->val += x;
    }
};