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
            ll x = A[i] % m;
            a[i] = num(x & ((1LL << 15)-1), x >> 15);
        }
        for (int i = 0; i < N; ++i) {
            ll x = B[i] % m;
            b[i] = num(x & ((1LL << 15)-1), x >> 15);
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
    int size() {return (int)v.size(); }
    poly cut(int len){
        if(len < v.size()) v.resize(static_cast<unsigned long>(len));
        return *this;
    }
    inline int& operator[] (int i) {return v[i]; }
};

poly operator+(poly &A, poly &B){
    poly C;
    C.v = vector<int>(max(A.size(), B.size()));
    for (int i = 0; i < A.size(); ++i) C[i] = A[i];
    for (int i = 0; i < B.size(); ++i) (C[i] += B[i]) %= MOD;
    return C;
}

poly operator-(poly &A, poly &B){
    poly C;
    C.v = vector<int>(max(A.size(), B.size()));
    for (int i = 0; i < A.size(); ++i) C[i] = A[i];
    for (int i = 0; i < B.size(); ++i) (C[i] += MOD-B[i]) %= MOD;
    return C;
}

poly operator* (poly &A, poly &B){
    poly C;
    C.v = vector<int>(A.size() + B.size()-1);
    for (int i = 0; i < A.size(); ++i) FFT::A[i] = A[i];
    for (int i = 0; i < B.size(); ++i) FFT::B[i] = B[i];
    FFT::multi_mod(A.size(), B.size(), MOD);
    for (int i = 0; i < C.size(); ++i) C[i] = FFT::C[i];
    return C;
}