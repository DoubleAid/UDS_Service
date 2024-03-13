#include "doip_gateway/DoIP_Gateway.h"
#include "uds_server/uds_server.h"
#include "src/common/utils/log/logger.h"
#include "src/common/utils/cfg_loader/cfg_loader.h"
#include "src/common/thread/threadsafe_queue.h"
#include "common/uds_message.h"


namespace server {

class Server {
public:
  Server(const std::string& customer);
  void process();
private:
  std::shared_ptr<doip::DoIP_Gateway> doip_str_;
  std::shared_ptr<uds::UDS_Server> uds_ptr_;
};

} // namespace server