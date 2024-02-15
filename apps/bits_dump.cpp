#include <array>
#include <cstdint>
#include <cxxopts.hpp>
#include <format>
#include <iostream>
#include <map>
#include <optional>

enum Base : uint8_t {
  BINARY = 0,
  OCTAL,
  DECIMAL,
  HEXIMAL,
};

void dump(Base const base, uint8_t const nbytes) {
  uint8_t bytes_cnt = 0;
  uint8_t c;
  while (std::cin.read((char*)&c, sizeof(uint8_t))) {
    if (bytes_cnt && bytes_cnt % nbytes == 0) {
      std::cout << '\n';
    }
    // format integrals
    // https://www.modernescpp.com/index.php/std-format-in-c-20/
    switch (base) {
      case Base::BINARY: {
        std::cout << std::format("{:08b} ", c);
        break;
      }
      case Base::OCTAL: {
        std::cout << std::format("{:04o} ", c);
        break;
      }
      case Base::DECIMAL: {
        std::cout << std::format("{:03d} ", c);
        break;
      }
      case Base::HEXIMAL: {
        std::cout << std::format("{:02x} ", c);
        break;
      }
    }

    bytes_cnt += 1;
  }
  std::cout << std::format("\n{:d} bytes\n", bytes_cnt);
}

int main(int argc, char* argv[]) {
  cxxopts::Options options("bits dump",
                           "dump bits in binary, octal, decimal, heximal");
  options.add_options()(
      "b,binary", "dump as binary",
      cxxopts::value<bool>()->default_value("false")->implicit_value("true"))(
      "o,octal", "dump as octal",
      cxxopts::value<bool>()->default_value("false")->implicit_value("true"))(
      "d,decimal", "dump as decimal",
      cxxopts::value<bool>()->default_value("false")->implicit_value("true"))(
      "h,heximal", "dump as heximal",
      cxxopts::value<bool>()->default_value("false")->implicit_value("true"))(
      "n,nbytes", "number of bytes to show a line",
      cxxopts::value<uint8_t>()->default_value("16"));

  auto const result = options.parse(argc, argv);

  std::array<std::string, 4> base{"binary", "octal", "decimal", "heximal"};
  auto check_unique = [&]() -> std::optional<std::string> {
    uint8_t cnt = 0;
    std::string r{"heximal"};
    for (auto const& b : base) {
      if (result.count(b)) {
        cnt += 1;
        r = b;
      }
    }
    if (cnt == 0 || cnt == 1) {
      return r;
    }
    return std::nullopt;
  };

  std::map<std::string, Base> base_map{
      {"binary", BINARY},
      {"octal", OCTAL},
      {"decimal", DECIMAL},
      {"heximal", HEXIMAL},
  };
  auto const opt_b = check_unique();
  if (!opt_b.has_value()) {
    throw cxxopts::exceptions::parsing("Only a single base is needed");
  }

  auto const nbytes = result["nbytes"].as<uint8_t>();

  dump(base_map.at(opt_b.value()), nbytes);
  return 0;
}
