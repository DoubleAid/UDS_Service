#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <unistd.h>
#include "Messages.h"
#include "src/common/utils/converter.h"

namespace common {
namespace proto {

Message::Message(uint8_t protocol_version, uint16_t payload_type, uint8_t *payload) :
        protocol_version_(protocol_version),
        payload_type_(payload_type) {
    inverse_protocol_version_ = protocol_version_ ^ 0xFF;
    set_payload(payload);
}

Message::Message(uint8_t protocol_version, uint16_t payload_type, std::vector<uint8_t> payload) :
        protocol_version_(protocol_version),
        payload_type_(payload_type) {
    inverse_protocol_version_ = protocol_version_ ^ 0xFF;
    set_payload(payload);
}

Message::Message(uint8_t protocol_version, uint16_t payload_type, char* payload) :
        protocol_version_(protocol_version),
        payload_type_(payload_type) {
    inverse_protocol_version_ = protocol_version_ ^ 0xFF;
    set_payload(reinterpret_cast<uint8_t*>(payload));
}

Message::Message(uint8_t protocol_version, uint16_t payload_type, const std::string& payload) :
        protocol_version_(protocol_version),
        payload_type_(payload_type) {
    inverse_protocol_version_ = protocol_version_ ^ 0xFF;
    char* payload_tmp = const_cast<char*>(payload.c_str());
    set_payload(payload_tmp);
}

void Message::set_protocol_version(uint8_t protocol_version) {
    protocol_version_ = protocol_version;
    inverse_protocol_version_ = protocol_version_ ^ 0xFF;
}

void Message::set_payload_type(uint16_t payload_type) {
    payload_type_ = payload_type;
}

void Message::set_payload(uint8_t *payload) {
    const char* payload_tmp = reinterpret_cast<const char*>(payload);
    payload_ = std::vector<uint8_t>(payload, payload + std::strlen(payload_tmp));
    payload_length_ = static_cast<uint32_t>(std::strlen(payload_tmp)); 
}

void Message::set_payload(std::vector<uint8_t> payload) {
    payload_ = payload;
    payload_length_ = static_cast<uint32_t>(payload.size());
}

void Message::set_payload(char* payload) {
    set_payload(reinterpret_cast<uint8_t*>(payload));
}

uint8_t Message::get_protocol_version() const {
    return protocol_version_;
}

uint16_t Message::get_version_info() const {
    return (protocol_version_ << 8) | inverse_protocol_version_;
}

uint16_t Message::get_payload_type() const {
    return payload_type_;
}

uint32_t Message::get_payload_length() const {
    return payload_length_;
}

uint8_t* Message::get_payload() {
    return payload_.data();
}

uint8_t *Message::get_message() const {
    uint8_t *message = new uint8_t[65535];
    message[0] = protocol_version_;
    message[1] = inverse_protocol_version_;
    std::vector<uint8_t> payload_type = common::utils::to_bytes(payload_type_, 2);
    std::copy(payload_type.begin(), payload_type.end(), message + 2);
    std::vector<uint8_t> payload_length = common::utils::to_bytes(payload_length_, 4);
    std::copy(payload_length.begin(), payload_length.end(), message + 4);
    for (int i = 0; i < int(payload_length_); i++) {
        message[8 + i] = payload_[i];
    }
    return message;
}

size_t Message::get_message_length() const {
    return 8 + payload_length_;
}

std::ostream& operator<<(std::ostream& os, const Message& message) {
    uint8_t *msg = message.get_message();
    size_t msg_len = message.get_message_length();
    for (size_t i = 0; i < msg_len; i++) {
        os << std::setfill('0') << std::setw(2) << std::hex << int(msg[i]) << " ";
    }
    return os;
}

Message Message::parse_message(uint8_t *message) {
    uint8_t protocol_version = message[0];
    uint8_t payload_type = message[2] << 8 | message[3];
    uint32_t payload_length = message[4] << 24 | message[5] << 16 | message[6] << 8 | message[7];
    std::vector<uint8_t> payload;
    for (int i = 0; i < int(payload_length); i++) {
        payload.push_back(message[8 + i]);
    }
    Message msg(protocol_version, payload_type, payload);
    return msg;
}

bool Message::send(int sockfd) {
    uint8_t *msg = get_message();
    size_t msg_len = get_message_length();
    int n = write(sockfd, msg, msg_len);
    if (n < 0) {
        std::cerr << "ERROR writing to socket" << std::endl;
        return false;
    }
    return true;
}

} // namespace proto
} // namespace common