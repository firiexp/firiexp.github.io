vector<int> get_prime(int n){
    if(n <= 1) return vector<int>();
    vector<bool> iscomp(n+1);
    vector<int> prime;
    for (int i = 2; i <= n; ++i) {
        if(!iscomp[i]) prime.emplace_back(i);
        for (auto &&j : prime){
            if((ll)i*j > n) break;
            iscomp[i*j] = true;
            if(i % j == 0) break;
        }
    }
    return prime;
}