#ifndef __ALG_SEARCH_TRIE_HPP__
#define __ALG_SEARCH_TRIE_HPP__

#include <cstdint>
#include <memory>
#include <optional>
#include <stdexcept>

namespace alg {

template<typename Val>
class Trie {
	class Node;
	using ShrPtr = std::shared_ptr<Node>;
	using OptVal = std::optional<Val>;

	uint64_t n_;  // size of tree
	ShrPtr   root_;

 public:
	Trie() : n_(0), root_(nullptr) {}

	// size of tree
	uint64_t
	size() const {
		return n_;
	}

	// get value associated with given string
	OptVal
	get(std::string const& s) const {
		if (s.size() == 0 || root_ == nullptr) { return std::nullopt; }
		uint64_t i = 0;
		Node*    x = root_.get();
		while (x != nullptr) {
			uint8_t const sc = static_cast<uint8_t>(s[i]), nc = x->c_;
			if (sc < nc) {
				x = x->left_.get();
			} else if (sc > nc) {
				x = x->right_.get();
			} else {
				i += 1;
				if (i == s.size()) { return x->v_; }
				x = x->mid_.get();
			}
		}
		return std::nullopt;
	}

	// put key-value pair into tree
	void
	put(std::string const& s, Val const& v) {
		if (s.size() == 0) {
			throw std::runtime_error("Cannot bind a empty string key to a value");
		}
		n_ += 1;
		if (root_ == nullptr) {
			root_ = std::make_shared<Node>(static_cast<uint8_t>(s[0]), std::nullopt);
		}
		Node*  x = root_.get();
		size_t i = 0;
		while (true) {
			uint8_t const sc = static_cast<uint8_t>(s[i]), nc = x->c_;
			if (sc < nc) {
				if (x->left_ == nullptr) {
					x->left_ = std::make_shared<Node>(sc, std::nullopt);
				}
				x = x->left_.get();
			} else if (sc > nc) {
				if (x->right_ == nullptr) {
					x->right_ = std::make_shared<Node>(sc, std::nullopt);
				}
				x = x->right_.get();
			} else {
				i += 1;
				if (i == s.size()) {
					x->v_ = v;
					return;
				}
				if (x->mid_ == nullptr) {
					x->mid_ =
					    std::make_shared<Node>(static_cast<uint8_t>(s[i]), std::nullopt);
				}
				x = x->mid_.get();
			}
		}
	}

	// longest prefix
	std::string
	lp(std::string const& s) const {
		if (s.size() == 0 || root_ == nullptr) { return ""; }
		Node*    x      = root_.get();
		uint64_t i      = 0;
		uint64_t length = 0;
		while (x != nullptr && i < s.size()) {
			uint8_t const sc = static_cast<uint8_t>(s[i]), nc = x->c_;
			if (sc < nc) {
				x = x->left_.get();
			} else if (sc > nc) {
				x = x->right_.get();
			} else {
				i += 1;
				if (x->v_.has_value()) { length = i; }
				x = x->mid_.get();
			}
		}
		return s.substr(0, length);
	}

 private:
	class Node {
	 public:
		uint8_t c_;  // character
		OptVal  v_;  // value associated with string
		    // subtrees, left and right are actually siblings, mid is actually child
		ShrPtr left_, mid_, right_;

		Node(uint8_t const c,
		     OptVal const  v,
		     ShrPtr const  left  = nullptr,
		     ShrPtr const  mid   = nullptr,
		     ShrPtr const  right = nullptr)
		    : c_(c), v_(v), left_(left), mid_(mid), right_(right) {}
	};
};
};      // namespace alg
#endif  // !__ALG_SEARCH_TRIE_HPP__
