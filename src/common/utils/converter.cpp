#include "converter.h"

namespace common {
namespace utils {

std::vector<uint8_t> to_bytes(uint32_t val, std::size_t length) {
    std::vector<uint8_t> bytes;
    for (std::size_t i = length - 1; i >= 0; i--) {
        bytes.push_back((val >> (i * 8)) & 0xFF);
    }
    return bytes;
}

} // namespace utils
} // namespace common