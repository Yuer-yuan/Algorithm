#ifndef __ALG_SEARCH_SEPERATE_CHAINING_HPP__
#define __ALG_SEARCH_SEPERATE_CHAINING_HPP__

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
class SeperateChaining {
  struct Pair;
  struct List;
  using Pair = struct Pair;
  using OptPair = std::optional<Pair>;
  using OptVal = std::optional<Val>;
  using ST = std::vector<List>;
  using KeyHash = int (*)(Key const&);
  using KeyEq = bool (*)(Key const& t1, Key const& t2);
  using VecKey = std::vector<Key>;
  using VecPair = std::vector<Pair>;

  struct Pair {
    Key key_;
    Val val_;

    Pair(Key const& key, Val const& val) : key_{key}, val_{val} {}
  };

  struct List {
    std::list<Pair> l_;
    KeyEq ke_;

    List(KeyEq ke) : ke_{ke} {}

    int size() { return l_.size(); }

    VecKey keys() {
      VecKey vk;
      vk.reserve(size());
      for (auto it = l_.begin(); it != l_.end(); it++) {
        vk.push_back((*it).key_);
      }
      return vk;
    }

    OptVal get(Key const& key) {
      for (auto it = l_.begin(); it != l_.end(); it++) {
        if (ke_(key, (*it).key_)) {
          return (*it).val_;
        }
      }
      return std::nullopt;
    }

    // indicating whether pair is new
    bool put(Key const& key, Val const& val) {
      if (size() == 0) {
        l_.emplace_front(key, val);
        return true;
      }
      for (auto it = l_.begin(); it != l_.end(); it++) {
        if (ke_(key, (*it).key_)) {
          (*it).val_ = val;
          return false;
        }
      }
      l_.emplace_front(key, val);
      return true;
    }

    // indicating whethen pair is deleted
    bool del(Key const& key) {
      if (size() == 0) {
        return false;
      }
      for (auto it = l_.begin(); it != l_.end(); it++) {
        if (ke_(key, (*it).key_)) {
          l_.erase(it);
          return true;
        }
      }
      return false;
    }
  };

  // number of key-value pairs
  int n_;
  // hash table size
  int m_;
  // array of linked-list symbol tables
  ST st_;
  // hash-code function of key
  KeyHash kh_;
  // key equality
  KeyEq ke_;
  // initial capacity
  static constexpr int INIT_CAPACITY = 4;

 public:
  SeperateChaining(KeyHash kh,
                   int const m = INIT_CAPACITY,
                   KeyEq ke = Order<Key>::equal)
      : n_{0}, kh_{kh}, ke_{ke} {
    if (m < 0) {
      std::cerr << "Error initializing seperate-chaining symbol table: invalid "
                   "capacity which is negtive. init with default capacity\n";
      m_ = INIT_CAPACITY;
      return;
    } else {
      m_ = m;
      st_.resize(m_, List(ke));
    }
  }

  int size() { return n_; }

  bool contains(Key const& key) { return get(key).has_value(); }

  OptVal get(Key const& key) { return st_[hash(key)].get(key); }

  void put(Key const& key, Val const& val) {
    if (n_ >= 10 * m_) {
      resize(2 * m_);
    }
    if (st_[hash(key)].put(key, val)) {
      n_++;
    }
  }

  void del(Key const& key) {
    if (!st_[hash(key)].del(key)) {
      return;
    }
    n_--;
    if (m_ > INIT_CAPACITY && n_ <= 2 * m_) {
      resize(m_ / 2);
    }
  }

  VecKey keys() {
    VecKey vk;
    vk.reserve(n_);
    for (int i = 0; i < m_; i++) {
      VecKey tmp = st_[i].keys();
      vk.insert(vk.end(), tmp.begin(), tmp.end());
    }
    return vk;
  }

 private:
  void resize(int const new_m) {
    SeperateChaining new_seperate_chaining(kh_, new_m, ke_);
    for (auto list_it = st_.begin(); list_it != st_.end(); list_it++) {
      auto begin = (*list_it).l_.begin(), end = (*list_it).l_.end();
      for (auto pair_it = begin; pair_it != end; pair_it++) {
        new_seperate_chaining.put((*pair_it).key_, (*pair_it).val_);
      }
    }
    m_ = new_seperate_chaining.m_;
    n_ = new_seperate_chaining.n_;
    st_ = std::move(new_seperate_chaining.st_);
  }

  int hash(Key const key) const {
    int h = kh_(key);
    h ^= (h >> 20) ^ (h >> 12) ^ (h >> 7) ^ (h >> 4);
    return h & (m_ - 1);
  }
};
};  // namespace alg

#endif  // !__ALG_SEARCH_SEPERATE_CHAINING_HPP__
