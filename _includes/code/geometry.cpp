using real = double;
real EPS = 1e-10;
struct Point {
    real x, y;
    Point& operator+=(const Point a) { x += a.x; y += a.y;  return *this; }
    Point& operator-=(const Point a) { x -= a.x; y -= a.y;  return *this; }
    Point operator+(const Point a) const {return Point(*this) += a; }
    Point operator-(const Point a) const {return Point(*this) -= a; }
    bool operator<(const Point &a) const { return (x != a.x ? x < a.x : y < a.y); }
    explicit Point(real a = 0, real b = 0) : x(a), y(b) {};
};

inline real dot(Point a, Point b){ return a.x*b.x + a.y*b.y; }
inline real cross(Point a, Point b){ return a.x*b.y - a.y*b.x; }
inline real abs(Point a){ return sqrt(dot(a, a)); }

struct Segment {
    Point a, b;
    Segment(Point x, Point y) : a(x), b(y) {};
};

double distance(Segment l, Point c){
    if(dot(l.b-l.a, c-l.a) < EPS) return abs(c-l.a);
    if(dot(l.a-l.b, c-l.b) < EPS) return abs(c-l.b);
    return abs(cross(l.b-l.a, c-l.a)) / abs(l.a-l.b);
}
