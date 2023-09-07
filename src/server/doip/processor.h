#pragma once

#include <memory>
#include <cassert>
#include "../uds_controller/uds_common/uds_storage.h"
#include "src/common/proto/Messages.h"

namespace server {
namespace processor {

enum PayloadType {
    Negative_Ack                    = 0x0000,
    Vehicle_Identification          = 0x0001,
    Vehicle_Identification_With_Mac = 0x0002,
    Vehicle_Identification_With_Vin = 0x0003,
    Vehicle_Identification_Response = 0x0004,
    Routing_Activation_Request      = 0x0005,
    UDS_Service_Request             = 0x8001,
    UDS_Service_ACK                 = 0x8002,
    UDS_Service_NAck                = 0x8003,
};

class BaseProcessor {
public:
    static BaseProcessor* create(const common::proto::Message& message,
                                 std::shared_ptr<server::storage::UdsStorage> storage,
                                 int sockfd);
    virtual ~BaseProcessor() = default;
    virtual void process() = 0;
protected:
    BaseProcessor() = default;
};

} // namespace processor
} // namespace server