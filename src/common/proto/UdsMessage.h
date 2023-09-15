#pragma once

#include "Message.h"
#include <memory>
#include <vector>

namespace common {
namespace proto {

class UdsMessage : public Message {
public:
UdsMessage(const Message& msg);

UdsMessage(uint8_t protocol_version, uint16_t payload_type, uint8_t *payload);

UdsMessage(uint8_t protocol_version, uint16_t payload_type, std::vector<uint8_t> payload);

UdsMessage(uint8_t protocol_version, uint16_t payload_type, char* payload);

UdsMessage(uint8_t protocol_version, uint16_t payload_type, const std::string& payload);

~UdsMessage() = default;

void set_source_address(uint16_t source_address);

void set_target_address(uint16_t target_address);

void set_service_id(uint8_t service_id);

void clear_data();

void append_data(uint8_t data);

void insert_data(std::vector<uint8_t> data);

uint16_t get_source_address() const;

uint16_t get_target_address() const;

uint8_t get_service_id() const;

std::vector<uint8_t> get_data() const;

void switch_source_target();

void send_reply(int sockfd, const std::vector<uint8_t>& data) const;

protected:
uint16_t source_address_;

uint16_t target_address_;

uint8_t service_id_;

std::vector<uint8_t> data_;
};

class UdsPositiveAckMessage : public UdsMessage {
public:
    UdsPositiveAckMessage(const Message& message) :
            UdsMessage(message) {
        set_payload_type(0x8002);
        clear_data();
        set_service_id(0x00);
        switch_source_target();
    }
};

class UdsNegativeAckMessage : public UdsMessage {
public:
    UdsNegativeAckMessage(const Message& message, uint8_t negative_code) :
            UdsMessage(message) {
        set_payload_type(0x8003);
        clear_data();
        set_service_id(negative_code);
        switch_source_target();
    }
};

} // namespace proto
} // namespace common