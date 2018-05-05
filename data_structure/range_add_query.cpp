// 区間加算，区間参照
template<typename T = int>
class range_add_query {
private:
     std::vector<T> data, lazy;
     int sz;
     void push(int k, int l, int r) {
          if (this->lazy[k]) {
               this->data[k] += this->lazy[k] * (r - l);
               if (k * 2 + 2 < sz * 2 - 1) {
                    this->lazy[2 * k + 1] += this->lazy[k];
                    this->lazy[2 * k + 2] += this->lazy[k];
               }
               this->lazy[k] = 0;
          }
     }
     void add(int l, int r, int L, int R, int k, T val) {
           this->push(k, l, r);
          if (L <= l && r <= R) {
               this->lazy[k] += val;
                  this->push(k, l, r);
          } else if (R <= l || r <= L) {
               return;
          } else if (r - l > 1) {
               const int mid = (l + r) / 2;
               this->add(l, mid, L, R, k * 2 + 1, val);
               this->add(mid, r, L, R, k * 2 + 2, val);
                  data[k] = data[k * 2 + 1] + data[k * 2 + 2];
          }
     }
     T query(int l, int r, int L, int R, int k) {
          this->push(k, l, r);
          if (L <= l && r <= R) {
               return data[k];
          } else if (R <= l || r <= L) {
               return 0;
          } else {
               const int mid = (l + r) / 2;
               const T left = this->query(l, mid, L, R, k * 2 + 1);
               const T right = this->query(mid, r, L, R, k * 2 + 2);
               return left + right;
          }
     }
public:
     range_add_query(const int n) {
          this->sz = 1;
          while (this->sz < n) {
              this->sz <<= 1;
          }
          this->data.resize(this->sz * 2 - 1);
          this->lazy.resize(this->sz * 2 - 1);
     }
     void add(int l, int r, T val) {
          this->add(0, this->sz, l, r, 0, val);
     }
     T query(int l, int r) {
          return this->query(0, this->sz, l, r, 0);
     }
};
