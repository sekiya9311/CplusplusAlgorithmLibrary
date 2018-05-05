// 有理数,分数
struct rational_number {
private:
    int64_t _numerator, _denominator;
public:
    static int64_t gcd(const int64_t a, const int64_t b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    rational_number()
        : _numerator(0LL), _denominator(1LL) {}
    rational_number(const int64_t val)
        : rational_number(val, 1LL) {}
    rational_number(const int64_t nume, const int64_t deno) {
        const auto gcdVal = gcd(std::abs(nume), std::abs(deno));
        _numerator = nume / gcdVal;
        _denominator = deno / gcdVal;
    }
    rational_number(const std::string val) {
        std::vector<int> slashIdx;
        const int L = val.length();
        for (int i = 0; i < L; i++) {
            if (val[i] == '/') {
                slashIdx.emplace_back(i);
            }
        }
        switch ((int) slashIdx.size()) {
            case 0: {
                _numerator = std::stoll(val);
                _denominator = 1LL;
                break;
            }
            case 1: {
                _numerator = std::stoll(val.substr(0, slashIdx[0]));
                _denominator = std::stoll(val.substr(slashIdx[0] + 1));
                const auto gcdVal = gcd(std::abs(_numerator), std::abs(_denominator));
                _numerator /= gcdVal;
                _denominator /= gcdVal;
                break;
            }
            default: {
                throw std::invalid_argument("Not rational format.");
                break;
            }
        }
    }
    rational_number(const rational_number &inst) {
        _numerator = inst.numerator();
        _denominator = inst.denominator();
    }
    inline const double fraction() const {
        return 1. * _numerator / _denominator;
    }
    inline const int64_t numerator() const {
        return _numerator;
    }
    inline const int64_t denominator() const {
        return _denominator;
    }
    inline const rational_number abs() const {
        return rational_number(std::abs(_numerator), std::abs(_denominator));
    }

    // operators
    rational_number operator+() const {
        return rational_number(_numerator, _denominator);
    }
    rational_number operator-() const {
        return rational_number(-_numerator, _denominator);
    }
    explicit operator double() const noexcept {
        return fraction();
    }
    rational_number& operator+=(const rational_number &other) {
        const auto denoGcd = gcd(_denominator, other.denominator());
        const auto deno = _denominator / denoGcd * other.denominator();
        const auto leftNume = _numerator * (other.denominator() / denoGcd);
        const auto rightNume = other.numerator() * (_denominator / denoGcd);
        _numerator = leftNume + rightNume;
        _denominator = deno;
        const auto gcdVal = gcd(_numerator, _denominator);
        _numerator /= gcdVal;
        _denominator /= gcdVal;
        return *this;
    }
    rational_number& operator-=(const rational_number &other) {
        *this += (-other);
        return *this;
    }
    rational_number& operator*=(const rational_number &other) {
        const auto lnrdGcd = rational_number::gcd(std::abs(_numerator), std::abs(other.denominator()));
        const auto ldrnGcd = rational_number::gcd(std::abs(_denominator), std::abs(other.numerator()));
        _numerator = (_numerator / lnrdGcd) * (other.numerator() / ldrnGcd);
        _denominator = (_denominator / ldrnGcd) * (other.denominator() / lnrdGcd);
        return *this;
    }
    rational_number& operator/=(const rational_number &other) {
        *this *= rational_number(other.denominator(), other.numerator());
        return *this;
    }
};
rational_number operator+(const rational_number &l,
                         const rational_number &r) {
    const auto denoGcd = rational_number::gcd(l.denominator(), r.denominator());
    const auto deno = l.denominator() / denoGcd * r.denominator();
    const auto leftNume = l.numerator() * (r.denominator() / denoGcd);
    const auto rightNume = r.numerator() * (l.denominator() / denoGcd);
    return rational_number(leftNume + rightNume, deno);
}
rational_number operator-(const rational_number &l,
                         const rational_number &r) {
    return l + (-r);
}
rational_number operator*(const rational_number &l,
                         const rational_number &r) {
    const auto lnrdGcd = rational_number::gcd(std::abs(l.numerator()), std::abs(r.denominator()));
    const auto ldrnGcd = rational_number::gcd(std::abs(l.denominator()), std::abs(r.numerator()));
    return rational_number((l.numerator() / lnrdGcd) * (r.numerator() / ldrnGcd),
                          (l.denominator() / ldrnGcd) * (r.denominator() / lnrdGcd));
}
rational_number operator/(const rational_number &l,
                         const rational_number &r) {
    return l * rational_number(r.denominator(), r.numerator());
}
bool operator<(const rational_number &l,
               const rational_number &r) {
    const auto sub = r - l;
    bool ret = sub.denominator() > 0 && sub.numerator() > 0;
    ret |= sub.denominator() < 0 && sub.numerator() < 0;
    return ret;
}
bool operator>(const rational_number &l,
               const rational_number &r) {
    return r < l;
}
bool operator<=(const rational_number &l,
               const rational_number &r) {
    return !(l > r);
}
bool operator>=(const rational_number &l,
               const rational_number &r) {
    return !(l < r);
}
bool operator==(const rational_number &l,
                const rational_number &r) {
    return !(l < r) && !(l > r);
}
bool operator!=(const rational_number &l,
                const rational_number &r) {
    return !(l == r);
}
