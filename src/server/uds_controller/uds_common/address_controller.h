#pragma once

#include <iostream>
#include <vector>
#include "src/common/utils/cfg_loader/cfg_loader.h"

namespace server {
namespace service {

class AddressController {
public:
AddressController() = default;

AddressController(const common::utils::ControllerConfig& cfg);

bool check_source_address(const uint16_t& source_address) const;

bool check_target_address(const uint16_t& target_address) const;

bool check_local_address(const uint16_t& local_address) const;

bool check_functional_address(const uint16_t& functional_address) const;

private:
std::vector<uint16_t> supported_source_addresses_;
std::vector<uint16_t> supported_local_addresses_;
std::vector<uint16_t> supported_functional_addresses_;
};

} // namespace service
} // namespace server