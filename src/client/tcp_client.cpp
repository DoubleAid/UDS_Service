#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iomanip>
#include <unordered_map>
#include <string>
#include <vector>
#include <cstring>
#include "src/common/proto/Messages.h"

using namespace std;

using Config = std::unordered_map<std::string, std::string>;

int main(int argc, char *argv[]) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(13400);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "connect failed" << endl;
        return -1;
    }

    std::vector<uint8_t> payload = {0x0e, 0x80, 0xe4, 0x00, 0x10, 0x01};
    common::proto::Message message(0x02, 0x8001, payload)
    uint8_t *msg = messgae.get_message();
    size_t msg_len = message.get_message_length();
    cout << "send message: " << message << endl;
    if (send(sockfd, msg, msg_len, 0) < 0) {
        cerr << "send failed" << endl;
        return -1;
    }

    size_t count = 200;
    uint8_t recv_buf[1024];
    while (true) {
        memset(recv_buf, 0, sizeof(recv_buf));
        int recv_len = recv(sockfd, recv_buf, sizeof(recv_buf), 0);
        if (recv_len < 0) {
            cerr << "receive message failed" << endl;
            continue;
        }
        common::proto::Message recv_msg = common::proto::Message::parse_message(recv_buf);
        cout << "recv message: " << recv_msg << endl;
        if (0 == count--) {
            break;
        }
    }
    close(sockfd);
    return 0;
}