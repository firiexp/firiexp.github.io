template <ll M = MOD> struct modint {
public:
    ll val;
    explicit modint(const ll x = 0) : val(x) {}
    modint operator+(const modint a) const { return modint(*this) += a; }
    modint operator-(const modint a) const { return modint(*this) -= a; }
    modint operator*(const modint a) const { return modint(*this) *= a; }
    modint operator/(const modint a) const { return modint(*this) /= a; }
    modint operator-() const { return modint(M-val); }
    modint inv(){
        ll u = 1, v = 0, s = 0, t = 1, m = M, x = val;
        while (x) {ll q = m/x; swap(s -= q*u, u); swap(t -= q*v, v); swap(m -= q*x, x); }
        if(s < 0) s += M;
        return modint(s);
    }
    modint pow(ll n){
        ll u = 1, xx = val;
        while (n > 0){ if (n&1) u = u * xx % M; xx = xx * xx % M; n >>= 1; }
        return u;
    }
    modint &operator+=(const modint a){ val += a.val; if(val >= M) val -= M; return *this; }
    modint &operator-=(const modint a){ val += a.val; if(val < 0) val += M; return *this; }
    modint &operator*=(const modint a){ val = val * a.val % M; return *this; }
    modint &operator/=(const modint a){ val = (val*a.inv()) %M; return *this;}
};