// 2次元幾何

namespace geometry2d {
    const double EPS = 1e-10;
    inline double add(double a, double b) {
        if (std::abs(a + b) < geometry2d::EPS * (std::abs(a) + std::abs(b))) return 0;
        return a + b;
    }
    inline int sgn(double a, double b = 0.0) {// sign function
        return a < b - EPS ? -1 : a > b + EPS ? 1 : 0;
    }

    struct point {//二次元座標
        double x, y;
        point() {}
        point(double _x, double _y) : x(_x), y(_y) {}
        const geometry2d::point operator+ (const geometry2d::point p) {
            return point(geometry2d::add(this->x, p.x), geometry2d::add(this->y, p.y));
        }
        const geometry2d::point operator- (const geometry2d::point p) {
            return point(geometry2d::add(this->x, -p.x), geometry2d::add(this->y, -p.y));
        }
        const geometry2d::point operator* (double d) {
            return point(this->x * d, this->y * d);
        }
    };

    struct line {
        geometry2d::point a, b, dis;
        line() {}
        line(const geometry2d::point &_a, const geometry2d::point &_b) : a(_a), b(_b), dis(b - a) {}
        double distSquare() { //距離の二乗
            return (this->a.x - this->b.x) * (this->a.x - this->b.x) + (this->a.y - this->b.y) * (this->a.y - this->b.y);
        }
        double distance() {
            return std::sqrt(this->distSquare());
        }
    };

    double naiseki(const geometry2d::point &p1, const geometry2d::point &p2) {
        return geometry2d::add(p1.x * p2.x, p1.y * p2.y);
    }
    double gaiseki(const geometry2d::point &p1, const geometry2d::point &p2) {
        return geometry2d::add(p1.x * p2.y, -p1.y * p2.x);
    }
    point intersection(geometry2d::line &l1, geometry2d::line &l2) {//p1-p2とq1-q2の交点
        auto buf = (l1.b - l1.a);
        return l1.a + buf * (gaiseki(l2.b - l2.a, l2.a - l1.a) / gaiseki(l2.b - l2.a, l1.b - l1.a));
    }
    bool colinear(const geometry2d::point &p1, const geometry2d::point &p2, const geometry2d::point &p3) {// 三点が一直線上にあるか
        return (p3.y - p1.y) * (p2.x - p1.x) == (p2.y - p1.y) * (p3.x - p1.x);
    }
    bool on_seg(geometry2d::point &p, geometry2d::line &l) {//線分l上にこの点pがあるか
        return geometry2d::sgn(geometry2d::gaiseki((l.a - p), (l.b - p))) == 0 && geometry2d::naiseki(l.a - p, l.b - p) <= 0;
    }
    bool is_intersect(geometry2d::line &l1, geometry2d::line &l2) { // l1とl2が交差してるか
        point intersect = intersection(l1, l2);
        return on_seg(intersect, l1) && on_seg(intersect, l2);
    }

    struct circle {//円
        double r;//半径
        point center;//中心座標
        circle() {}
        circle(double _x, double _y, double _r) : r(_r), center(_x, _y) {}
        circle(const point &_p, double _r) : r(_r), center(_p) {}
        bool inside(point &p) {//円内部に居るか(円周含まない)
            return geometry2d::sgn(geometry2d::add(geometry2d::line(p, this->center).distSquare(), -(this->r * this->r))) == -1;
        }
        bool on_seg(point &p) {//円周上に居るか
            return geometry2d::sgn(geometry2d::add(geometry2d::line(p, this->center).distSquare(), -(this->r * this->r))) == 0;
        }
        double square() {
            return this->r * this->r * std::acos(-1.0);
        }
    };
};
