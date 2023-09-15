add_library(common_proto
    Messages.cpp
    Messages.h
    UdsMessage.cpp
    UdsMessage.h
)

target_link_libraries(common_proto
    common_util
)