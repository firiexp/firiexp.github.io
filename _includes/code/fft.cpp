template<typename T>
T extgcd(T a, T b, T &x ,T &y){
    for (T u = y = 1, v = x = 0; a; ) {
        ll q = b/a;
        swap(x -= q*u, u);
        swap(y -= q*v, v);
        swap(b -= q*a, a);
    }
    return b;
}

template<typename T>
T mod_inv(T x, T m){
    T s, t;
    extgcd(x, m, s, t);
    return (m+s)% m;
}

#include <cmath>
namespace FFT {
    const int max_base = 19, maxN = 1 << max_base; // N <= 2e5
    const double PI = acos(-1);
    struct num {
        double x{}, y{};
        num() = default;
        num(double x, double y): x(x), y(y) {}
        explicit num(double r): x(cos(r)), y(sin(r)) {}
    };
    num operator+(num a, num b) { return {a.x + b.x, a.y + b.y}; }
    num operator-(num a, num b) { return {a.x - b.x, a.y - b.y}; }
    num operator*(num a, num b) { return {a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x}; }
    num conj(num a) {return {a.x, -a.y}; }
    num root[maxN];
    int rev[maxN];
    bool is_root_prepared = false;

    void prepare_root(){
        if(is_root_prepared) return;
        is_root_prepared = true;
        root[1] = num(1, 0);
        for (int i = 1; i < max_base; ++i) {
            num x(2*PI / (1LL << (i+1)));
            for (ll j = (1LL << (i-1)); j < (1LL << (i)); ++j) {
                root[2*j] = root[j];
                root[2*j+1] = root[j]*x;
            }
        }
    }

    int base, N;
    int lastN = -1;

    void prepare_rev(){
        if(lastN == N) return;
        lastN = N;
        for (int i = 0; i < N; ++i) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (base - 1));
    }

    void fft(num *a, num *f){
        for (int i = 0; i < N; ++i) f[i] = a[rev[i]];
        for (int k = 1; k < N; k <<= 1) {
            for (int i = 0; i < N; i += 2*k) {
                for (int j = 0; j < k; ++j) {
                    num z = f[i+j+k]* root[j+k];
                    f[i+j+k] = f[i+j] - z;
                    f[i+j] = f[i+j] + z;
                }
            }
        }
    }
    num a[maxN], b[maxN], f[maxN], g[maxN];
    ll A[maxN], B[maxN], C[maxN];

    void multi_mod(int m){
        for (int i = 0; i < N; ++i) {
            a[i] = num( A[i] & ((1LL << 15)-1),  A[i] >> 15);
        }
        for (int i = 0; i < N; ++i) {
            b[i] = num(B[i] & ((1LL << 15)-1), B[i] >> 15);
        }
        fft(a, f);
        fft(b, g);
        for (int i = 0; i < N; ++i) {
            int j = (N-i) &(N-1);
            num a1 = (f[i] + conj(f[j])) * num(0.5, 0);
            num a2 = (f[i] - conj(f[j])) * num(0, -0.5);
            num b1 = (g[i] + conj(g[j])) * num(0.5/N, 0);
            num b2 = (g[i] - conj(g[j])) * num(0, -0.5/N);
            a[j] = a1*b1 + a2*b2 * num(0, 1);
            b[j] = a1*b2 + a2*b1;
        }
        fft(a, f);
        fft(b, g);
        for (int i = 0; i < N; ++i) {
            ll aa = f[i].x + 0.5;
            ll bb = g[i].x + 0.5;
            ll cc = f[i].y + 0.5;
            C[i] = (aa + bb % m * (1LL << 15) + cc% m *(1LL << 30)) % m;
        }
    }

    void prepare_AB(int n1, int n2){
        base = 1;
        N = 2;
        while(N < n1+n2) base++, N <<= 1;
        for (int i = n1; i < N; ++i) A[i] = 0;
        for (int i = n2; i < N; ++i) B[i] = 0;
        prepare_root();
        prepare_rev();
    }

    void multi_mod(int n1, int n2, int m){
        prepare_AB(n1, n2);
        multi_mod(m);
    }
}


struct poly {
    vector<int> v;
    poly() = default;
    explicit poly(vector<int> vv) : v(std::move(vv)) {};
    explicit poly(size_t n) : v(n) {};
    int size() const {return (int)v.size(); }
    poly cut(int len){
        if(len < v.size()) v.resize(static_cast<unsigned long>(len));
        return *this;
    }
    inline int& operator[] (int i) {return v[i]; }
   

    poly inv() const {
        int n = size();
        vector<int> rr(1, mod_inv(this->v[0], MOD));
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
                nr[i] = (2*r[i]-nr[i]+MOD)%MOD;
                nr[i+k/2] = (MOD-nr[i+k/2])%MOD;
            }
            r = nr;
        }
        r.v.resize(n);
        return r;
    }

    poly operator+(const poly &a) const { return poly(*this) += a; }
    poly operator-(const poly &a) const { return poly(*this) -= a; }
    poly operator*(const poly &a) const { return poly(*this) *= a; }
    poly operator/(const poly &a) const { return poly(*this) /= a; }

    poly& operator+=(const poly &a) {
        this->v.resize(max(size(), a.size()));
        for (int i = 0; i < a.size(); ++i) {
            (this->v[i] += a.v[i]);
            if(this->v[i] > MOD) this->v[i] -= MOD;
        }
        return *this;
    }
    poly& operator-=(const poly &a) {
        this->v.resize(max(size(), a.size()));
        for (int i = 0; i < a.size(); ++i) {
            (this->v[i] += MOD-a.v[i]);
            if(this->v[i] > MOD) this->v[i] -= MOD;
        }
        return *this;
    }

    poly& operator*=(const poly &a) {
        for (int i = 0; i < size(); ++i) FFT::A[i] = this->v[i];
        for (int i = 0; i < a.size(); ++i) FFT::B[i] = a.v[i];
        FFT::multi_mod(size(), a.size(), MOD);
        this->v.resize(size() + a.size()-1);
        for (int i = 0; i < size(); ++i) this->v[i] = FFT::C[i];
        return *this;
    }
    
    poly& operator/=(const poly &a){
        return (*this *= a.inv()); 
    }
};