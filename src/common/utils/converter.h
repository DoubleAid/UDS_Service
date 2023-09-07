#include <vector>
#include <cstdint>

namespace common {
namespace utils {

std::vector<uint8_t> to_bytes(uint32_t val, size_t length);

} // namespace utils
} // namespace common