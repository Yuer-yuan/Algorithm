#ifndef __ALG_SEARCH_LLRB_HPP
#define __ALG_SEARCH_LLRB_HPP

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <optional>
#include <queue>
#include <sort/common.hpp>
#include <vector>

namespace alg {
template <typename Key, typename Val>
class LLRB {
  struct Node;
  using Node = struct Node;
  using Cmp = int (*)(Key const& t1, Key const& t2);
  using OptVal = std::optional<Val>;
  using OptKey = std::optional<Key>;
  using UniPtr = std::unique_ptr<Node>;
  using VecKey = std::vector<Key>;

  enum Color { Red, Black };
  struct Node {
    Key key_;
    Val val_;
    UniPtr left_, right_;
    int size_;
    Color col_;

    Node(Key const& key, Val const& val, Color col = Color::Black)
        : key_{key},
          val_{val},
          left_{nullptr},
          right_{nullptr},
          size_{1},
          col_{col} {};
  };

  UniPtr root_;
  Cmp cmp_;

 public:
  LLRB(Cmp cmp = Order<Key>::default_three_way_comparator)
      : root_{nullptr}, cmp_{cmp} {}

  // return the size of the tree
  int size() const { return size(root_.get()); }

  // return the size between the given range
  int size(Key const& lo, Key const& hi) const {
    if (cmp_(lo, hi) > 0) {
      std::cerr << "Error getting size between an abnormal range\n";
      return 0;
    }
    if (!get(hi).has_value()) {
      return rank(hi) - rank(lo);
    }
    return rank(hi) - rank(lo) + 1;
  };

  // put key-value pair into the tree
  void put(Key const& key, Val const& val) {
    root_ = put(std::move(root_), key, val);
    root_->col_ = Color::Black;

    /* assert(check()); */
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
  void del(Key const& key) {
    if (!contains(key)) {
      return;
    }
    if (!is_red(root_->left_.get()) && !is_red(root_->right_.get())) {
      root_->col_ = Color::Red;
    }
    root_ = del(std::move(root_), key);
    if (size() > 0) {
      root_->col_ = Color::Black;
    }

    /* assert(check()); */
  }

  // delete the min_key-value pair
  void del_min() {
    if (size() == 0) {
      std::cerr << "Error deleting minimum: red-black tree empty\n";
      return;
    }
    if (!is_red(root_->left_.get()) && !is_red(root_->right_.get())) {
      root_->col_ = Color::Red;
    }
    root_ = del_min(std::move(root_));
    if (size() > 0) {
      root_->col_ = Color::Black;
    }

    /* assert(check()); */
  }

  // delete the max_key-value pair
  void del_max() {
    if (size() == 0) {
      std::cerr << "Error deleting maximum: red-black tree empty\n";
      return;
    }
    if (!is_red(root_->left_.get()) && !is_red(root_->right_.get())) {
      root_->col_ = Color::Red;
    }
    root_ = del_max(std::move(root_));
    if (size() > 0) {
      root_->col_ = Color::Black;
    }

    /* assert(check()); */
  }

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
  int rank(Key const& key) const { return rank(root_.get(), key); };

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
  int height() const { return height(root_.get()); };

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
  void print(std::ostream& ostream) const {
    ostream << "binary search tree:\n";
    print_node(ostream, 0, root_.get(), Direction::Root);
  }

 private:
  inline int size(Node* x) const { return x == nullptr ? 0 : x->size_; }

  UniPtr put(UniPtr x, Key const& key, Val const& val) {
    if (x == nullptr) {
      return std::make_unique<Node>(key, val, Color::Red);
    }
    int c = cmp_(key, x->key_);
    if (c < 0) {
      x->left_ = put(std::move(x->left_), key, val);
    } else if (c > 0) {
      x->right_ = put(std::move(x->right_), key, val);
    } else {
      x->val_ = val;
    }

    return balance(std::move(x));
  }

  Node* get(Node* x, Key const& key) const {
    if (x == nullptr) {
      return nullptr;
    }
    int c = cmp_(key, x->key_);
    if (c < 0) {
      return get(x->left_.get(), key);
    }
    if (c > 0) {
      return get(x->right_.get(), key);
    }
    return x;
  }

  UniPtr del(UniPtr x, Key const& key) {
    if (cmp_(key, x->key_) < 0) {
      if (!is_red(x->left_.get()) && (x->left_ != nullptr) &&
          !is_red(x->left_->left_.get())) {
        x = move_red_left(std::move(x));
      }
      x->left_ = del(std::move(x->left_), key);
    } else {
      if (is_red(x->left_.get())) {
        x = rotate_right(std::move(x));
      }
      if ((cmp_(key, x->key_) == 0) && (x->right_ == nullptr)) {
        return nullptr;
      }
      if (!is_red(x->right_.get()) && (x->right_ != nullptr) &&
          !is_red(x->right_->left_.get())) {
        x = move_red_right(std::move(x));
      }
      if (cmp_(key, x->key_) == 0) {
        Node* h = min(x->right_.get());
        x->key_ = h->key_;
        x->val_ = h->val_;
        x->right_ = del_min(std::move(x->right_));
      } else {
        x->right_ = del(std::move(x->right_), key);
      }
    }
    return balance(std::move(x));
  }

  UniPtr del_min(UniPtr x) {
    // since left-leaning, no left means a single node
    if (x->left_ == nullptr) {
      return nullptr;
    }
    if (!is_red(x->left_.get()) && (x->left_ != nullptr) &&
        !is_red(x->left_->left_.get())) {
      x = move_red_left(std::move(x));
    }
    x->left_ = del_min(std::move(x->left_));
    return balance(std::move(x));
  }

  UniPtr del_max(UniPtr x) {
    if (is_red(x->left_.get())) {
      x = rotate_right(std::move(x));
    }
    // single element
    if (x->right_ == nullptr) {
      return nullptr;
    }
    if (!is_red(x->right_.get()) && (x->right_ != nullptr) &&
        !is_red(x->right_->left_.get())) {
      x = move_red_right(std::move(x));
    }
    x->right_ = del_max(std::move(x->right_));
    return balance(std::move(x));
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
    int c = cmp_(key, x->key_);
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
    int c = cmp_(key, x->key_);
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
    int left_size = size(x->left_.get());
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
    int c = cmp_(key, x->key_);
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
    return size(x->left_.get()) + 1 + rank(x->right_.get(), key);
  }

  void keys(Node* x, VecKey& vk, Key const& lo, Key const& hi) const {
    if (x == nullptr) {
      return;
    }
    int cl = cmp_(lo, x->key_);
    int ch = cmp_(hi, x->key_);
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

  int height(Node* x) const {
    if (x == nullptr) {
      return 0;
    }
    return 1 + std::max(height(x->left_.get(), x->right_.get()));
  }

  enum Direction { Root, Left, Right };

  void print_node(std::ostream& ostream,
                  int level,
                  Node* x,
                  Direction d) const {
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

  bool is_red(Node* x) const {
    if (x == nullptr) {
      return false;
    }
    return x->col_ == Color::Red;
  }

  UniPtr rotate_left(UniPtr x) {
    /* assert(("Error rotating left: null tree\n") && (x != nullptr)); */
    /* assert(("Error rotating left: left of root is not black\n") && */
    /*        (!is_red(x->left_.get()))); */
    /* assert(("Error rotating left: right of root is not red\n") && */
    /*        (is_red(x->right_.get()))); */

    UniPtr h = std::move(x->right_);
    h->col_ = x->col_;
    h->size_ = x->size_;
    x->col_ = Color::Red;
    x->right_ = std::move(h->left_);
    x->size_ = 1 + size(x->left_.get()) + size(x->right_.get());
    h->left_ = std::move(x);
    return h;
  }

  UniPtr rotate_right(UniPtr x) {
    /* assert(("Error rotating right: null tree\n") && (x != nullptr)); */
    /* assert(("Error rotating right: left of root is not red\n") && */
    /*        (is_red(x->left_.get()))); */
    /* assert(("Error rotating right: right of root is not black\n") && */
    /*        (!is_red(x->right_.get()))); */

    UniPtr h = std::move(x->left_);
    h->col_ = x->col_;
    h->size_ = x->size_;
    x->col_ = Color::Red;
    x->left_ = std::move(h->right_);
    x->size_ = 1 + size(x->left_.get()) + size(x->right_.get());
    h->right_ = std::move(x);
    return h;
  }

  inline Color flip_color(Color col) const {
    return col == Color::Black ? Color::Red : Color::Black;
  }

  void flip_colors(Node* x) {
    /* assert(("Error fliping colors: null tree\n") && (x != nullptr)); */
    /* assert(("Error fliping colors: left of root is not red\n") && */
    /*        (is_red(x->left_.get()))); */
    /* assert(("Error fliping colors: right of root is not red\n") && */
    /*        (is_red(x->right_.get()))); */

    x->col_ = flip_color(x->col_);
    x->left_->col_ = flip_color(x->left_->col_);
    x->right_->col_ = flip_color(x->right_->col_);
  }

  UniPtr balance(UniPtr x) {
    // fix up right leaning lines
    // its a finite state machine: left->right->flip
    if (is_red(x->right_.get()) && !is_red(x->left_.get())) {
      x = rotate_left(std::move(x));
    }
    if (is_red(x->left_.get()) && (x->left_ != nullptr) &&
        is_red(x->left_->left_.get())) {
      x = rotate_right(std::move(x));
    }
    if (is_red(x->left_.get()) && is_red(x->right_.get())) {
      flip_colors(x.get());
    }
    x->size_ = 1 + size(x->left_.get()) + size(x->right_.get());
    return x;
  }

  UniPtr move_red_left(UniPtr x) {
    flip_colors(x.get());
    if ((x->right_ != nullptr) && is_red(x->right_->left_.get())) {
      x->right_ = rotate_right(std::move(x->right_));
      x = rotate_left(std::move(x));
      flip_colors(x.get());
    }
    return x;
  }

  UniPtr move_red_right(UniPtr x) {
    flip_colors(x.get());
    if ((x->left_ != nullptr) && is_red(x->left_->left_.get())) {
      x = rotate_right(std::move(x));
      flip_colors(x.get());
    }
    return x;
  }

  bool check() {
    bool ok = true;
    if (!is_bst()) {
      ok = false;
      std::cout << "not in symmetric order\n";
    }
    if (!is_size_consistent()) {
      ok = false;
      std::cout << "subtree counts not consistent\n";
    }
    if (!is_rank_consistent()) {
      ok = false;
      std::cout << "ranks not consistent\n";
    }
    if (!is_two_three_tree()) {
      ok = false;
      std::cout << "not a 2-3 tree\n";
    }
    if (!is_balanced()) {
      ok = false;
      std::cout << "not balanced\n";
    }
    return ok;
  }

  bool is_bst() { return is_bst(root_.get(), std::nullopt, std::nullopt); }

  bool is_bst(Node* x, OptKey const min_key, OptKey const max_key) {
    if (x == nullptr) {
      return true;
    }
    if (min_key.has_value() && (cmp_(x->key_, min_key.value()) <= 0)) {
      return false;
    }
    if (max_key.has_value() && (cmp_(x->key_, max_key.value()) >= 0)) {
      return false;
    }
    return is_bst(x->left_.get(), min_key, x->key_) &&
           is_bst(x->right_.get(), x->key_, max_key);
  }

  bool is_size_consistent() { return true; }

  bool is_size_consistent(Node* x) {
    if (x == nullptr) {
      return true;
    }
    if (x->size_ != (1 + size(x->left_.get()) + size(x->right_.get()))) {
      return false;
    }
    return is_size_consistent(x->left_.get()) &&
           is_size_consistent(x->right_.get());
  }

  bool is_rank_consistent() {
    for (int i = 0; i < size(); i++) {
      if (i != rank(select(i).value())) {
        return false;
      }
    }
    for (Key const key : keys()) {
      if (cmp_(key, select(rank(key)).value()) != 0) {
        return false;
      }
    }
    return true;
  }

  bool is_two_three_tree() { return is_two_three_tree(root_.get()); }

  bool is_two_three_tree(Node* x) {
    if (x == nullptr) {
      return true;
    }
    if (is_red(x->right_.get())) {
      return false;
    }
    if (is_red(x->left_.get()) && is_red(x->right_.get())) {
      return false;
    }
    return is_two_three_tree(x->left_.get()) &&
           is_two_three_tree(x->right_.get());
  }

  bool is_balanced() {
    int black = 0;
    Node* x = root_.get();
    while (x != nullptr) {
      if (!is_red(x)) {
        black++;
      }
      x = x->left_.get();
    }
    return is_balanced(root_.get(), black);
  }

  bool is_balanced(Node* x, int black) {
    if (x == nullptr) {
      return black == 0;
    }
    if (!is_red(x)) {
      black--;
    }
    return is_balanced(x->left_.get(), black) &&
           is_balanced(x->right_.get(), black);
  }
};
};      // namespace alg
#endif  // !__ALG_SEARCH_LLRB_HPP
