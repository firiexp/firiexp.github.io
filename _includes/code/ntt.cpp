
constexpr int ntt_mod = 998244353, ntt_root = 3;
// 1012924417 -> 5, 924844033 -> 5
// 998244353  -> 3, 897581057 -> 3
// 645922817  -> 3;

template<int M, int proot>
class NTT {
    vector<vector<int>> rts, rrts;
public:
    NTT() = default;

    inline int add(int a,int b){ a += b; if(a >= M) a -= M; return a; }

    inline int mul(int a,int b){ return 1LL * a * b % M; }

    inline int pow(int a,int b){
        int res = 1;
        while(b){
            if(b&1) res = mul(res, a);
            a = mul(a, a);
            b >>= 1;
        }
        return res;
    }

    inline int extgcd(int a, int b, int &x ,int &y){
        for (int u = y = 1, v = x = 0; a; ) {
            ll q = b/a;
            swap(x -= q*u, u);
            swap(y -= q*v, v);
            swap(b -= q*a, a);
        }
        return b;
    }
    inline int inv(int x){
        int s, t;
        extgcd(x, M, s, t);
        return (M+s)%M;
    }

    void ensure_base(int N) {
        if(rts.size() >= N) return;
        rts.resize(N), rrts.resize(N);
        for(int i = 1; i < N; i <<= 1) {
            if(!rts[i].empty()) continue;
            int w = pow(proot, (M - 1) / (i << 1));
            int rw = inv(w);
            rts[i].resize(i), rrts[i].resize(i);
            rts[i][0] = 1, rrts[i][0] = 1;
            for(int k = 1; k < i; k++) {
                rts[i][k] = mul(rts[i][k - 1],w);
                rrts[i][k] = mul(rrts[i][k - 1],rw);
            }
        }
    }
    void ntt(vector<int> &a, int sign){
        int n = a.size();
        ensure_base(n);

        for (int i = 0, j = 1; j < n-1; ++j) {
            for (int k = n >> 1; k > (i ^= k); k >>= 1);
            if(j < i) swap(a[i], a[j]);
        }
        for (int i = 1; i < n; i <<= 1) {
            for (int j = 0; j < n; j += i * 2) {
                for (int k = 0; k < i; ++k) {
                    int y = mul(a[j+k+i], (sign ? rrts[i][k] : rts[i][k]));
                    a[j+k+i] = add(a[j+k], M-y), a[j+k] = add(a[j+k], y) ;
                }
            }
        }
        if(sign) {
            int temp = inv(n);
            for (int i = 0; i < n; ++i) a[i] = mul(a[i],temp);
        }
    }
};



NTT<ntt_mod, ntt_root> ntt;

constexpr int M = ntt_mod;

struct poly {
    vector<int> v;
    poly() = default;
    explicit poly(int n) : v(n) {};
    explicit poly(vector<int> vv) : v(std::move(vv)) {};
    int size() const {return (int)v.size(); }
    poly cut(int len){
        if(len < v.size()) v.resize(static_cast<unsigned long>(len));
        return *this;
    }
    inline int& operator[] (int i) {return v[i]; }
    poly operator+(const poly &a) const { return poly(*this) += a; }
    poly operator-(const poly &a) const { return poly(*this) -= a; }
    poly operator*(const poly &a) const { return poly(*this) *= a; }

    poly& operator+=(const poly &a) {
        this->v.resize(max(size(), a.size()));
        for (int i = 0; i < a.size(); ++i) {
            (this->v[i] += a.v[i]);
            if(this->v[i] > ntt_mod) this->v[i] -= M;
        }
        return *this;
    }
    poly& operator-=(const poly &a) {
        this->v.resize(max(size(), a.size()));
        for (int i = 0; i < a.size(); ++i) {
            (this->v[i] += M-a.v[i]);
            if(this->v[i] > M) this->v[i] -= M;
        }
        return *this;
    }

    poly& operator*=(poly a) {
        int N = size()+a.size()-1;
        int sz = 1;
        while(sz < N) sz <<= 1;
        ntt.ensure_base(sz);
        this->v.resize(sz); a.v.resize(sz);
        ntt.ntt(this->v, 0); ntt.ntt(a.v, 0);
        for(int i = 0; i < sz; ++i) this->v[i] = ntt.mul(this->v[i], a.v[i]);
        ntt.ntt(this->v, 1);
        return *this;
    }

    poly inv() const {
        int n = size();
        vector<int> rr(1, ntt.inv(this->v[0]));
        poly r(rr);
        for (int k = 2; k <= n; k <<= 1) {
            vector<int> u(k);
            for (int i = 0; i < k; ++i) {
                u[i] = this->v[i];
            }
            poly ff(u);
            poly nr = (r*r);
            nr = nr*ff;
            nr.cut(k);
            for (int i = 0; i < k/2; ++i) {
                nr[i] = (2*r[i]-nr[i]+M)%M;
                nr[i+k/2] = (M-nr[i+k/2])%M;
            }
            r = nr;
        }
        r.v.resize(n);
        return r;
    }
};
