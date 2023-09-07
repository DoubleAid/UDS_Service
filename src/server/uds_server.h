#pragma once

#include <iostream>
#include "src/common/thread/thread_pool.h"
#include "src/common/utils/cfg_loader/cfg_loader.h"
#include "doip/processor.h"
#include "uds_controller/uds_common/uds_storage.h"

namespace server {

class Task {
public:
    Task(int ver = -1, int sockfd = -1) : version_(ver), sockfd_(sockfd) {}

    void set_version(int ver) { version_ = ver; }
    void set_sockfd(int sockfd) { sockfd_ = sockfd; }

    int get_version() const { return version_; }
    int get_sockfd() const { return sockfd_; }

private:
    int version_;
    int sockfd_;
};

using TaskQueue = common::thread::ThreadSafeQueue<Task>;

class UdsServer {
public:
    UdsServer();

    UdsServer(const common::utils::Config &cfg);

    void process();

    static void tcp_listener(std::shared_ptr<TaskQueue> task_queue);

    static void tcp_processor(int id,
                              std::shared_ptr<TaskQueue> task_queue
                              std::shared_ptr<server::storage::UdsStorage> uds_storage);
private:
    std::shared_ptr<common::thread::ThreadPool> pool_;
    std::shared_ptr<TaskQueue> queue_;
    std::shared_ptr<server::storage::UdsStorage> storage_;
};

} // namespace server