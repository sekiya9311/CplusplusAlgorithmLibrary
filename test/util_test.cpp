#include <bits/stdc++.h>

#include "../util/calc_multiple_integer_mod.cpp"
#include "../util/dir.cpp"
#include "../util/timer.cpp"
#include "../util/xor_shift.cpp"
#include "../util/bit_count.cpp"
#include "../util/day_of_month.cpp"
#include "../util/calc_bracket_pair_rank.cpp"
#include "../util/calc_bracket_rank.cpp"
#include "../util/inside.cpp"
#include "../util/mod_count_in_range.cpp"

void mod_count_in_range_test() {
  auto tmp = mod_count_in_range(0, 2, 3);
  for (auto e : tmp) {
    assert(e == 1);
  }
  tmp = mod_count_in_range(0, 3, 3);
  for (int i = 0; i < 3; i++) {
    if (i == 0) assert(tmp[i] == 2);
    else assert(tmp[i] == 1);
  }
}

void util_test() {
  mod_count_in_range_test();
}