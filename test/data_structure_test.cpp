#include <bits/stdc++.h>

#include "../data_structure/binary_indexed_tree.cpp"
#include "../data_structure/binary_indexed_tree_2d.cpp"
#include "../data_structure/binary_indexed_tree_2d_by_mod.cpp"
#include "../data_structure/binary_indexed_tree_by_mod.cpp"
#include "../data_structure/cumulative_sum_2d.cpp"
#include "../data_structure/imos_2d.cpp"
#include "../data_structure/range_add_query.cpp"
#include "../data_structure/range_update_query.cpp"
#include "../data_structure/range_update_query_minmax.cpp"
#include "../data_structure/rational_number.cpp"
#include "../data_structure/segment_tree.cpp"
#include "../data_structure/segment_tree_gcd.cpp"
#include "../data_structure/segment_tree_rmq.cpp"
#include "../data_structure/segment_tree_use_function_object.cpp"
#include "../data_structure/starry_sky_tree.cpp"

void binary_indexed_tree_test() {
  const int L = 5;
  binary_indexed_tree<int> bit(L);
  for (int i = 0; i < L; i++) {
    bit.add(i, i + 1);
  }
  // idx: [ 0, 1, 2, 3, 4 ]
  // val: [ 1, 2, 3, 4, 5 ]
  assert(bit.sum(0) == 0); // [0, 0)
  assert(bit.sum(1, 4) == (4 * 5) / 2 - 1); // [1, 4)
  assert(bit.sum(0, L) == (L * (L + 1)) / 2); // [0, L)
  assert(bit.sum(L) == bit.sum(0, L));
}

void binary_indexed_tree_by_mod_test() {
    const int MOD = 5;
    const int L = 5;
    binary_indexed_tree_by_mod<MOD> bit(L);
    for (int i = 0; i < L; i++) {
        bit.add(i, i + 1);
    }

    // idx: [ 0, 1, 2, 3, 4 ]
    // val: [ 1, 2, 3, 4, 5 ]
    assert(bit.sum(0) == 0); // [0, 0)
    assert(bit.sum(1, 4) == ((4 * 5) / 2 - 1) % MOD); // [1, 4)
    assert(bit.sum(0, L) == ((L * (L + 1)) / 2) % MOD); // [0, L)
    assert(bit.sum(L) == bit.sum(0, L));
}

void binary_indexed_tree_2d_test() {
    const int L = 5;
    binary_indexed_tree_2d<> bit(L, L);
    for (int i = 0; i < L; i++) {
        bit.add(i, i, i + 1);
    }

    // 1, 0, 0, 0, 0
    // 0, 2, 0, 0, 0
    // 0, 0, 3, 0, 0
    // 0, 0, 0, 4, 0
    // 0, 0, 0, 0, 5

    for (int i = 0; i < L; i++) {
        assert(bit.sum(i, i, i, i) == 0);
        for (int j = i; j < L; j++) {
            const int ans = ((j + 1) * (j + 2) / 2 - (i + 0) * (i + 1) / 2);
            assert(bit.sum(i, i, j + 1, j + 1) == ans);
        }
    }
}

void binary_indexed_tree_2d_by_mod_test() {
    const int MOD = 5;
    const int L = 5;
    binary_indexed_tree_2d_by_mod<MOD> bit(L, L);
    for (int i = 0; i < L; i++) {
        bit.add(i, i, i + 1);
    }

    // 1, 0, 0, 0, 0
    // 0, 2, 0, 0, 0
    // 0, 0, 3, 0, 0
    // 0, 0, 0, 4, 0
    // 0, 0, 0, 0, 5

    for (int i = 0; i < L; i++) {
        assert(bit.sum(i, i, i, i) == 0);
        for (int j = i; j < L; j++) {
            const int ans = ((j + 1) * (j + 2) / 2 - (i + 0) * (i + 1) / 2) % MOD;
            assert(bit.sum(i, i, j + 1, j + 1) == ans);
        }
    }
}

void imos_2d_test() {
  imos_2d<> data(5, 5);
  // 1 1 1 1 0
  // 1 2 2 2 1
  // 1 2 3 3 1
  // 1 1 2 2 0
  // 0 0 1 1 0
  data.set({0, 0}, {4, 4});
  data.set({1, 1}, {3, 5});
  data.set({2, 2}, {5, 4});
  data.calc();

  assert(data.get({0, 0}) == 1);
  assert(data.get({0, 1}) == 1);
  assert(data.get({0, 2}) == 1);
  assert(data.get({0, 3}) == 1);
  assert(data.get({0, 4}) == 0);
  assert(data.get({1, 0}) == 1);
  assert(data.get({1, 1}) == 2);
  assert(data.get({1, 2}) == 2);
  assert(data.get({1, 3}) == 2);
  assert(data.get({1, 4}) == 1);
  assert(data.get({2, 0}) == 1);
  assert(data.get({2, 1}) == 2);
  assert(data.get({2, 2}) == 3);
  assert(data.get({2, 3}) == 3);
  assert(data.get({2, 4}) == 1);
  assert(data.get({3, 0}) == 1);
  assert(data.get({3, 1}) == 1);
  assert(data.get({3, 2}) == 2);
  assert(data.get({3, 3}) == 2);
  assert(data.get({3, 4}) == 0);
  assert(data.get({4, 0}) == 0);
  assert(data.get({4, 1}) == 0);
  assert(data.get({4, 2}) == 1);
  assert(data.get({4, 3}) == 1);
  assert(data.get({4, 4}) == 0);
}

void data_structure_test() {
  binary_indexed_tree_test();
  binary_indexed_tree_by_mod_test();
  binary_indexed_tree_2d_test();
  binary_indexed_tree_2d_by_mod_test();
  imos_2d_test();
}
