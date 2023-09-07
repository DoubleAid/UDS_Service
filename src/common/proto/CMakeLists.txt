add_library(common_proto
    Messages.cpp
)

target_link_libraries(common_proto
    common_util
)