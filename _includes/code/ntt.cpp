constexpr int ntt_mod = 998244353, ntt_root = 3;
// 1012924417 -> 5, 924844033 -> 5
// 998244353  -> 3, 897581057 -> 3
// 645922817  -> 3;
template<u32 M = 1000000007>
struct modint{
    u32 val;
    modint(): val(0){}
    template<typename T>
    explicit modint(T t){t %= (T)M; if(t < 0) t += (T)M; val = t;}

    modint pow(ll k) const {
        modint res(1), x(val);
        while(k){
            if(k&1) res *= x;
            x *= x;
            k >>= 1;
        }
        return res;
    }
    template<typename T>
    modint& operator=(T t){t %= (T)M; if(t < 0) t += (T)M; val = t; return *this; }
    modint inv() const {return pow(M-2);}
    modint& operator+=(modint a){ val += a.val; if(val >= M) val -= M; return *this;}
    modint& operator-=(modint a){ if(val < a.val) val += M-a.val; else val -= a.val; return *this;}
    modint& operator*=(modint a){ val = (u64)val*a.val%M; return *this;}
    modint& operator/=(modint a){ return (*this) *= a.inv();}
    modint operator+(modint a) const {return modint(val) +=a;}
    modint operator-(modint a) const {return modint(val) -=a;}
    modint operator*(modint a) const {return modint(val) *=a;}
    modint operator/(modint a) const {return modint(val) /=a;}
    modint operator-(){ return modint(M-val);}
    bool operator==(const modint a) const {return val == a.val;}
    bool operator!=(const modint a) const {return val != a.val;}
    bool operator<(const modint a) const {return val < a.val;}
};

using mint = modint<ntt_mod>;


template<int M, int proot>
class NTT {
    vector<vector<mint>> rts, rrts;
public:
    NTT() = default;

    void ensure_base(int N) {
        if(rts.size() >= N) return;
        rts.resize(N), rrts.resize(N);
        for(int i = 1; i < N; i <<= 1) {
            if(!rts[i].empty()) continue;
            mint w = mint(proot).pow((M-1) / (i << 1));
            mint rw = w.inv();
            rts[i].resize(i), rrts[i].resize(i);
            rts[i][0] = 1, rrts[i][0] = 1;
            for(int k = 1; k < i; k++) {
                rts[i][k] = rts[i][k-1]*w;
                rrts[i][k] = rrts[i][k-1]*rw;
            }
        }
    }
    void ntt(vector<mint> &a, int sign){
        int n = a.size();
        ensure_base(n);

        for (int i = 0, j = 1; j < n-1; ++j) {
            for (int k = n >> 1; k > (i ^= k); k >>= 1);
            if(j < i) swap(a[i], a[j]);
        }
        for (int i = 1; i < n; i <<= 1) {
            for (int j = 0; j < n; j += i << 1) {
                for (int k = 0; k < i; ++k) {
                    mint y = a[j+k+i]*(sign ? rrts[i][k] : rts[i][k]);
                    a[j+k+i] = a[j+k]-y, a[j+k] += y;
                }
            }
        }
        if(sign) {
            mint temp = mint(n).inv();
            for (int i = 0; i < n; ++i) a[i] *= temp;
        }
    }
};



NTT<ntt_mod, ntt_root> ntt;

struct poly {
    vector<mint> v;
    poly() = default;
    explicit poly(int n) : v(n) {};
    explicit poly(vector<mint> vv) : v(std::move(vv)) {};
    int size() const {return (int)v.size(); }
    poly cut(int len){
        if(len < v.size()) v.resize(static_cast<unsigned long>(len));
        return *this;
    }
    inline mint& operator[] (int i) {return v[i]; }
    poly operator+(const poly &a) const { return poly(*this) += a; }
    poly operator-(const poly &a) const { return poly(*this) -= a; }
    poly operator*(const poly &a) const { return poly(*this) *= a; }

    poly inv() const {
        int n = size();
        poly r(1);
        r[0] = (this->v[0]).inv();
        int k = 1;
        while(k < n){
            k *= 2;
            poly ff(k);
            for (int i = 0; i < min(k, n); ++i) {
                ff[i] = this->v[i];
            }
            poly nr = r*r*ff;
            nr.cut(k);
            for (int i = 0; i < k/2; ++i) {
                nr[i] = (r[i]+r[i]-nr[i]);
                nr[i+k/2] = -nr[i+k/2];
            }
            r = nr;
        }
        r.v.resize(n);
        return r;
    }

    poly& operator+=(const poly &a) {
        this->v.resize(max(size(), a.size()));
        for (int i = 0; i < a.size(); ++i) {
            (this->v[i] += a.v[i]);
        }
        return *this;
    }
    poly& operator-=(const poly &a) {
        this->v.resize(max(size(), a.size()));
        for (int i = 0; i < a.size(); ++i) {
            (this->v[i] -= a.v[i]);
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
        for(int i = 0; i < sz; ++i) this->v[i] *= a.v[i];
        ntt.ntt(this->v, 1);
        return *this;
    }

    poly& operator/=(const poly &a){
        return (*this *= a.inv());
    }
};