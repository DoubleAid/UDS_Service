#include "address_controller.h"
#include <algorithm>

namespace server {
namespace service {

AddressController::AddressController(const common::utils::ControllerConfig& cfg) {}

bool AddressController::check_source_address(const uint16_t& source_address) const {
  return std::find(supported_source_addresses_.begin(), supported_source_addresses_.end(), source_address) !=
         supported_source_addresses_.end();
}

bool AddressController::check_target_address(const uint16_t& target_address) const {
  return check_local_address(target_address) || check_functional_address(target_address);
}

bool AddressController::check_local_address(const uint16_t& local_address) const {
  return std::find(supported_local_addresses_.begin(), supported_local_addresses_.end(), local_address) !=
         supported_local_addresses_.end();
}

bool AddressController::check_functional_address(const uint16_t& functional_address) const {
  return std::find(supported_functional_addresses_.begin(), supported_functional_addresses_.end(),
                   functional_address) != supported_functional_addresses_.end();
}

} // namespace service
} // namespace server