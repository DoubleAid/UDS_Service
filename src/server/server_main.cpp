#include "server.h"
#include "common/constants.h"

using namespace std;

void print_usage() {
  cout << "Usage: ./uds_server_main <config_file>" << endl;
}

void destoryer() {
  common::util::LOG_INFO("server exit");
}

int main(int argc, char *argv[]) {
  std::atexit(destoryer);

  int option;
  bool display_trigger = false;
  std::string customer = "DEV"
  while ((option = getopt(argc, argv, "c:d")) != -1) {
    switch (option) {
      case 'c':
        if (optarg != nullptr) {
          customer = optarg;
        }
        break;
      case 'd':
        display_trigger = true;
        break;
      default:
        print_usage()
        return -1
    }
  }
  
  common::util::init_logger(display_trigger,
                            server::constants::Log_Filepath);

  try {
    server::Server server(customer);
    server.process();
  } catch (std::exception& e) {
    common::util::LOG_ERROR("Error: %s")
    return 
  }
  return 0;
}