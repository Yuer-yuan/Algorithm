#ifndef __ALG_BST_HPP__
#define __ALG_BST_HPP__

#include <algorithm>
#include <array>
#include <cassert>
#include <compare>
#include <iostream>
#include <memory>
#include <optional>
#include <ostream>
#include <vector>

namespace alg {
template <typename Key, typename Value>
class BST {
 protected:
  // helper class
  class Node {
   public:
    Key key_;
    Value val_;
    std::unique_ptr<Node> left_, right_;
    int size_;

    Node(Key const& key, Value const& val)
        : key_{key}, val_{val}, left_{nullptr}, right_{nullptr}, size_{1} {}
  };

  // point to the root of the tree
  std::unique_ptr<Node> root_;

  int size(Node* x) const {
    if (x == nullptr)
      return 0;
    return x->size_;
  }

  void put(Node* x, Key const& key, Value const& val) {
    if (x == nullptr) {
      if (root_ == nullptr) {
        root_ = std::make_unique<Node>(key, val);
      }
      return;
    }
    if (key < x->key_) {
      if (x->left_ == nullptr) {
        x->left_ = std::make_unique<Node>(key, val);
      } else {
        put(x->left_.get(), key, val);
      }
      x->size_++;
    } else if (key > x->key_) {
      if (x->right_ == nullptr) {
        x->right_ = std::make_unique<Node>(key, val);
      } else {
        put(x->right_.get(), key, val);
      }
      x->size_++;
    } else {
      x->val_ = val;
    }
  }

  Node* get(Node* x, Key const& key) const {
    if (x == nullptr) {
      return nullptr;
    }
    if (key < x->key_) {
      return get(x->left_.get(), key);
    }
    if (key > x->key_) {
      return get(x->right_.get(), key);
    }
    return x;
  }

  std::unique_ptr<Node> del(std::unique_ptr<Node> x, Key const& key) {
    if (x == nullptr) {
      return nullptr;
    }
    if (key < x->key_) {
      x->left_ = del(std::move(x->left_), key);
    } else if (key > x->key_) {
      x->right_ = del(std::move(x->right_), key);
    } else {
      if (x->left_ == nullptr) {
        return std::move(x->right_);
      }
      if (x->right_ == nullptr) {
        return std::move(x->left_);
      }
      auto min_node = min(x->right_.get());
      auto new_x = std::make_unique<Node>(min_node->key_, min_node->val_);
      new_x->left_ = std::move(x->left_);
      new_x->right_ = std::move(del_min(std::move(x->right_)));
      x = std::move(new_x);
    }
    x->size_ = size(x->left_.get()) + size(x->right_.get()) + 1;
    return x;
  }

  std::unique_ptr<Node> del_min(std::unique_ptr<Node> x) {
    if (x == nullptr) {
      return nullptr;
    }
    if (x->left_ == nullptr) {
      return std::move(x->right_);
    }
    Node *t = x.get(), *t1 = t->left_.get();
    for (; --t->size_ && t1->left_ != nullptr; t = t1, t1 = t->left_.get())
      ;
    t->left_ = std::move(t1->right_);
    return x;
  }

  std::unique_ptr<Node> del_max(std::unique_ptr<Node> x) {
    if (x == nullptr) {
      return nullptr;
    }
    if (x->right_ == nullptr) {
      return std::move(x->left_);
    }
    Node *t = x.get(), *t1 = t->right_.get();
    for (; --t->size_ && t1->right_ != nullptr; t = t1, t1 = t->right_.get())
      ;
    t->right_ = std::move(t1->left_);
    return x;
  }

  Node* min(Node* x) const {
    if (x == nullptr)
      return nullptr;
    for (; x->left_ != nullptr; x = x->left_.get())
      ;
    return x;
  }

  Node* max(Node* x) const {
    if (x == nullptr)
      return nullptr;
    for (; x->right_ != nullptr; x = x->right_.get())
      ;
    return x;
  }

  void keys(Node* x,
            std::vector<Key>& vec,
            Key const& lo,
            Key const& hi) const {
    if (x == nullptr || x->key_ < lo || x->key_ > hi)
      return;
    keys(x->left_.get(), vec, lo, hi);
    vec.push_back(x->key_);
    keys(x->right_.get(), vec, lo, hi);
  }

  enum direction { root, left, right };

  void print_node(std::ostream& ostream,
                  int level,
                  Node* x,
                  direction d) const {
    if (x == nullptr) {
      ostream << "empty\n";
      return;
    }
    for (int i = 0; i < level; i++) {
      ostream << ' ';
    }
    ostream << "-level " << level << ", size " << x->size_ << ", (" << x->key_
            << "->" << x->val_ << ") ";
    switch (d) {
      case direction::root:
        ostream << "root";
        break;
      case direction::left:
        ostream << "left";
        break;
      case direction::right:
        ostream << "right";
        break;
    }
    ostream << '\n';
    if (x->left_ != nullptr) {
      print_node(ostream, level + 1, x->left_.get(), direction::left);
    }
    if (x->right_ != nullptr) {
      print_node(ostream, level + 1, x->right_.get(), direction::right);
    }
  };

 public:
  // constructors
  BST() : root_{nullptr} {}

  // put key-value pair into the tree
  void put(Key const& key, Value& val) { put(root_.get(), key, val); }

  // return the value mapped by the key
  std::optional<Value> get(Key const& key) const {
    Node* x = get(root_.get(), key);
    if (x != nullptr) {
      return {x->val_};
    }
    return {};
  }

  // check if tree constains key
  bool contains(Key const& key) const {
    return get(root_.get(), key) != nullptr;
  }

  // delete the key and its value
  void del(Key const& key) { root_ = std::move(del(std::move(root_), key)); }

  // delete the min_key-value pair
  void del_min() { root_ = std::move(del_min(std::move(root_))); }

  // delete the min_key-value pair
  void del_max() { root_ = std::move(del_max(std::move(root_))); }

  // return the size of the tree
  int size() const { return size(root_.get()); }

  // return the size between the given range
  // TODO
  int size(Key const& lo, Key const& hi) const = delete;

  // get the value mapped by min key
  std::optional<Value> min() const {
    Node* x = min(root_.get());
    if (x != nullptr) {
      return {x->key_};
    }
    return {};
  }

  // get the value mapped by max key
  std::optional<Value> max() const {
    Node* x = max(root_.get());
    if (x != nullptr) {
      return {x->key_};
    }
    return {};
  }

  // return the largest key less than or equal to the key
  // TODO
  std::optional<Key> floor(Key const& key) const = delete;

  // return the smallest key greater than or equal to the key
  // TODO
  std::optional<Key> ceiling(Key const& key) const = delete;

  // return the key of rank.
  // TODO
  std::optional<Key> select(int rank) const = delete;

  // return the number that strictly smaller than the key
  // TODO
  int rank(Key const& key) const = delete;

  // all keys
  void keys(std::vector<Key>& vec) const {
    vec.clear();
    keys(root_.get(), vec, *min(), *max());
  }

  // keys between `lo` and `hi`
  void keys(std::vector<Key>& vec, Key const& lo, Key const& hi) const {
    vec.clear();
    keys(root_.get(), vec, lo, hi);
  }

  // return the height of the tree (from `1`)
  // TODO
  int height() const = delete;

  // return the keys in level order
  // TODO
  void keys_level_order(std::vector<Key>& vec) const = delete;

  // print in a level form
  void print(std::ostream& ostream) const {
    ostream << "binary search tree:\n";
    print_node(ostream, 0, root_.get(), direction::root);
  }
};  // class BST
}  // namespace alg
#endif  // !__ALG_BST_HPP
