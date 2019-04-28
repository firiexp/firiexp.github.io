template<class T>
class monotonic_CHT {
    using P = pair<T, T>;
    vector<P> lines;
public:
    monotonic_CHT() {}

    bool check(P l1, P l2, P l3){
        if(l1 < l3) swap(l1, l3);
        return (l3.second - l2.second)*(l2.first-l1.first)
            >= (l2.second - l1.second)*(l3.first-l2.first);
    }
    void add(T a, T b){
        P line(a, b);
        while(lines.size() >= 2 && check(*(lines.end()-2), lines.back(), line)) lines.pop_back();
        lines.emplace_back(line);
    }

    T f(int i, T x){
        return lines[i].first * x + lines[i].second;
    }

    T f(P line, T x){
        return line.first * x + line.second;
    }

    T get(T x){
        static int head = 0;
        while(lines.size()-head >= 2 && f(head, x) >= f(head+1, x)) ++head;
        return f(head, x);
    }
};