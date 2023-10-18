#ifndef __ALG_SEARCH_LINEAR_PROBING_HPP__
#define __ALG_SEARCH_LINEAR_PROBING_HPP__

#include <array>
#include <iostream>
#include <list>
#include <optional>
#include <queue>
#include <sort/common.hpp>
#include <tuple>
#include <vector>

namespace alg {
template <typename Key, typename Val>
class LinearProbing {
  using OptKey = std::optional<Key>;
  using OptVal = std::optional<Val>;
  using VecKey = std::vector<Key>;
  using VecOptKey = std::vector<OptKey>;
  using VecOptVal = std::vector<OptVal>;
  using KeyHash = int (*)(Key const&);
  using KeyEq = bool (*)(Key const& t1, Key const& t2);

  // number of key-value pairs
  int n_;
  // hash table size
  int m_;
  // keys (possibly null)
  VecOptKey keys_;
  // vals (possibly null)
  VecOptVal vals_;
  // hash-code function of key
  KeyHash kh_;
  // key equality
  KeyEq ke_;
  // initial capacity
  constexpr static int INIT_CAPACITY = 4;

 public:
  LinearProbing(KeyHash kh,
                int const m = INIT_CAPACITY,
                KeyEq ke = Order<Key>::equal)
      : n_{0}, kh_{kh}, ke_{ke} {
    if (m < 0) {
      std::cerr << "Error initializing linear-probing symbol table: invalid "
                   "capacity which is negtive. init with default capacity\n";
      m_ = INIT_CAPACITY;
      return;
    } else {
      m_ = m;
      keys_.resize(m_);
      vals_.resize(m_);
    }
  }

  int size() { return n_; }

  bool contains(Key const& key) { return get(key).has_value(); }

  OptVal get(Key const& key) {
    for (int i = hash(key); keys_[i].has_value(); i = r_add(i)) {
      if (ke_(key, keys_[i].value())) {
        return vals_[i].value();
      }
    }
    return std::nullopt;
  }

  void put(Key const& key, Val const& val) {
    if (n_ >= m_ / 2) {
      resize(2 * m_);
    }
    int i = hash(key);
    for (; keys_[i].has_value(); i = r_add(i)) {
      if (ke_(key, keys_[i].value())) {
        *vals_[i] = val;
        return;
      }
    }
    keys_[i] = key;
    vals_[i] = val;
    n_++;
  }

  void del(Key const& key) {
    int i = hash(key);
    for (; keys_[i].has_value() && !ke_(key, keys_[i].value()); i = r_add(i))
      ;
    if (!keys_[i].has_value()) {
      std::cout << "Cannot delete key-value pair: given key not exist\n";
      return;
    }
    keys_[i].reset();
    vals_[i].reset();
    n_--;

    // refresh successive keys
    for (i = r_add(i); keys_[i].has_value(); i = r_add(i)) {
      Key const key_tmp = keys_[i].value();
      Val const val_tmp = vals_[i].value();
      keys_[i].reset();
      vals_[i].reset();
      n_--;
      put(key_tmp, val_tmp);
    }

    if (n_ > 0 && n_ <= m_ / 8) {
      resize(m_ / 2);
    }
  }

  VecKey keys() {
    VecKey vk;
    vk.reserve(n_);
    for (int i = 0; i < m_; i++) {
      if (keys_[i].has_value()) {
        vk.push_back(keys_[i].value());
      }
    }
    return vk;
  }

 private:
  void resize(int const new_m) {
    LinearProbing new_linear_probing(kh_, new_m, ke_);
    for (int i = 0; i < m_; i++) {
      if (keys_[i].has_value()) {
        new_linear_probing.put(keys_[i].value(), vals_[i].value());
      }
    }
    m_ = new_linear_probing.m_;
    keys_ = std::move(new_linear_probing.keys_);
    vals_ = std::move(new_linear_probing.vals_);
  }

  int hash(Key const key) const {
    int h = kh_(key);
    h ^= (h >> 20) ^ (h >> 12) ^ (h >> 7) ^ (h >> 4);
    return h & (m_ - 1);
  }

  inline int r_add(int const i) { return (i + 1) % m_; }
};
};  // namespace alg

#endif  // !__ALG_SEARCH_LINEAR_PROBING_HPP__
