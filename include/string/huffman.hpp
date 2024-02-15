#ifndef __ALG_STRING_HUFFMAN_HPP
#define __ALG_STRING_HUFFMAN_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include "IO/bitstream.hpp"
#include "sort/common.hpp"
#include "sort/heap.hpp"

namespace alg {

class Huffman {
  static constexpr uint64_t R = 256;
  class Node;
  using UniPtr = std::unique_ptr<Node>;
  using ShrPtr = std::shared_ptr<Node>;

  class Node {
   public:
    uint8_t c_;
    uint64_t freq_;
    ShrPtr left_, right_;

    Node(uint8_t const& c, uint64_t const& freq, ShrPtr left, ShrPtr right)
        : c_(c), freq_(freq), left_(left), right_(right) {}

    bool is_leaf() const { return left_ == nullptr && right_ == nullptr; }

    friend bool operator<(Node const& lhs, Node const& rhs) {
      return lhs.freq_ <= rhs.freq_;
    }
  };

 public:
  static void compress() {
    // read string from stdin
    std::vector<uint8_t> s;
    uint8_t c;
    while (std::cin.read((char*)&c, sizeof(uint8_t))) {
      s.push_back(c);
    }

    // count frequency
    uint64_t const n = s.size();
    std::array<uint64_t, R> freq_tb;
    for (uint64_t i = 0; i < n; i++) {
      freq_tb[s[i]] += 1;
    }

    // build trie
    auto const root = build_trie(freq_tb);

    // build look-up table
    auto const st = build_code(root.get());

    // print trie for decoder
    write_trie(root.get());

    // print uncompressed message length
    out_bitstream.write_long(n);

    // encode the message
    for (auto const& c : s) {
      for (auto const& b : st[c]) {
        out_bitstream.write_bit(b);
      }
    }
    out_bitstream.flush();
  }

  static void expand() {
    auto const root = read_trie();
    uint64_t const n = in_bitstream.read_long();
    for (uint64_t i = 0; i < n; i++) {
      Node* x = root.get();
      while (!x->is_leaf()) {
        bool const bit = in_bitstream.read_bit();
        if (bit) {
          x = x->right_.get();
        } else {
          x = x->left_.get();
        }
      }
      out_bitstream.write_char(x->c_);
    }
    out_bitstream.flush();
  }

 private:
  /*
   * build trie from `freq_table` and return a root node
   */
  static ShrPtr build_trie(std::array<uint64_t, R> const& freq_table) {
    alg::PriorityQueue<Node, Order<Node>::less> pq;
    for (uint64_t c = 0; c < R; c++) {
      size_t const freq = freq_table[c];
      if (freq > 0) {
        pq.push(Node((uint8_t)c, freq, nullptr, nullptr));
      }
    }
    auto n2p = [](Node const& x) {
      return std::make_shared<Node>(x.c_, x.freq_, x.left_, x.right_);
    };
    while (pq.size() > 1) {
      auto x = pq.pop();
      auto y = pq.pop();
      pq.push(Node((uint8_t)0, x.freq_ + y.freq_, n2p(x), n2p(y)));
    }
    auto root = pq.pop();
    return n2p(root);
  }

  /*
   * traversing the trie in preorder
   */
  static void write_trie(Node* x) {
    // leaf node, write `1` and character
    if (x->is_leaf()) {
      out_bitstream.write_bit(1);
      out_bitstream.write_char(x->c_);
      ;
      return;
    }
    // internal node, write `0`
    out_bitstream.write_bit(0);
    write_trie(x->left_.get());
    write_trie(x->right_.get());
  }

  /*
   * read a `bool` to determine the type of the node
   */
  static ShrPtr read_trie() {
    bool const flag = in_bitstream.read_bit();
    // leaf node
    if (flag) {
      uint8_t const c = in_bitstream.read_char();
      return std::make_shared<Node>(c, 0, nullptr, nullptr);
    }
    // internal node
    auto const left = read_trie();
    auto const right = read_trie();
    return std::make_shared<Node>(0, 0, left, right);
  }

  /*
   * build look-up table for each char
   */
  static std::array<std::vector<bool>, R> build_code(Node* root) {
    std::array<std::vector<bool>, R> st;
    build_code(st, root, {});
    return st;
  }

  static void build_code(std::array<std::vector<bool>, R>& st,
                         Node* x,
                         std::vector<bool> const& s) {
    if (x->is_leaf()) {
      st[x->c_] = s;
      return;
    }
    build_code(st, x->left_.get(), append<bool>(s, 0));
    build_code(st, x->right_.get(), append<bool>(s, 1));
  }

  template <typename T>
  static std::vector<T> append(std::vector<T> const& v, T const& e) {
    std::vector<T> v1(v);
    v1.push_back(e);
    return v1;
  }
};
};      // namespace alg
#endif  // !__ALG_STRING_HUFFMAN_HPP
