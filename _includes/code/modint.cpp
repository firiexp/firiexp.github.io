template<ll M = 1000000007>
struct modint{
    ll val;
    modint(): val(0){}
    template<typename T>
    explicit modint(T t){val = t%M; if(val < 0) val += M;}
 
    modint pow(ll k){
        modint res(1), x(val);
        while(k){
            if(k&1) res *= x;
            x *= x;
            k >>= 1;
        }
        return res;
    }
    template<typename T>
    modint& operator=(T a){ val = a%M; if(val < 0) val += M; return *this; }
    modint inv() {return pow(M-2);}
    modint& operator+=(modint a){ val += a.val; if(val >= M) val -= M; return *this;}
    modint& operator-=(modint a){ val += M-a.val; if(val >= M) val -= M; return *this;}
    modint& operator*=(modint a){ val = 1LL*val*a.val%M; return *this;}
    modint& operator/=(modint a){ return (*this) *= a.inv();}
    modint operator+(modint a) const {return modint(val) +=a;}
    modint operator-(modint a) const {return modint(val) -=a;}
    modint operator*(modint a) const {return modint(val) *=a;}
    modint operator/(modint a) const {return modint(val) /=a;}
    modint operator-(){ return modint(-val);}
    bool operator==(const modint a) const {return val == a.val;}
    bool operator!=(const modint a) const {return val != a.val;}
    bool operator<(const modint a) const {return val < a.val;}
};
 
using mint = modint<MOD>;