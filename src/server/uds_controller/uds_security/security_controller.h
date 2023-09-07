#pragma once

#include <vector>
#include <cstdint>
#include <unordered_map>
#include "src/common/utils/cfg_loader/cfg_loader.h"

namespace server {
namespace service {

enum SecurityLevel {
    SECURITY_NONE       = 0x00,
    SECURITY_BASIC      = 0x01,
    SECURITY_HIGH       = 0x02,
    SECURITY_SVA        = 0x03,
    SECURITY_FLASH      = 0x04,
    SECURITY_SUPPLIER   = 0x05,
    SECURITY_SUPPLIER_7 = 0x07,
    SECURITY_SUPPLIER_9 = 0x09,
    SECURITY_SUPPLIER_11= 0x0B,
    SECURITY_INVALID    = 0xFF,
};

class SecurityController {
public:
    SecurityController();

    SecurityController(const SecurityLevel& security_level,
                       const std::vector<SecurityLevel>& supported_security_levels);

    SecurityController(const common::utils::Config& cfg);

    ~SecurityController() = default;

    SecurityLevel get_security_level() const;

    bool set_current_security_level(const SecurityLevel& security_level);

    std::vector<SecurityLevel> get_supported_security_levels() const;

    bool set_supported_security_levels(const std::vector<SecurityLevel>& supported_security_levels);

    bool is_supported_security_level(const SecurityLevel& security_level) const;

private:
    SecurityLevel current_security_level_;
    std::vector<SecurityLevel> supported_security_levels_;
    std::unordered_map<uint32_t, std::vector<SecurityLevel>> security_limitation_map_;
};

} // namespace service
} // namespace server