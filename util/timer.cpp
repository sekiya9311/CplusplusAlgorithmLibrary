// タイマー,時間計測
// basis msec
// 1[sec] == 1000[msec]
#include <chrono>
class timer {
private:
    std::chrono::system_clock::time_point start;
    const long long LIMIT;
    bool is_start = false;
public:
    timer() : LIMIT(-1) {}
    timer(long long limit) : LIMIT(limit) {}

    void start_measure() {
        this->start = std::chrono::system_clock::now();
        this->is_start = true;
    }

    long long get_elapse_msec() const {
        if (!this->is_start) {
            throw std::runtime_error("Not start measure");
        }
        auto pass = std::chrono::system_clock::now() - this->start;
        return std::chrono::duration_cast<std::chrono::milliseconds>(pass).count();
    }

    long long get_remaining_msec() const {
        if (this->LIMIT == -1) {
            throw std::runtime_error("Not defined LIMIT");
        }
        return LIMIT - this->get_elapse_msec();
    }
};
timer timer(6000);
