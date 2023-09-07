add_executable(tcp_client
    tcp_client.cpp
)

target_link_libraries(tcp_client
    common_proto
)

add_executable(udp_client
    udp_client.cpp
)

target_link_libraries(udp_client
    common_proto
)