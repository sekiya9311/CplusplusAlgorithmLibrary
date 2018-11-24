#include<bits/stdc++.h>

#include "../math/euler_phi.cpp"
#include "../math/mod_calc.cpp"
#include "../math/pow_mod.cpp"
#include "../math/sieve_of_eratosthenes.cpp"
#include "../math/prime_factor_decomposition.cpp"
#include "../math/gcd_lcm.cpp"
#include "../math/geometry3d.cpp"
#include "../math/geometry2d.cpp"
#include "../math/is_prime.cpp"
#include "../math/matrix.cpp"
#include "../math/divisor.cpp"
#include "../math/miller_labin.cpp"

void point_test() {
    using namespace geometry2d;
    {
        // equals test
        point a(1, 1);
        point b(1, 1);
        assert(a == b);
        b = point(2, 2);
        assert(a != b);
    }
}

void rectangle_test() {
    using namespace geometry2d;
    rectangle rec(0, 0, 2, 3);
    assert(sgn(rec.square(), 6) == 0);
    assert(sgn(rec.square(), 2) != 0);
    
    assert(rec.get_point(rectangle::direction::left_down) == point(0, 0));
    assert(rec.get_point(rectangle::direction::left_up) == point(0, 3));
    assert(rec.get_point(rectangle::direction::right_down) == point(2, 0));
    assert(rec.get_point(rectangle::direction::right_up) == point(2, 3));

    rectangle rec2(1, 2, 3, 4);
    auto is_rect = intersect(rec, rec2);
    assert(is_rect == rectangle(1, 2, 2, 3));
    assert(is_rect != rectangle(1, 1, 1, 1));
}

void math_test() {
    point_test();
    rectangle_test();
}