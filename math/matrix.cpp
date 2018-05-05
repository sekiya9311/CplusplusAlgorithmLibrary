// 行列,行列積,行列累乗

using row = std::vector<long long>;
using matrix = std::vector<row>;
//(A * B) mod
matrix matrix_mul(matrix &A, matrix &B, const int mod) {
    const int asz = A.size();
    const int bsz = B.size();
    const int bcolsz = B.front().size();
    matrix res(asz, row(bcolsz, 0));
    for (int i = 0; i < asz; i++) {
        for (int k = 0; k < bsz; k++) {
            for (int j = 0; j < bcolsz; j++) {
                (res[i][j] += A[i][k] * B[k][j]) %= mod;
            }
        }
    }
    return res;
}
//(mat^p) mod
matrix mat_pow_mod(matrix mat, long long p, const int mod) {
    const int matsz = mat.size();
    assert((int) mat.front().size() == matsz);//must square matrix!!
    matrix res(matsz, row(matsz, 0));
    for (int i = 0; i < matsz; i++) {
        res[i][i] = 1;
    }
    while (p) {
        if (p & 1) res = matrix_mul(res, mat, mod);
        mat = matrix_mul(mat, mat, mod);
        p >>= 1;
    }
    return res;
}
// ( matrix * vector ) % mod
row mul(matrix mat, row r, const int mod) {
  assert(mat[0].size() == r.size());
  row res(mat.size(), 0);
  for (int i = 0; i < (int) mat.size(); i++) {
    for (int j = 0; j < (int) r.size(); j++) {
      (res[i] += mat[i][j] * r[j]) %= mod;
    }
  }
  return res;
}
matrix make_matrix(int r, int c) {
    return matrix(r, row(c));
}
