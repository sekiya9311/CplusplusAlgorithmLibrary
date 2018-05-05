// xor_shift,ランダム
#include <random>
class xor_shift {
private:
    uint32_t x = 123456789;
    uint32_t y = 362436069;
    uint32_t z = 521288629;
    uint32_t w;
public:
    xor_shift(uint32_t seed = 0)
        : w(seed ? seed : 88675123) {this->random_loop();}
    void random_loop() {
        int loop_num = this->next() % 100;
        while (loop_num--) this->next();
    }
    uint32_t next(bool heavy_ok = false) {
        if (heavy_ok) this->random_loop();
        uint32_t t = this->x ^ (this->x << 11);
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
    uint32_t operator()(bool heavy_ok = false) {
        return this->next(heavy_ok);
    }
};
std::random_device rnd;
std::mt19937 mt(rnd());
xor_shift xrnd(mt());
