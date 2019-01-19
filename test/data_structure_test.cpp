#include <bits/stdc++.h>

#include "../data_structure/binary_indexed_tree.cpp"
#include "../data_structure/rational_number.cpp"
#include "../data_structure/segment_tree.cpp"
#include "../data_structure/starry_sky_tree.cpp"
#include "../data_structure/cumulative_sum_2d.cpp"
#include "../data_structure/segment_tree_gcd.cpp"
#include "../data_structure/segment_tree_rmq.cpp"
#include "../data_structure/range_update_query.cpp"
#include "../data_structure/range_update_query_minmax.cpp"
#include "../data_structure/range_add_query.cpp"
#include "../data_structure/segment_tree_use_function_object.cpp"

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

void data_structure_test() {
  binary_indexed_tree_test();
}