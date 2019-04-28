vector<int> get_prime(int n) {
    if(n <= 1) return vector<int>{};
    vector<bool> is_composite(n+1);
    vector<int> prime;
    for (int i = 2; i <= n; ++i) {
        if(!is_composite[i]) prime.push_back(i);
        for (auto &&j : prime) {
            if((ll)i*j > n) continue;
            is_composite[i*j] = true;
            if(i % j == 0) break;
        }
    }
    return prime;
}
const auto primes = get_prime(65535);

template<class T>
vector<T> prime_factor(T n){
    vector<T> res;
    for (auto &&i : primes) {
        while (n % i == 0){
            res.emplace_back(i);
            n /= i;
        }
    }
    if(n != 1) res.emplace_back(n);
    return res;
}