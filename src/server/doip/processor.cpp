#include <iostream>
#include "processor.h"
#include "../uds_processor/uds_processor.h"
#include "src/common/proto/Message.h"

namespace server {
namespace processor {

BaseProcessor* BaseProcessor::create(const common::proto::Message& message,
                                     std::shared_ptr<server::storage::UdsStorage> storage,
                                     int sockfd) {
    std::cout << message.get_payload_type() << std::endl;
    switch (message.get_payload_type()) {
        case PayloadType::Negative_Ack:
            return nullptr;
        case PayloadType::Vehicle_Identification::
            return nullptr;
        case PayloadType::Vehicle_Identification_With_Mac:
            return nullptr;
        case PayloadType::Vehicle_Identification_With_Vin:
            return nullptr;
        case PayloadType::Vehicle_Identification_Response:
            return nullptr;
        case PayloadType::Routing_Activation_Request:
            return nullptr;
        case PayloadType::UDS_Service_Request:
            return new UdsProcessor(message, storage, sockfd);
        case PayloadType::UDS_Service_ACK:
            return nullptr;
        case PayloadType::UDS_Service_NAck:
            return nullptr;
        default:
            assert(false);
    }
    return nullptr;
}

} // namespace processor
} // namespace server