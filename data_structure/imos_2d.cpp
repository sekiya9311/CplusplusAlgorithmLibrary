template <typename T = int> class imos_2d {
private:
  int H, W;
  std::vector<std::vector<T>> data;

public:
  imos_2d(int _h, int _w)
      : H(_w), W(_w), data(_h + 1, std::vector<T>(_w + 1, 0)) {}

  void set(const std::pair<int, int> start_point,
           const std::pair<int, int> end_point) {
    data[start_point.first][start_point.second]++;
    data[start_point.first][end_point.second]--;
    data[end_point.first][start_point.second]--;
    data[end_point.first][end_point.second]++;
  }

  void calc() {
    for (int i = 0; i < H + 1; i++) {
      for (int j = 1; j < W + 1; j++) {
        data[i][j] += data[i][j - 1];
      }
    }
    for (int i = 1; i < H + 1; i++) {
      for (int j = 0; j < W + 1; j++) {
        data[i][j] += data[i - 1][j];
      }
    }
  }

  T get(const std::pair<int, int> p) { return data[p.first][p.second]; }
};
