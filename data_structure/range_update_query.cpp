// 区間変更，一点参照
// 一度もupdate無いidxを参照したらexception
template<typename T>
class range_update_query {
private:
     std::vector<T> data, lazy;
     std::vector<bool> valid, lazy_flag;
     const int sz;
     void push(int k) {
          if (this->lazy_flag[k]) {
               this->valid[k] = true;
               this->data[k] = this->lazy[k];
               if (k * 2 + 2 < sz * 2 - 1) {
                    this->lazy[k * 2 + 1] = this->lazy[k * 2 + 2] = this->lazy[k];
                    this->lazy_flag[k * 2 + 1] = this->lazy_flag[k * 2 + 2] = true;
               }
               this->lazy_flag[k] = false;
          }
     }
     void update(int l, int r, int L, int R, int k, T val) {
          this->push(k);
          if (L <= l && r <= R) {
               this->lazy[k] = val;
               this->lazy_flag[k] = true;
               this->push(k);
          } else if (r < L || R < l) {
               return;
          } else if (r - l > 1) {
               const int mid = (l + r) / 2;
               this->update(l, mid, L, R, k * 2 + 1, val);
               this->update(mid, r, L, R, k * 2 + 2, val);
          }
     }
     T query(int l, int r, int idx, int k) {
          this->push(k);
          if (r - l == 1) {
               if (!valid[k]) {
                    throw std::exception();
               }
               return this->data[k];
          } else if (l <= idx && idx <= r) {
               const int mid = (l + r) / 2;
               if (idx < mid) {
                    return this->query(l, mid, idx, k * 2 + 1);
               } else {
                    return this->query(mid, r, idx, k * 2 + 2);
               }
          }
     }
public:
     range_update_query(const int n) {
          this->sz = 1;
          while (this->sz < n) {
              this->sz <<= 1;
          }
          this->data.resize(this->sz * 2 - 1);
          this->lazy.resize(this->sz * 2 - 1);
          this->valid.resize(this->sz * 2 - 1, false);
          this->lazy_flag.resize(this->sz * 2 - 1, false);
     }
     void update(int l, int r, T val) {
          this->update(0, sz, l, r, 0, val);
     }
     T query(int idx) {
          return this->query(0, sz, idx, 0);
     }
};
