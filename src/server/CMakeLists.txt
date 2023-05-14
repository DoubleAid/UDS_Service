add_executable(server
		server.cpp
)

target_link_libraries(server
		common_thread
		common_proto
		${PROTOBUF_LIBRARIES}
		protobuf::libprotobuf
)