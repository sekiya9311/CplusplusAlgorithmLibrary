// xor_shift,ランダム
#include <random>
class xor_shift {
public:
    using result_type = uint32_t;

    static result_type min() {
        return std::numeric_limits<result_type>::min();
    }

    static result_type max() {
        return std::numeric_limits<result_type>::max();
    }

private:
    result_type x = 123456789;
    result_type y = 362436069;
    result_type z = 521288629;
    result_type w;
public:
    xor_shift(result_type seed = 0)
        : w(seed ? seed : 88675123) {this->random_loop();}
    void random_loop() {
        int loop_num = this->next() % 100;
        while (loop_num--) this->next();
    }
    result_type next(bool heavy_ok = false) {
        if (heavy_ok) this->random_loop();
        const auto t = this->x ^ (this->x << 11);
        this->x = this->y;
        this->y = this->z;
        this->z = this->w;
        return this->w = (this->w ^ (this->w >> 19))
                            ^ (t ^ (t >> 8));
    }
    uint64_t nextl(bool heavy_ok = false) {
        return ((((uint64_t)this->next(heavy_ok)) << 32)
                    | this->next(heavy_ok));
    }
    result_type operator()(bool heavy_ok = false) {
        return this->next(heavy_ok);
    }
};
std::random_device rnd;
std::mt19937 mt(rnd());
xor_shift xrnd(mt());
