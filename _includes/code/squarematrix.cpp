template<class T, size_t SIZE>
struct SquareMatrix {
    using ar = array<T, SIZE>;
    using mat = array<ar, SIZE>;
    mat A;
    SquareMatrix() = default;
    static SquareMatrix I(T e){
        SquareMatrix X;
        for (int i = 0; i < SIZE; ++i) {
            X[i][i] = e;
        }
        return X;
    }

    inline const ar &operator[](int k) const{ return (A.at(k)); }
    inline ar &operator[](int k) { return (A.at(k)); }
    SquareMatrix &operator+= (const SquareMatrix &B){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                (*this)[i][j] += B[i][j];
            }
        }
        return (*this);
    }

    SquareMatrix &operator-= (const SquareMatrix &B){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                (*this)[i][j] -= B[i][j];
            }
        }
        return (*this);
    }

    SquareMatrix &operator*=(const SquareMatrix &B) {
        SquareMatrix C;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < SIZE; ++k) {
                    C[i][j] += ((*this)[i][k] * B[k][j]);
                }
            }
        }
        A.swap(C.A);
        return (*this);
    }

    SquareMatrix pow(ll n) const {
        SquareMatrix a = (*this), res = I(T(1));
        while(n > 0){
            if(n & 1) res *= a;
            a *= a;
            n >>= 1;
        }
        return res;
    }
    SquareMatrix operator+(const SquareMatrix &B) const {return SquareMatrix(*this) += B;}
    SquareMatrix operator-(const SquareMatrix &B) const {return SquareMatrix(*this) -= B;}
    SquareMatrix operator*(const SquareMatrix &B) const {return SquareMatrix(*this) *= B;}
};