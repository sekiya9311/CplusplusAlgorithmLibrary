// 区間変更，区間最小値
template<typename T = int,
typename ctype = std::less<T>,
T LIM = (std::is_same<ctype, std::less<T>>::value ?
std::numeric_limits<T>::max() : std::numeric_limits<T>::min())>
class range_update_query_minmax {
private:
     std::vector<T> data, lazy;
     std::vector<bool> valid, lazyFlag;
     ctype comp;
     const T initVal;
     int sz;
     void push(int k) {
          if (this->lazyFlag[k]) {
               this->valid[k] = true;
               this->data[k] = this->lazy[k];
               if ((k << 1) + 2 < (sz << 1) - 1) {
                    this->lazy[(k << 1) + 1] = this->lazy[(k << 1) + 2] = this->lazy[k];
                    this->lazyFlag[(k << 1) + 1] = this->lazyFlag[(k << 1) + 2] = true;
               }
               this->lazyFlag[k] = false;
          }
     }
     void update(int l, int r, int L, int R, int k, T val) {
          this->push(k);
          if (L <= l && r <= R) {
               this->lazy[k] = val;
               this->lazyFlag[k] = true;
               this->push(k);
          } else if (r < L || R < l) {
               return;
          } else if (r - l > 1) {
               const int mid = (l + r) >> 1;
               this->update(l, mid, L, R, (k << 1) + 1, val);
               this->update(mid, r, L, R, (k << 1) + 2, val);
               data[k] = std::min(data[(k << 1) + 1], data[(k << 1) + 2], comp);
          }
     }
     T query(int l, int r, int L, int R, int k) {
          this->push(k);
          if (L <= l && r <= R) {
               return this->data[k];
          } else if (r <= L || R <= l) {
               return this->initVal;
          } else {
               const int mid = (l + r) >> 1;
               T left = this->query(l, mid, L, R, (k << 1) + 1);
               T right = this->query(mid, r, L, R, (k << 1) + 2);
               return std::min(left, right, comp);
          }
     }
public:
     range_update_query_minmax(const int n, T initval = LIM) : initVal(initval) {
          this->sz = 1;
          while (this->sz < n) {
              this->sz <<= 1;
          }
          this->data.resize((this->sz << 1) - 1, this->initVal);
          this->lazy.resize((this->sz << 1) - 1);
          this->valid.resize((this->sz << 1) - 1, false);
          this->lazyFlag.resize((this->sz << 1) - 1, false);
     }
     void update(int l, int r, T val) {
          this->update(0, sz, l, r, 0, val);
     }
     T query(int l, int r) {
          return this->query(0, sz, l, r, 0);
     }
};
