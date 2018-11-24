// 2次元幾何
#include <cmath>
#include <algorithm>
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
        const geometry2d::point operator+ (const geometry2d::point p) const {
            return point(geometry2d::add(this->x, p.x), geometry2d::add(this->y, p.y));
        }
        const geometry2d::point operator- (const geometry2d::point p) const {
            return point(geometry2d::add(this->x, -p.x), geometry2d::add(this->y, -p.y));
        }
        const geometry2d::point operator* (double d) const {
            return point(this->x * d, this->y * d);
        }
        bool operator==(const geometry2d::point &other) const {
            return sgn(x, other.x) == 0 && sgn(y, other.y) == 0;
        }
        bool operator!=(const geometry2d::point &other) const {
            return !(*this == other);
        }
        const point clone() const {
            return point(x, y);
        }
    };

    struct rectangle {
        enum class direction {
            left_down,
            left_up,
            right_down,
            right_up
        };
        point left_down, right_up;
        rectangle() {}
        rectangle(point a, point b) : 
            left_down(std::min(a.x, b.x), std::min(a.y, b.y)), 
            right_up(std::max(a.x, b.x), std::max(a.y, b.y)) {}
        rectangle(double x1, double y1, double x2, double y2)
            : left_down(x1, y1), right_up(x2, y2) {}
        const double square() const {
            return std::abs(left_down.x - right_up.x) * std::abs(left_down.y - right_up.y);
        }
        bool operator==(const rectangle &other) const {
            return left_down == other.left_down && right_up == other.right_up;
        }
        bool operator!=(const rectangle &other) const {
            return !(*this == other);
        }
        const point get_point(direction dir) const {
            switch (dir) {
                case direction::left_down: {
                    return left_down.clone();
                    break;
                }
                case direction::left_up: {
                    return point(std::min(left_down.x, right_up.x), std::max(left_down.y, right_up.y));
                    break;
                }
                case direction::right_down: {
                    return point(std::max(left_down.x, right_up.x), std::min(left_down.y, right_up.y));
                    break;
                }
                case direction::right_up: {
                    return right_up.clone();
                    break;
                }
                default: {
                    throw std::invalid_argument("dir");
                    break;
                }
            }
        }
    };

    struct line {
        geometry2d::point a, b, dis;
        line() {}
        line(const geometry2d::point &_a, const geometry2d::point &_b) : a(_a), b(_b), dis(b - a) {}
        const double distSquare() const { //距離の二乗
            return (this->a.x - this->b.x) * (this->a.x - this->b.x) + (this->a.y - this->b.y) * (this->a.y - this->b.y);
        }
        const double distance() const {
            return std::sqrt(this->distSquare());
        }
    };

    const double naiseki(const geometry2d::point &p1, const geometry2d::point &p2) {
        return geometry2d::add(p1.x * p2.x, p1.y * p2.y);
    }
    const double gaiseki(const geometry2d::point &p1, const geometry2d::point &p2) {
        return geometry2d::add(p1.x * p2.y, -p1.y * p2.x);
    }
    const geometry2d::point intersection(geometry2d::line &l1, geometry2d::line &l2) {//p1-p2とq1-q2の交点
        auto buf = (l1.b - l1.a);
        return l1.a + buf * (gaiseki(l2.b - l2.a, l2.a - l1.a) / gaiseki(l2.b - l2.a, l1.b - l1.a));
    }
    const bool colinear(const geometry2d::point &p1, const geometry2d::point &p2, const geometry2d::point &p3) {// 三点が一直線上にあるか
        return (p3.y - p1.y) * (p2.x - p1.x) == (p2.y - p1.y) * (p3.x - p1.x);
    }
    const bool on_seg(const geometry2d::point &p, const geometry2d::line &l) {//線分l上にこの点pがあるか
        return geometry2d::sgn(geometry2d::gaiseki((l.a - p), (l.b - p))) == 0 && geometry2d::naiseki(l.a - p, l.b - p) <= 0;
    }
    const bool is_intersect(geometry2d::line &l1, geometry2d::line &l2) { // l1とl2が交差してるか
        point intersect = intersection(l1, l2);
        return on_seg(intersect, l1) && on_seg(intersect, l2);
    }
    const bool is_left(const geometry2d::line &l, const geometry2d::point &p, const bool permit_on_seg = true) {// !!! ベクトル(a, b)に対して !!!
        if (permit_on_seg && geometry2d::on_seg(p, l)) {
            return true;
        }
        const auto foo = p - l.a;
        return geometry2d::sgn(l.dis.x * foo.y - l.dis.y * foo.x) == 1;
    }
    const bool is_right(const geometry2d::line &l, const geometry2d::point &p, const bool permit_on_seg = true) {// !!! ベクトル(a, b)に対して !!!
        if (permit_on_seg && geometry2d::on_seg(p, l)) {
            return true;
        }
        return !geometry2d::is_left(l, p, false);
    }
    const geometry2d::rectangle intersect(const geometry2d::rectangle &a, const geometry2d::rectangle b) { // 2つの長方形の重なっている部分を返す
        const auto sx = std::max(a.get_point(rectangle::direction::left_down).x, b.get_point(rectangle::direction::left_down).x);
        const auto sy = std::max(a.get_point(rectangle::direction::left_down).y, b.get_point(rectangle::direction::left_down).y);
        const auto gx = std::min(a.get_point(rectangle::direction::right_up).x, b.get_point(rectangle::direction::right_up).x);
        const auto gy = std::min(a.get_point(rectangle::direction::right_up).y, b.get_point(rectangle::direction::right_up).y);
        const auto len_x = gx - sx + 1;
        const auto len_y = gy - sy + 1;
        if (len_x > 0 && len_y > 0) {
            return geometry2d::rectangle(sx, sy, gx, gy);
        }
        return geometry2d::rectangle(0, 0, 0, 0);
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
