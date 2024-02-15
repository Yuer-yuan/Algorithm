#ifndef __ALG_SEARCH_BST_HPP__
#define __ALG_SEARCH_BST_HPP__

#include <cstddef>
#include <iostream>
#include <memory>
#include <optional>
#include <ostream>
#include <queue>
#include <stdexcept>
#include <vector>

#include <sort/common.hpp>

namespace alg {
template <typename Key,
          typename Val,
          int (*cmp)(Key const& t1, Key const& t2) =
              Order<Key>::default_three_way_comparator>
class BST {
  struct Node;
  using Node = struct Node;
  using VecKey = std::vector<Key>;
  using UniPtr = std::unique_ptr<Node>;
  using OptVal = std::optional<Val>;
  using OptKey = std::optional<Key>;

  // helper class
  struct Node {
    Key key_;
    Val val_;
    UniPtr left_, right_;
    size_t size_;

    Node(Key const& key, Val const& val)
        : key_{key}, val_{val}, left_{nullptr}, right_{nullptr}, size_{1} {}
  };

  UniPtr root_;

 public:
  // constructors
  BST() : root_{nullptr} {}

  // return the size of the tree
  size_t size() const { return size(root_.get()); }

  // return the size between the given range
  size_t size(Key const& lo, Key const& hi) const {
    if (cmp(lo, hi) > 0) {
      throw std::runtime_error(
          "Error getting size between an abnormal range\n");
    }
    if (!get(hi).has_value()) {
      return rank(hi) - rank(lo);
    }
    return rank(hi) - rank(lo) + 1;
  };

  // put key-value pair into the tree
  void put(Key const& key, Val const& val) {
    root_ = put(std::move(root_), key, val);
  }

  // return the value mapped by the key
  OptVal get(Key const& key) const {
    Node* x = get(root_.get(), key);
    if (x != nullptr) {
      // `val` inside is `copy` constructed
      return x->val_;
    }
    return std::nullopt;
  }

  // check if tree constains key
  bool contains(Key const& key) const {
    return get(root_.get(), key) != nullptr;
  }

  // delete the key and its value
  void del(Key const& key) { root_ = del(std::move(root_), key); }

  // delete the min_key-value pair
  void del_min() { root_ = del_min(std::move(root_)); }

  // delete the min_key-value pair
  void del_max() { root_ = del_max(std::move(root_)); }

  // get the min key
  OptKey min() const {
    Node* x = min(root_.get());
    if (x != nullptr) {
      return x->key_;
    }
    return std::nullopt;
  }

  // get the max key
  OptKey max() const {
    Node* x = max(root_.get());
    if (x != nullptr) {
      return x->key_;
    }
    return std::nullopt;
  }

  // return the largest `key` less than or equal to the `given key`
  // `key` <= `given`
  OptKey floor(Key const& key) const {
    Node* x = floor(root_.get(), key);
    return x == nullptr ? nullptr : x->key_;
  }

  // return the smallest key greater than or equal to the key
  // `key` >= `given`
  OptKey ceiling(Key const& key) const {
    Node* x = ceiling(root_.get(), key);
    return x == nullptr ? nullptr : x->key_;
  };

  // return the key of rank.
  OptKey select(int const rank) const {
    if (rank < 0 || rank > size()) {
      return std::nullopt;
    }
    Node* x = select(root_.get(), rank);
    // x should not be null
    if (x == nullptr) {
      return std::nullopt;
    }
    return x->key_;
  };

  // return the number of keys strictly smaller than given
  size_t rank(Key const& key) const { return rank(root_.get(), key); };

  // get all keys
  VecKey keys() const {
    VecKey foo;
    if (root_ == nullptr) {
      return foo;
    }
    return keys(min().value(), max().value());
  }

  // keys between `lo` and `hi`
  VecKey keys(Key const& lo, Key const& hi) const {
    VecKey vk;
    if (root_ != nullptr) {
      keys(root_.get(), vk, lo, hi);
    }
    return vk;
  }

  // return the height of the tree
  size_t height() const { return height(root_.get()); };

  // return the keys in level order
  // breath first search
  VecKey keys_level_order() const {
    VecKey vk;
    if (root_ == nullptr) {
      return vk;
    }
    std::queue<Node*> qnode;
    qnode.push(root_);
    while (!qnode.empty()) {
      Node* x = qnode.pop();
      vk.push_back(x->key_);
      if (x->left_ != nullptr) {
        qnode.push(x->left_.get());
      }
      if (x->right_ != nullptr) {
        qnode.push(x->right_.get());
      }
    }
  };

  // print in a level form
  std::ostream& operator<<(std::ostream& ostream) const {
    ostream << "binary search tree:\n";
    print_node(ostream, 0, root_.get(), Direction::Root);
    return ostream;
  }

 private:
  size_t size(Node* x) const { return x == nullptr ? 0 : x->size_; }

  UniPtr put(UniPtr x, Key const& key, Val const& val) {
    if (x == nullptr) {
      return std::make_unique<Node>(key, val);
    }
    int const c = cmp(key, x->key_);
    // less, put to `left_`
    if (c < 0) {
      x->left_ = put(std::move(x->left_), key, val);
      x->size_++;
    }
    // greater, put to `right`
    else if (c > 0) {
      x->right_ = put(std::move(x->right_), key, val);
      x->size_++;
    }
    // equal, update `val_`
    else {
      x->val_ = val;
    }
    return x;
  }

  Node* get(Node* x, Key const& key) const {
    if (x == nullptr) {
      return nullptr;
    }
    int const c = cmp(key, x->key_);
    if (c < 0) {
      return get(x->left_.get(), key);
    }
    if (c > 0) {
      return get(x->right_.get(), key);
    }
    return x;
  }

  UniPtr del(UniPtr x, Key const& key) {
    if (x == nullptr) {
      return nullptr;
    }
    int const c = cmp(key, x->key_);
    if (c < 0) {
      x->left_ = del(std::move(x->left_), key);
    } else if (c > 0) {
      x->right_ = del(std::move(x->right_), key);
    } else {
      if (x->left_ == nullptr) {
        return std::move(x->right_);
      }
      if (x->right_ == nullptr) {
        return std::move(x->left_);
      }
      // replace with successor
      Node* min_node = min(x->right_.get());
      UniPtr new_x = std::make_unique<Node>(min_node->key_, min_node->val_);
      new_x->left_ = std::move(x->left_);
      new_x->right_ = std::move(del_min(std::move(x->right_)));
      x = std::move(new_x);
    }
    x->size_ = size(x->left_.get()) + size(x->right_.get()) + 1;
    return x;
  }

  UniPtr del_min(UniPtr x) {
    if (x == nullptr) {
      return nullptr;
    }
    if (x->left_ == nullptr) {
      return std::move(x->right_);
    }
    x->left_ = del_min(std::move(x->left_));
    x->size_ = 1 + size(x->left_.get()) + size(x->right_.get());
    return x;
  }

  UniPtr del_max(UniPtr x) {
    if (x == nullptr) {
      return nullptr;
    }
    if (x->right_ == nullptr) {
      return std::move(x->left_);
    }
    x->right_ = del_max(std::move(x->right_));
    x->size_ = 1 + size(x->left_.get()) + size(x->right_.get());
    return x;
  }

  Node* min(Node* x) const {
    if (x == nullptr) {
      return nullptr;
    }
    if (x->left_ == nullptr) {
      return x;
    }
    return min(x->left_.get());
  }

  Node* max(Node* x) const {
    if (x == nullptr) {
      return nullptr;
    }
    if (x->right_ == nullptr) {
      return x;
    }
    return max(x->right_.get());
  }

  Node* floor(Node* x, Key const& key) const {
    if (x == nullptr) {
      return nullptr;
    }
    int const c = cmp(key, x->key_);
    if (c == 0) {
      // equal
      return x;
    }
    if (c < 0) {
      // `key` is less than current node
      // must be on the left
      return floor(x->left_.get(), key);
    }
    // `key` is greater than current node
    // "could" be on the right
    Node* y = floor(x->right_.get(), key);
    // no greater node than current on the right
    if (y == nullptr) {
      return x;
    }
    // some node satisfies
    return y;
  }

  Node* ceiling(Node* x, Key const& key) const {
    if (x == nullptr) {
      return nullptr;
    }
    int const c = cmp(key, x->key_);
    if (c == 0) {
      return x;
    }
    if (c > 0) {
      return ceiling(x->right_.get(), key);
    }
    Node* y = ceiling(x->left_.get(), key);
    if (y == nullptr) {
      return x;
    }
    return y;
  }

  Node* select(Node* x, int const rank) const {
    if (x == nullptr) {
      return nullptr;
    }
    int const left_size = size(x->left_.get());
    if (rank < left_size) {
      return select(x->left_.get(), rank);
    }
    if (rank == left_size) {
      return x;
    }
    // rank > left_size
    return select(x->right_.get(), rank - left_size - 1);
  }

  int rank(Node* x, Key const& key) const {
    if (x == nullptr) {
      return 0;
    }
    int const c = cmp(key, x->key_);
    if (c < 0) {
      // `key` is smaller than current
      // find on the left
      return rank(x->left_.get(), key);
    }
    if (c == 0) {
      // `key` equals current
      // all left elements count
      return size(x->left_.get());
    }
    // `key` is bigger than current
    // all left and current count, then add those on the right
    return size(x->left_.get()) + 1 + rank(x->right_.get());
  }

  void keys(Node* x, VecKey& vk, Key const& lo, Key const& hi) const {
    if (x == nullptr) {
      return;
    }
    int const cl = cmp(lo, x->key_), ch = cmp(hi, x->key_);
    if (cl < 0) {
      keys(x->left_.get(), vk, lo, hi);
    }
    if (cl <= 0 && ch >= 0) {
      vk.push_back(x->key_);
    }
    if (ch > 0) {
      keys(x->right_.get(), vk, lo, hi);
    }
  }

  size_t height(Node* x) const {
    if (x == nullptr) {
      return 0;
    }
    return 1 + std::max(height(x->left_.get(), x->right_.get()));
  }

  enum Direction { Root, Left, Right };

  void print_node(std::ostream& ostream,
                  size_t const level,
                  Node* const x,
                  Direction d) const {
    if (x == nullptr) {
      ostream << "empty\n";
      return;
    }
    for (size_t i = 0; i < level; i++) {
      ostream << ' ';
    }
    ostream << "-level " << level << ", size " << x->size_ << ", (" << x->key_
            << "->" << x->val_ << ") ";
    switch (d) {
      case Direction::Root:
        ostream << "root";
        break;
      case Direction::Left:
        ostream << "left";
        break;
      case Direction::Right:
        ostream << "right";
        break;
    }
    ostream << '\n';
    if (x->left_ != nullptr) {
      print_node(ostream, level + 1, x->left_.get(), Direction::Left);
    }
    if (x->right_ != nullptr) {
      print_node(ostream, level + 1, x->right_.get(), Direction::Right);
    }
  };

};  // class BST
}  // namespace alg
#endif  // !__ALG_SEARCH_BST_HPP
