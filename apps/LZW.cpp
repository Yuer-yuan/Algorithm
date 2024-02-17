#include "string/LZW.hpp"

#include <cstring>
#include <stdexcept>

int
main(int argc, char* argv[]) {
	if (argc != 2) { throw std::runtime_error("usage: huffman_test +/-"); }
	if (strcmp(argv[1], "-") == 0) { alg::LZW::compress(); }
	if (strcmp(argv[1], "+") == 0) { alg::LZW::expand(); }
	return 0;
}
