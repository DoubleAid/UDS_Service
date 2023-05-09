//
// Created by guanggang.bian on 2023/5/8.
//


#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <netinet/in.h>

// using close
#include <unistd.h>

//#include <google/protobuf/message.h>

#define PORT 13200
#define MAX_LISTEN_QUEUE 5

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cout << "socket fail" << std::endl;
        return -1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
//    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret = bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (ret < 0) {
        std::cout << "bind socket fail" << std::endl;
        return -1;
    }

    ret = listen(server_fd, MAX_LISTEN_QUEUE);
    if (ret < 0) {
        std::cout << "listen socket fail" << std::endl;
        return -1;
    }

    std::cout << "welcome to UDS server!" << std::endl;

    char buffer[1024];

    int client_fd = 0;
    socklen_t client_addr_len = 0;

    sockaddr_in client_addr{};

    while (true) {
        std::cout << "wait..." << std::endl;
        bzero(&client_addr, sizeof(client_addr));
        client_addr_len = sizeof(client_addr);

        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_fd < 0) {
            std::cout << "accept failed" << std::endl;
            return -1;
        }

        while (true) {
            memset(buffer, 0, 1024);

            ssize_t rec_ret = recv(client_fd, buffer, sizeof(buffer), 0);
            if (rec_ret > 0) {
                std::cout << "receive message:" << (std::string)buffer << std::endl;
            } else if (rec_ret == 0) {
                std::cout << "receive close" << std::endl;
                break;
            } else {
                std::cout << "receive fail" << std::endl;
                break;
            }

            std::string ans = "i have received message!";

            ssize_t send_ret = send(client_fd, ans.c_str(), strlen(ans.c_str()), 0);
            if (send_ret == -1) {
                std::cout << "server send failed" << std::endl;
            }
        }
        close(client_fd);
    }
    close(server_fd);
    return 0;
}