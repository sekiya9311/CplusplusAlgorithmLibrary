// 範囲内のmodごとの数
// [l, r] 閉区間
std::vector<long long> mod_count_in_range(long long left, long long right, int mod) {
  const long long range = (right - left + 1);
  std::vector<long long> mod_count(mod, range / mod);
  if (range % mod > 0) {
    const int add_of_rest_left = left % mod;
    int add_of_rest_right;
    if (left % mod <= right % mod) {
      add_of_rest_right = right % mod;
    } else {
      add_of_rest_right = right % mod + mod;
    }
    for (int i = add_of_rest_left; i <= add_of_rest_right; i++) {
      mod_count[i % mod]++;
    }
  }
  return mod_count;
}
