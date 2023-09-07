#include <algorithm>
#include "security_controller.h"

namespace server {
namespace service {

SecurityController::SecurityController() :
        current_security_level_(SecurityLevel::SECURITY_NONE),
        supported_security_levels_({SecurityLevel::SECURITY_NONE}) {}

SecurityController::SecurityController(const SecurityLevel& security_level,
                                       const std::vector<SecurityLevel>& supported_security_levels) :
        current_security_level_(security_level),
        supported_security_levels_(supported_security_levels) {}

SecurityController::SecurityController(const common::utils::Config& cfg) {
    if (cfg.find("Supported_Security_Level") != cfg.end()) {
        std::string val = cfg["Supported_Security_Level"];
        std::vector<int> local_address_tmp = common::utils::string_to_vector<int>(val);
        for (auto& address : local_address_tmp) {
            supported_security_levels_.push_back(static_cast<SecurityLevel>(address));
        }
        current_security_level_ = supported_security_levels_[0];
    }
}

SecurityLevel SecurityController::get_security_level() const {
    return current_security_level_;
}

bool SecurityController::set_current_security_level(const SecurityLevel& security_level) {
    if (std::find(supported_security_levels_.begin(), supported_security_levels_.end(), security_level) !=
        supported_security_levels_.end()) {
        current_security_level_ = security_level;
        return true;
    }
    return false;
}

std::vector<SecurityLevel> SecurityController::get_supported_security_levels() const {
    return supported_security_levels_;
}

bool SecurityController::set_supported_security_levels(const std::vector<SecurityLevel>& supported_security_levels) {
    supported_security_levels_ = supported_security_levels;
    return true;
}

bool SecurityController::is_supported_security_level(const SecurityLevel& security_level) const {
    return std::find(supported_security_levels_.begin(), supported_security_levels_.end(), security_level) !=
           supported_security_levels_.end();
}

} // namespace service
} // namespace server