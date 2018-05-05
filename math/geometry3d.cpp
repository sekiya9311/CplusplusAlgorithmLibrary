// 3次元幾何

namespace geometry3d {
    const long double EPS = 1e-10;
    inline double add(double a, double b) {
        if (abs(a + b) < geometry3d::EPS * (abs(a) + abs(b))) return 0;
        return a + b;
    }
    inline int sgn(double a, double b = 0.0) {// sign function
        return a < b - EPS ? -1 : a > b + EPS ? 1 : 0;
    }

    struct Point {
        double x, y, z;
        Point() {}
        Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
        const geometry3d::Point operator+ (const geometry3d::Point &p) {
            return Point(geometry3d::add(this->x, p.x), geometry3d::add(this->y, p.y), geometry3d::add(this->z, p.z));
        }
        const geometry3d::Point operator- (const geometry3d::Point &p) {
            return Point(geometry3d::add(this->x, -p.x), geometry3d::add(this->y, -p.y), geometry3d::add(this->z, -p.z));
        }
        const geometry3d::Point operator* (double d) {
            return Point(this->x * d, this->y * d, this->z * d);
        }
        double norm() { //外積として求めたベクトルの絶対値の2乗
            return this->x * this->x + this->y * this->y + this->z * this->z;
        }
        double distance() {
            return sqrt(this->norm());
        }
    };

    double naiseki(const geometry3d::Point &p1, const geometry3d::Point &p2) {
        return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
    }
    geometry3d::Point gaiseki(const geometry3d::Point &p1, const geometry3d::Point &p2) {
        return geometry3d::Point(p1.y * p2.z - p2.y * p1.z, -(p1.x * p2.z - p2.x * p1.z), p1.x * p2.y - p2.x * p1.y);
    }

    struct Line {
        geometry3d::Point a, b, dis;
        Line() {}
        Line(const geometry3d::Point &_a, const geometry3d::Point &_b) : a(_a), b(_b), dis(b - a) {}
        double distSquare() {
            const double X = this->a.x - this->b.x;
            const double Y = this->a.y - this->b.y;
            const double Z = this->a.z - this->b.z;
            return X * X + Y * Y + Z * Z;
        }
        double distance() {
            return this->distSquare();
        }
    };
    using Segment = geometry3d::Line;

    double distanceLineToPoint(geometry3d::Line &l, geometry3d::Point &p) {
        return geometry3d::gaiseki(l.dis, p - l.a).distance() / l.dis.distance();
    }

    double distanceSegmentToPoint(geometry3d::Segment &l, geometry3d::Point &p) {
        if (geometry3d::naiseki(l.b - l.a, p - l.a) < 0) {
            auto buf = p - l.a;
            return buf.distance();
        }
        if (geometry3d::naiseki(l.a - l.b, p - l.b) < 0) {
            auto buf = p - l.b;
            return buf.distance();
        }
        return geometry3d::distanceLineToPoint(l, p);
    }

    struct Ball {
        geometry3d::Point center;
        double r;
        Ball() {}
        Ball(double _x, double _y, double _z, double _r) : center(_x, _y, _z), r(_r) {}
        Ball(const geometry3d::Point &_c, double _r) : center(_c), r(_r) {}
        bool inside(const geometry3d::Point &p) {
            const double X = p.x - this->center.x;
            const double Y = p.y - this->center.y;
            const double Z = p.z - this->center.z;
            return sgn(X * X + Y * Y + Z * Z, -(this->r * this->r)) == -1;
        }
        bool inside(geometry3d::Segment &s) {
            return geometry3d::sgn(geometry3d::distanceSegmentToPoint(s, this->center) - this->r) == -1;
        }
        bool on_seg(const geometry3d::Point &p) {
            const double X = p.x - this->center.x;
            const double Y = p.y - this->center.y;
            const double Z = p.z - this->center.z;
            return sgn(X * X + Y * Y + Z * Z, -(this->r * this->r)) == 0;
        }
        bool on_seg(geometry3d::Segment &s) {
            return geometry3d::sgn(geometry3d::distanceSegmentToPoint(s, this->center) - this->r) == 0;
        }
    };
};
