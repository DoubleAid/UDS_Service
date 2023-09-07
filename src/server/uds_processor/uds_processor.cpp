#include "uds_processor.h"
#include <iostream>

namespace server {
namespace service {

UdsProcessor::UdsProcessor(const common::proto::Message& recv_msg,
                           std::shared_ptr<server::storage::UdsStorage> storage,
                           int sockfd) :
        recv_msg_(recv_msg),
        storage_(storage),
        sockfd_(sockfd) {}

void UdsProcessor::process() {
    common::proto::UdsMessage uds_msg(recv_msg_);

    bool ret = storage_->check_source_address(uds_msg.get_source_address());
    if (!ret) {
        std::cout << "source address is not valid" << std::endl;
        common::proto::UdsNegativeAckMessage neg_ack_msg(uds_msg, 0x02);
        neg_ack_msg.send(sockfd_);
        return;
    }

    ret = storage_->check_target_address(uds_msg.get_target_address());
    if (!ret) {
        std::cout << "target address is not valid" << std::endl;
        common::proto::UdsNegativeAckMessage neg_ack_msg(uds_msg, 0x03);
        neg_ack_msg.send(sockfd_);
        return;
    }

    common::proto::UdsPositiveAckMessage ack_msg(uds_msg);
    ack_msg.send(sockfd_);

    switch (uds_msg.get_service_id()) {
        case 0x10:
            process_sid_0x10();
            break;
        case 0x11:
            process_sid_0x11();
            break;
        default:
            std::cout << "service id is not valid" << std::endl;
            break;
    }
}

void UdsProcessor::process_sid_0x10(const common::proto::UdsMessage& uds_msg) {
    std::cout << "process_sid_0x10" << std::endl;
    uds_msg.send_reply(sockfd_, {0x01, 0x00});
}

void UdsProcessor::process_sid_0x11(const common::proto::UdsMessage& uds_msg) {
    std::cout << "process_sid_0x11" << std::endl;
    uds_msg.send_reply(sockfd_, {0x00});
}

} // namespace service
} // namespace server