//
// Created by guanggang.bian on 2023/5/8.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>


#define PORT 13200


int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        std::cout << "socket fail" << std::endl;
        return -1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int con_fd = connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (con_fd == -1) {
        std::cout << "connect failed" << std::endl;
        return -1;
    }

    std::cout << "this is client" << std::endl;

    std::string hello = "hello, this is client";

    ssize_t send_ret = send(client_fd, hello.c_str(), strlen(hello.c_str()), 0);
    if (send_ret == -1) {
        std::cout << "client send fail" << std::endl;
        return -1;
    }

    char response[1024];
    memset(response, 0, 1024);

    int rec_ret = recv(client_fd, response, sizeof(response), 0);
    if (rec_ret > 0) {
        std::cout << "receive success:\n" << (std::string)response << std::endl;
    } else if (rec_ret == 0) {
        std::cout << "receive close" << std::endl;
    } else {
        std::cout << "receive failed" << std::endl;
    }
    close(client_fd);
    return 0;
}