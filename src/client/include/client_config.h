#include <iostream>
#include <vector>
#include <string>

namespace client {
namespace service {

class ClientConfig {
public:
    static ClientConfig parse_config(int argc, char** argv);
    uint32_t get_port() const;
    std::string get_server_ip() const;
    std::string get_customer_name() const;
private:
    std::string server_ip_;
    std::string nickname_;
    uint32_t port_;
    uint16_t source_addr_;
    uint16_t target_addr_;
};

}
}