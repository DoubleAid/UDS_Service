#include <iostream>
#include "uds_server.h"
#include "src/common/utils/cfg_loader/cfg_loader.h"

using namespace std;

void print_usage() {
    cout << "Usage: ./uds_server_main <config_file>" << endl;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Error: need extra argument" << endl;
        print_usage();
        return -1;
    }

    std::string config_file(argv[1]);
    common::utils::Config cfg = common::utils::readIniFile(config_file);

    server::UdsServer uds_server(cfg);
    uds_server.process();
    return 0;
}