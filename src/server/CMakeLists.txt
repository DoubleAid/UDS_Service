add_library(uds_library
    uds_server.cpp
    doip/processor.cpp
    uds_controller/uds_did/did_controller.cpp
    uds_controller/uds_dtc/dtc_controller.cpp
    uds_controller/uds_routine/routine_controller.cpp
    uds_controller/uds_security/security_controller.cpp
    uds_controller/uds_session/session_controller.cpp
    uds_controller/uds_common/address_controller.cpp
    uds_controller/uds_common/uds_storage.cpp
    uds_processor/uds_processor.cpp
)

target_link_libraries(uds_library
    common_thread
    common_utils
    common_proto
)

add_executable(uds_server uds_server_main.cpp)

target_link_libraries(uds_server
    common_thread
    common_utils
    uds_library
)