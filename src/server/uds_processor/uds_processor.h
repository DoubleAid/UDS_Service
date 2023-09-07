#pragma once

#include "../doip/processor.h"
#include "../uds_controller/uds_common/uds_storage.h"
#include "src/common/proto/Message.h"
#include "src/common/proto/UdsMessage.h"

namespace server {
namespace service {

class UdsProcessor : public BaseProcessor {
public:
UdsProcessor(const common::proto::Message& recv_msg,
             std::shared_ptr<server::storage::UdsStorage> storage = nullptr,
             int sockfd = -1);

~UdsProcessor() = default;

void process() override;

void process_sid_0x10();

void process_sid_0x11();

protected:
common::proto::Message recv_msg_;
std::shared_ptr<server::storage::UdsStorage> storage_;
int sockfd_;
};

} // namespace service
} // namespace server