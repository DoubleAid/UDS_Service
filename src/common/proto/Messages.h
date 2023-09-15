#pragma once

#include <vector>
#include <string>

namespace common {
namespace proto {

class Message {
public:
    Message(uint8_t protocol_version, uint16_t payload_type, uint8_t *payload);
    Message(uint8_t protocol_version, uint16_t payload_type, std::vector<uint8_t> payload);
    Message(uint8_t protocol_version, uint16_t payload_type, char* payload);
    Message(uint8_t protocol_version, uint16_t payload_type, const std::string& payload);
    ~Message() = default;
    void set_protocol_version(uint8_t protocol_version);
    void set_payload_type(uint16_t payload_type);
    void set_payload(uint8_t *payload);
    void set_payload(std::vector<uint8_t> payload);
    void set_payload(char* payload);
    uint8_t get_protocol_version() const;
    uint16_t get_version_info() const;
    uint16_t get_payload_type() const;
    uint32_t get_payload_length() const;
    uint8_t *get_payload();
    uint8_t *get_message() const;
    size_t get_message_length() const;
    friend std::ostream& operator<<(std::ostream& os, const Message& message);
    static Message parse_message(uint8_t *message);
    bool send(int sockfd);
private:
    uint8_t protocol_version_;
    uint8_t inverse_protocol_version_;
    uint16_t payload_type_;
    uint32_t payload_length_;
    std::vector<uint8_t> payload_;
};

class NegativeAckMessage : public Message {
public:
    NegativeAckMessage(uint8_t protocol_version = 0x02) :
            Message(protocol_version, 0x0000, std::vector<uint8_t>()) {}
    NegativeAckMessage(const Message& message) :
            Message(message.get_protocol_version(), 0x0000, std::vector<uint8_t>()) {}
};

} // namespace proto
} // namespace common