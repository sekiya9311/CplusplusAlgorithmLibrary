// 2次元幾何

namespace geometry2d {
    const double EPS = 1e-10;
    inline double add(double a, double b) {
        if (abs(a + b) < geometry2d::EPS * (abs(a) + abs(b))) return 0;
        return a + b;
    }
    inline int sgn(double a, double b = 0.0) {// sign function
        return a < b - EPS ? -1 : a > b + EPS ? 1 : 0;
    }

    struct Point {//二次元座標
        double x, y;
        Point() {}
        Point(double _x, double _y) : x(_x), y(_y) {}
        const geometry2d::Point operator+ (const geometry2d::Point p) {
            return Point(geometry2d::add(this->x, p.x), geometry2d::add(this->y, p.y));
        }
        const geometry2d::Point operator- (const geometry2d::Point p) {
            return Point(geometry2d::add(this->x, -p.x), geometry2d::add(this->y, -p.y));
        }
        const geometry2d::Point operator* (double d) {
            return Point(this->x * d, this->y * d);
        }
    };

    struct Line {
        geometry2d::Point a, b, dis;
        Line() {}
        Line(const geometry2d::Point &_a, const geometry2d::Point &_b) : a(_a), b(_b), dis(b - a) {}
        double distSquare() { //距離の二乗
            return (this->a.x - this->b.x) * (this->a.x - this->b.x) + (this->a.y - this->b.y) * (this->a.y - this->b.y);
        }
        double distance() {
            return sqrt(this->distSquare());
        }
    };

    double naiseki(const geometry2d::Point &p1, const geometry2d::Point &p2) {
        return geometry2d::add(p1.x * p2.x, p1.y * p2.y);
    }
    double gaiseki(const geometry2d::Point &p1, const geometry2d::Point &p2) {
        return geometry2d::add(p1.x * p2.y, -p1.y * p2.x);
    }
    Point intersection(geometry2d::Line &l1, geometry2d::Line &l2) {//p1-p2とq1-q2の交点
        auto buf = (l1.b - l1.a);
        return l1.a + buf * (gaiseki(l2.b - l2.a, l2.a - l1.a) / gaiseki(l2.b - l2.a, l1.b - l1.a));
    }
    bool colinear(const geometry2d::Point &p1, const geometry2d::Point &p2, const geometry2d::Point &p3) {// 三点が一直線上にあるか
        return (p3.y - p1.y) * (p2.x - p1.x) == (p2.y - p1.y) * (p3.x - p1.x);
    }
    bool on_seg(geometry2d::Point &p, geometry2d::Line &l) {//線分l上にこの点pがあるか
        return geometry2d::sgn(geometry2d::gaiseki((l.a - p), (l.b - p))) == 0 && geometry2d::naiseki(l.a - p, l.b - p) <= 0;
    }
    bool isIntersect(geometry2d::Line &l1, geometry2d::Line &l2) { // l1とl2が交差してるか
        Point intersect = intersection(l1, l2);
        return on_seg(intersect, l1) && on_seg(intersect, l2);
    }

    struct Circle {//円
        double r;//半径
        Point center;//中心座標
        Circle() {}
        Circle(double _x, double _y, double _r) : r(_r), center(_x, _y) {}
        Circle(const Point &_p, double _r) : r(_r), center(_p) {}
        bool inside(Point &p) {//円内部に居るか(円周含まない)
            return geometry2d::sgn(geometry2d::add(geometry2d::Line(p, this->center).distSquare(), -(this->r * this->r))) == -1;
        }
        bool on_seg(Point &p) {//円周上に居るか
            return geometry2d::sgn(geometry2d::add(geometry2d::Line(p, this->center).distSquare(), -(this->r * this->r))) == 0;
        }
        double square() {
            return this->r * this->r * acos(-1.0);
        }
    };
};
