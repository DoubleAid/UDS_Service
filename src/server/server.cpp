#include <thread>
#include "server.h"


namespace server {
  Server::Server(const std::string& customer) {
    server::uds::UDSStorageFactory::getInstance().init(customer);
    doip_ptr_ = doip::DoIP_Gateway::getInstance();
    uds_ptr_ = uds::UDS_Server::getInstance();
    doip_ptr_ -> setTxQueue(uds_ptr_->getRxQueue());
    uds_ptr_ -> setTxQueue(doip_ptr_->getRxQueue());
  }

  void Server::process() {
    std::thread doip_thread([&]() {
      doip_str_ -> process();
    });

    std::thread uds_thread([&]() {
      uds_ptr_ -> process();
    });

    doip_thread.join();
    uds_thread.join();
  }
} // namespace server