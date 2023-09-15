#include <unistd.h>
#include <cstring>
#include "UdsMessage.h"

namespace common {
namespace proto {

UdsMessage::UdsMessage(const Message& message) : Message(message) {
    source_address_ = (payload_[0] << 8) | payload_[1];
    target_address_ = (payload_[2] << 8) | payload_[3];
    service_id_ = payload_[4];
    data_.assign(payload_.begin() + 5, payload_.end());
}

UdsMessage::UdsMessage(uint8_t protocol_version, uint16_t payload_type, uint8_t *payload) :
        Message(protocol_version, payload_type, payload) {
    source_address_ = (payload_[0] << 8) | payload_[1];
    target_address_ = (payload_[2] << 8) | payload_[3];
    service_id_ = payload_[4];
    data_.assign(payload_.begin() + 5, payload_.end());
}

UdsMessage::UdsMessage(uint8_t protocol_version, uint16_t payload_type, std::vector<uint8_t> payload) :
        Message(protocol_version, payload_type, payload) {
    source_address_ = (payload_[0] << 8) | payload_[1];
    target_address_ = (payload_[2] << 8) | payload_[3];
    service_id_ = payload_[4];
    data_.assign(payload_.begin() + 5, payload_.end());
}

UdsMessage::UdsMessage(uint8_t protocol_version, uint16_t payload_type, char* payload) :
        Message(protocol_version, payload_type, payload) {
    source_address_ = (payload_[0] << 8) | payload_[1];
    target_address_ = (payload_[2] << 8) | payload_[3];
    service_id_ = payload_[4];
    data_.assign(payload_.begin() + 5, payload_.end());
}

UdsMessage::UdsMessage(uint8_t protocol_version, uint16_t payload_type, const std::string& payload) :
        Message(protocol_version, payload_type, payload) {
    source_address_ = (payload_[0] << 8) | payload_[1];
    target_address_ = (payload_[2] << 8) | payload_[3];
    service_id_ = payload_[4];
    data_.assign(payload_.begin() + 5, payload_.end());
}

void UdsMessage::set_source_address(uint16_t source_address) {
    source_address_ = source_address;
    payload_[0] = (source_address_ >> 8) & 0xFF;
    payload_[1] = source_address_ & 0xFF;
}

void UdsMessage::set_target_address(uint16_t target_address) {
    target_address_ = target_address;
    payload_[2] = (target_address_ >> 8) & 0xFF;
    payload_[3] = target_address_ & 0xFF;
}

void UdsMessage::set_service_id(uint8_t service_id) {
    service_id_ = service_id;
    payload_[4] = service_id_;
}

void UdsMessage::clear_data() {
    data_.clear();
    payload_.erase(payload_.begin() + 5, payload_.end());
    payload_length_ = static_cast<uint32_t>(payload_.size());
}

void UdsMessage::append_data(uint8_t data) {
    data_.push_back(data);
    payload_.push_back(data);
    payload_length_ = static_cast<uint32_t>(payload_.size());
}

void UdsMessage::insert_data(std::vector<uint8_t> data) {
    data_.insert(data_.end(), data.begin(), data.end());
    payload_.insert(payload_.end(), data.begin(), data.end());
    payload_length_ = static_cast<uint32_t>(payload_.size());
}

uint16_t UdsMessage::get_source_address() const {
    return source_address_;
}

uint16_t UdsMessage::get_target_address() const {
    return target_address_;
}

uint8_t UdsMessage::get_service_id() const {
    return service_id_;
}

std::vector<uint8_t> UdsMessage::get_data() const {
    return data_;
}

void UdsMessage::switch_source_target() {
    uint16_t tmp = source_address_;
    source_address_ = target_address_;
    target_address_ = tmp;
    payload_[0] = (source_address_ >> 8) & 0xFF;
    payload_[1] = source_address_ & 0xFF;
    payload_[2] = (target_address_ >> 8) & 0xFF;
    payload_[3] = target_address_ & 0xFF;
}

void UdsMessage::send_reply(int socket_fd, const std::vector<uint8_t>& data) const {
    UdsMessage reply(*this);
    reply.set_service_id(service_id_ + 0x40);
    reply.switch_source_target();
    reply.clear_data();
    reply.insert_data(data);
    reply.send(socket_fd);
}

} // namespace proto
} // namespace common