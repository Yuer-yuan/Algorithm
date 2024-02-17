#ifndef __ALG_STRING_LZW_HPP__
#define __ALG_STRING_LZW_HPP__

#include <array>
#include <cstdint>
#include <iostream>
#include <string>

#include "IO/bitstream.hpp"
#include "search/trie.hpp"

namespace alg {

class LZW {
	static constexpr uint32_t R = 256;
	static constexpr uint32_t W = 12;
	static constexpr uint32_t L = 4096;  // 2 ^ W

 public:
	LZW();

	static void
	compress() {
		auto const s  = read_str();
		auto       st = Trie<uint32_t>();

		// init with single-char
		for (uint32_t i = 0; i < R; i++) {
			st.put(single_char_str(static_cast<char>(i)), i);
		}

		uint64_t code = R + 1;  // R is reserved for EOF
		uint64_t i    = 0;
		while (i < s.size()) {
			auto const lp      = st.lp(s.substr(i));
			auto const lp_code = st.get(lp).value();
			out_bitstream.write_int(lp_code, W);
			if (lp.size() + i < s.size() && code < L) {
				auto const key = s.substr(i, lp.size() + 1);
				st.put(key, code);
				code += 1;
			}
			i += lp.size();
		};
		out_bitstream.write_int(R, W);
		out_bitstream.flush();
	};

	static void
	expand() {
		std::array<std::string, L> st;
		for (uint32_t i = 0; i < R; i++) {
			st[i] = single_char_str(static_cast<char>(i));
		}

		auto codeword = in_bitstream.read_int(W);
		if (codeword == R) { return; }
		auto val = st[codeword];
		auto i   = R + 1;
		while (true) {
			write_str(val);
			codeword = in_bitstream.read_int(W);
			if (codeword == R) { break; }
			auto s = st[codeword];
			if (i == codeword) { s = val + val[0]; }  // special case
			if (i < L) {
				st[i] = val + s[0];
				i += 1;
			}
			val = s;
		}
	};

 private:
	static std::string
	read_str() {
		std::string s("");
		char        c;
		while (std::cin.read(&c, sizeof(char))) { s.push_back(c); }
		return s;
	}

	static void
	write_str(std::string const& str) {
		for (auto const c : str) { std::cout.write(&c, sizeof(char)); }
	}

	static std::string
	single_char_str(char const c) {
		std::string s;
		s.push_back(c);
		return s;
	}
};
};  // namespace alg

#endif  // !__ALG_STRING_LZW_HPP__
