using real = double;
real EPS = 1e-10;
struct Point {
    real x, y;
    Point& operator+=(const Point a) { x += a.x; y += a.y;  return *this; }
    Point& operator-=(const Point a) { x -= a.x; y -= a.y;  return *this; }
    Point& operator*=(const real k) { x *= k; y *= k;  return *this; }
    Point& operator/=(const real k) { x /= k; y /= k;  return *this; }
    Point operator+(const Point a) const {return Point(*this) += a; }
    Point operator-(const Point a) const {return Point(*this) -= a; }
    Point operator*(const real k) const {return Point(*this) *= k; }
    Point operator/(const real k) const {return Point(*this) /= k; }
    bool operator<(const Point &a) const { return (x != a.x ? x < a.x : y < a.y); }
    explicit Point(real a = 0, real b = 0) : x(a), y(b) {};
};

bool sorty(Point a, Point b){
    return (a.y != b.y ? a.y < b.y : a.x < b.x);
}

istream& operator>> (istream& s, Point& P){
    s >> P.x >> P.y;
    return s;
}

inline real dot(Point a, Point b){ return a.x*b.x + a.y*b.y; }
inline real cross(Point a, Point b){ return a.x*b.y - a.y*b.x; }
inline real abs(Point a){ return sqrt(dot(a, a)); }

static constexpr int COUNTER_CLOCKWISE = 1;
static constexpr int CLOCKWISE = -1;
static constexpr int ONLINE_BACK = 2;
static constexpr int ONLINE_FRONT = -2;
static constexpr int ON_SEGMENT = 0;

int ccw(Point a, Point b, Point c){
    b -= a; c -= a;
    if(cross(b, c) > EPS) return COUNTER_CLOCKWISE;
    if(cross(b, c) < -EPS) return CLOCKWISE;
    if(dot(b, c) < 0) return ONLINE_BACK;
    if(abs(b) < abs(c)) return ONLINE_FRONT;
    return ON_SEGMENT;
}
struct Segment {
    Point a, b;
    Segment(Point x, Point y) : a(x), b(y) {};
};

struct Line {
    Point a, b;
    Line(Point x, Point y) : a(x), b(y) {};
};

bool intersect(Segment s, Segment t){
    return (ccw(s.a, s.b, t.a)*ccw(s.a, s.b, t.b) <= 0 &&
            ccw(t.a, t.b, s.a)*ccw(t.a, t.b, s.b) <= 0);
}

double distance(Segment s, Point c){
    if(dot(s.b-s.a, c-s.a) < EPS) return abs(c-s.a);
    if(dot(s.a-s.b, c-s.b) < EPS) return abs(c-s.b);
    return abs(cross(s.b-s.a, c-s.a)) / abs(s.a-s.b);
}

double distance(Segment s, Segment t){
    if(intersect(s, t)) return 0.0;
    return min({distance(s, t.a), distance(s, t.b),
                distance(t, s.a), distance(t, s.b)});
}



Point crossPoint(Segment s, Segment t){
    real d1 = cross(s.b-s.a, t.b-t.a);
    real d2 = cross(s.b-s.a, s.b-t.a);
    if(fabs(d1) < EPS && fabs(d2) < EPS) return t.a;
    return t.a+(t.b-t.a)*d2/d1;
}

Point crossPoint(Line s, Line t){
    real d1 = cross(s.b-s.a, t.b-t.a);
    real d2 = cross(s.b-s.a, s.b-t.a);
    if(fabs(d1) < EPS && fabs(d2) < EPS) return t.a;
    return t.a+(t.b-t.a)*d2/d1;
}


Point project(Segment s, Point p){
    Point Q = s.b-s.a;
    return s.a + Q*(dot(p-s.a, Q) / dot(Q, Q));
}

Point refrect(Segment s, Point p){
    Point Q = project(s, p);
    return Q*2-p;
}

bool isOrthogonal(Segment s, Segment t){
    return fabs(dot(s.b-s.a, t.b-t.a)) < EPS;
}

bool isparallel(Segment s, Segment t){
    return fabs(cross(s.b-s.a, t.b-t.a)) < EPS;
}

using Polygon = vector<Point>;

real area(Polygon v){
    if(v.size() < 3) return 0.0;
    real ans = 0.0;
    for (int i = 0; i < v.size(); ++i) {
        ans += cross(v[i], v[(i+1)%v.size()]);
    }
    return ans/2;
}

Polygon convex_hull(Polygon v){
    int n = v.size();
    sort(v.begin(),v.end(), sorty);
    int k = 0;
    Polygon ret(n*2);
    for (int i = 0; i < n; ++i) {
        while(k > 1 && cross(ret[k-1]-ret[k-2], v[i]-ret[k-1]) < 0) k--;
        ret[k++] = v[i];
    }
    for(int i = n-2, t=k; i >= 0; i--){
        while(k > t && cross(ret[k-1]-ret[k-2], v[i]-ret[k-1]) < 0) k--;
        ret[k++] = v[i];
    }
    ret.resize(k-1);
    return ret;
}

bool isconvex(Polygon v){
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        if(ccw(v[(i+n-1)%n], v[i], v[(i+1)%n]) == CLOCKWISE) return false;
    }
    return true;
}

// in = 2, on = 1, out = 0;
int contains(Polygon v, Point p){
    int n = v.size();
    bool x = false;
    for (int i = 0; i < n; ++i) {
        Point a = v[i]-p, b = v[(i+1)%n]-p;
        if(fabs(cross(a, b)) < EPS && dot(a, b) < EPS) return 1;
        if(a.y > b.y) swap(a, b);
        if(a.y < EPS && EPS < b.y && cross(a, b) > EPS) x = !x;
    }
    return (x?2:0);
}

double diameter(Polygon v){
    int n = v.size();
    if(n == 2) return abs(v[0]-v[1]);
    int i = 0, j = 0;
    for (int k = 0; k < n; ++k) {
        if(v[i] < v[k]) i = k;
        if(!(v[j] < v[k])) j = k;
    }
    double ret = 0;
    int si = i, sj = j;
    while(i != sj || j != si){
        ret = max(ret, abs(v[i]-v[j]));
        if(cross(v[(i+1)%n]-v[i], v[(j+1)%n]-v[j]) < 0.0) i = (i+1)%n;
        else j = (j+1)%n;
    }
    return ret;
}

Polygon convexCut(Polygon v, Line l){
    Polygon q;
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        Point a = v[i], b = v[(i+1)%n];
        if(ccw(l.a, l.b, a) != -1) q.push_back(a);
        if(ccw(l.a, l.b, a)*ccw(l.a, l.b, b) < 0){
            q.push_back(crossPoint(Line(a, b), l));
        }
    }
    return q;
}
