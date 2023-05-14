
# FILE(GLOB_RECURSE PROTOS_ALL RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/proto/.. *.proto)

# # Specify the directory in which to search for imports.
# set(PROTOBUF_SEARCH_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/proto/..)
# # current directory to get proto file's absolute path
# set(PROTOBUF_IMPORT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
# # set(PROTOBUF_GENERATE_CPP_APPEND_PATH ${CMAKE_CURRENT_BINARY_DIR}/proto/..)
# # protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS 
# #                       ${PROTOBUF_SEARCH_DIRS}
# #                       ${PROTOBUF_IMPORT_DIR}
# #                       ${PROTOBUF_CPP_EXPORT_DIR} 
# #                       ${PROTOS_ALL}
# # )
# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOS_ALL})

# add_library(common_proto SHARED
#     ${PROTO_SRCS}
# )

# target_link_libraries(common_proto
#     ${PROTBUF_LIBRARIES}
# )

add_subdirectory(thread)
add_subdirectory(logger)
add_subdirectory(util)
add_subdirectory(proto)