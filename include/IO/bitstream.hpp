#ifndef __ALG_IO_BITSTREAM_HPP__
#define __ALG_IO_BITSTREAM_HPP__

#include <cstdint>
#include <iostream>
#include <stdexcept>

namespace alg {

class InBitStream {
	uint8_t n_;  // number of bits remained in the buffer
	uint8_t buffer_;
	bool    init_;

 public:
	InBitStream() : n_(8), buffer_(0), init_(false) {}
	InBitStream(InBitStream const&) = delete;
	InBitStream&
	operator=(InBitStream const&) = delete;
	InBitStream(InBitStream&&)    = delete;
	InBitStream&
	operator=(InBitStream&&) = delete;

	bool
	read_bit() {
		if (!init_) {
			fill_buffer();
			init_ = true;
		}
		n_ -= 1;
		bool const bit = ((buffer_ >> n_) & 1) == 1;
		if (n_ == 0) { fill_buffer(); }
		return bit;
	}

	uint8_t
	read_char() {
		if (!init_) {
			fill_buffer();
			init_ = true;
		}

		// alligned
		if (n_ == 8) {
			uint8_t const c = buffer_;
			fill_buffer();
			return c;
		}
		// not alligned
		uint8_t const x     = (buffer_ << (8 - n_));
		uint8_t const old_n = n_;
		fill_buffer();
		n_ = old_n;
		return x | (buffer_ >> n_);
	}

	uint32_t
	read_int() {
		if (!init_) {
			fill_buffer();
			init_ = true;
		}

		uint32_t x = 0;
		for (uint8_t i = 0; i < 4; i++) {
			uint8_t const c = read_char();
			x <<= 8;
			x |= c;
		}
		return x;
	}

	uint32_t
	read_int(uint8_t const r) {
		if (r == 32) { return read_int(); }
		if (r > 32) {
			throw std::runtime_error("cannot read more than 32 bits into a integer");
		}
		uint32_t x = 0;
		for (uint8_t i = 0; i < r; i++) {
			x <<= 1;
			bool const bit = read_bit();
			if (bit) { x |= 1; }
		}
		return x;
	}

	uint64_t
	read_long() {
		if (!init_) {
			fill_buffer();
			init_ = true;
		}

		uint64_t x = 0;
		for (uint8_t i = 0; i < 8; i++) {
			uint8_t const c = read_char();
			x <<= 8;
			x |= c;
		}
		return x;
	}

	uint64_t
	read_long(uint8_t const r) {
		if (r == 64) { return read_long(); }
		if (r > 64) {
			throw std::runtime_error("cannot read more than 64 bits into a long");
		}
		uint64_t x = 0;
		for (uint8_t i = 0; i < r; i++) {
			x <<= 1;
			bool const bit = read_bit();
			if (bit) { x |= 1; }
		}
		return x;
	}

 private:
	void
	fill_buffer() {
		n_ = 8;
		std::cin.read((char*) &buffer_, sizeof(uint8_t));
	}
};

class OutBitStream {
	uint8_t n_;
	uint8_t buffer_;

 public:
	OutBitStream() : n_(0), buffer_(0) {}

	void
	write_bit(bool const bit) {
		buffer_ <<= 1;
		if (bit) { buffer_ |= 1; }
		n_ += 1;
		if (n_ == 8) { flush(); }
	}

	void
	write_char(uint8_t const c) {
		if (n_ == 0) {
			std::cout.write((char*) &c, sizeof(uint8_t));
			return;
		}
		for (uint8_t i = 0; i < 8; i++) {
			bool const bit = ((c >> (8 - i - 1)) & 1) == 1;
			write_bit(bit);
		}
	}

	void
	write_int(uint32_t const x) {
		for (uint8_t i = 0; i < 4; i++) {
			uint8_t const c = static_cast<uint8_t>(x >> (8 * (4 - i - 1)));
			write_char(c);
		}
	}

	void
	write_int(uint32_t const x, uint8_t const r) {
		if (r == 32) {
			write_int(x);
			return;
		}
		if (r > 32) {
			throw std::runtime_error("cannot write more than 32 bits of a integer");
		}
		for (uint8_t i = 0; i < r; i++) {
			bool const bit = ((x >> (r - i - 1)) & 1) == 1;
			write_bit(bit);
		}
	}

	void
	write_long(uint64_t const x) {
		for (uint8_t i = 0; i < 2; i++) {
			uint32_t const j = static_cast<uint32_t>(x >> (32 * (2 - i - 1)));
			write_int(j);
		}
	}

	void
	write_long(uint64_t const x, uint8_t const r) {
		if (r == 64) {
			write_int(x);
			return;
		}
		if (r > 64) {
			throw std::runtime_error("cannot write more than 64 bits of a long");
		}
		for (uint8_t i = 0; i < r; i++) {
			bool const bit = ((x >> (r - i - 1)) & 1) == 1;
			write_bit(bit);
		}
	}

	void
	flush() {
		if (n_ == 0) { return; }
		if (n_ > 0) { buffer_ <<= (8 - n_); }
		std::cout.write((char*) &buffer_, sizeof(uint8_t));
		n_      = 0;
		buffer_ = 0;
	}
};

static InBitStream  in_bitstream;
static OutBitStream out_bitstream;
};      // namespace alg
#endif  // !__ALG_IO_BITSTREAM_HPP__
