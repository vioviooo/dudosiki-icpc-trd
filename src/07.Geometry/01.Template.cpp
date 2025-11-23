const double EPS = 1e-9;
const double PI = acos(-1.0);

// Helper functions for floating point comparisons
bool eq(double a, double b) { return fabs(a - b) < EPS; }
bool lt(double a, double b) { return a - b < -EPS; }
bool le(double a, double b) { return a - b < EPS; }
bool gt(double a, double b) { return a - b > EPS; }
bool ge(double a, double b) { return a - b > -EPS; }

// Point/Vector class
struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
    
    // Vector operations
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator*(double k) const { return Point(x * k, y * k); }
    Point operator/(double k) const { return Point(x / k, y / k); }
    
    // Comparison (lexicographical)
    bool operator<(const Point& p) const {
        return !eq(x, p.x) ? lt(x, p.x) : lt(y, p.y);
    }
    bool operator==(const Point& p) const {
        return eq(x, p.x) && eq(y, p.y);
    }
    
    // Dot product
    double dot(const Point& p) const { return x * p.x + y * p.y; }
    
    // Cross product
    double cross(const Point& p) const { return x * p.y - y * p.x; }
    
    // Distance
    double dist(const Point& p) const { return hypot(x - p.x, y - p.y); }
    
    // Length of vector
    double len() const { return hypot(x, y); }
    
    // Rotate point by theta radians (counter-clockwise)
    Point rotate(double theta) const {
        double c = cos(theta), s = sin(theta);
        return Point(x * c - y * s, x * s + y * c);
    }
    
    // Normalize vector
    Point normalize() const {
        double l = len();
        return Point(x / l, y / l);
    }
};

// Line class
struct Line {
    // ax + by + c = 0
    double a, b, c;
    
    Line() : a(0), b(0), c(0) {}
    Line(double a, double b, double c) : a(a), b(b), c(c) {}
    
    // Construct line from two points
    Line(const Point& p1, const Point& p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = p2.x * p1.y - p1.x * p2.y;
        
        // Normalize
        double len = hypot(a, b);
        if (!eq(len, 0)) {
            a /= len; b /= len; c /= len;
        }
    }
    
    // Evaluate line at point
    double eval(const Point& p) const {
        return a * p.x + b * p.y + c;
    }
    
    // Distance from point to line
    double dist(const Point& p) const {
        return fabs(eval(p)) / hypot(a, b);
    }
};

// Counter-clockwise test
// Returns: 
//  1 if points are counter-clockwise (p1 -> p2 -> p3 turns left)
// -1 if clockwise (turns right)
//  0 if collinear
int ccw(const Point& p1, const Point& p2, const Point& p3) {
    double cross = (p2 - p1).cross(p3 - p1);
    if (gt(cross, 0)) return 1;    // counter-clockwise
    if (lt(cross, 0)) return -1;   // clockwise
    return 0;                      // collinear
}

// Check if point p lies on segment ab
bool onSegment(const Point& a, const Point& b, const Point& p) {
    return eq(ccw(a, b, p), 0) && 
           le((p - a).dot(p - b), 0);
}

// Check if two line segments intersect
bool segmentIntersect(const Point& a, const Point& b, 
                     const Point& c, const Point& d) {
    int ab_c = ccw(a, b, c);
    int ab_d = ccw(a, b, d);
    int cd_a = ccw(c, d, a);
    int cd_b = ccw(c, d, b);
    
    // Proper intersection
    if (ab_c * ab_d < 0 && cd_a * cd_b < 0) return true;
    
    // Check for endpoint intersections
    if (onSegment(a, b, c) || onSegment(a, b, d) ||
        onSegment(c, d, a) || onSegment(c, d, b)) return true;
    
    return false;
}

// Andrew's Monotone Chain convex hull
vector<Point> convexHull(vector<Point> points) {
    int n = points.size();
    if (n <= 1) return points;
    
    sort(points.begin(), points.end());
    
    vector<Point> hull;
    
    // Build lower hull
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 && 
               ccw(hull[hull.size()-2], hull.back(), points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    
    // Build upper hull
    int lower_size = hull.size();
    for (int i = n - 2; i >= 0; i--) {
        while (hull.size() > lower_size && 
               ccw(hull[hull.size()-2], hull.back(), points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    
    // Remove duplicate point (first and last are the same)
    if (hull.size() > 1) hull.pop_back();
    
    return hull;
}

// Polygon area (signed)
double polygonArea(const vector<Point>& poly) {
    double area = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += poly[i].cross(poly[j]);
    }
    return fabs(area) / 2.0;
}

// Check if point is inside polygon (ray casting algorithm)
bool pointInPolygon(const vector<Point>& poly, const Point& p) {
    int n = poly.size();
    int cnt = 0;
    
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        Point a = poly[i], b = poly[j];
        
        // Check if point is on boundary
        if (onSegment(a, b, p)) return true;
        
        // Ray casting
        if ((lt(a.y, p.y) && ge(b.y, p.y) || 
             lt(b.y, p.y) && ge(a.y, p.y)) &&
            lt(p.x, (b.x - a.x) * (p.y - a.y) / (b.y - a.y) + a.x)) {
            cnt++;
        }
    }
    return cnt % 2 == 1;
}

// Distance between two line segments
double segmentDist(const Point& a, const Point& b, 
                  const Point& c, const Point& d) {
    if (segmentIntersect(a, b, c, d)) return 0.0;
    
    double dist = min({
        Line(a, b).dist(c),
        Line(a, b).dist(d),
        Line(c, d).dist(a),
        Line(c, d).dist(b),
        a.dist(c), a.dist(d),
        b.dist(c), b.dist(d)
    });
    
    return dist;
}

int main() {
    vector<Point> points = {
        Point(0, 0), Point(4, 0), Point(4, 4), 
        Point(2, 2), Point(0, 4), Point(1, 1)
    };
    
    auto hull = convexHull(points);
    cout << "Convex hull points:" << endl;
    for (auto& p : hull) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }
    
    double area = polygonArea(hull);
    cout << "Convex hull area: " << area << endl;
    
    Point p1(0, 0), p2(1, 0), p3(0, 1);
    cout << "CCW test: " << ccw(p1, p2, p3) << " (should be 1)" << endl;
    
    Point a(0, 0), b(2, 2), c(0, 2), d(2, 0);
    cout << "Segments intersect: " << segmentIntersect(a, b, c, d) << " (should be 1)" << endl;
    
    return 0;
}