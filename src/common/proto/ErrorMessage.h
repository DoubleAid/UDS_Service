#pragma once

#include "Message.h"

namespace common {
namespace proto {

enum UDS_NRC {
    UDS_NRC_GR      = 0x10,         // General Reject
    UDS_NRC_SNS     = 0x11,         // Service Not Supported
    UDS_NRC_SFNS    = 0x12,         // Sub-Function Not Supported
    UDS_NRC_IMLOIFC = 0x13,         // Incorrect Message Length Or Invalid Format
    UDS_NRC_RTL     = 0x14,         // Response Too Long
    UDS_NRC_BRR     = 0x21,         // Busy Repeat Request By Tester
    UDS_NRC_CNC     = 0x22,         // Conditions Not Correct
    UDS_NRC_RSE     = 0x24,         // Request Sequence Error
    UDS_NRC_NCS     = 0x25,         // No Communication Session
    UDS_NRC_FPE     = 0x26,         // Failure Prevents Execution Of Requested Action
    UDS_NRC_ROOR    = 0x31,         // Request Out Of Range
    UDS_NRC_SAD     = 0x33,         // Security Access Denied
    UDS_NRC_IK      = 0x35,         // Invalid Key
    UDS_NRC_EA      = 0x36,         // Exceed Number Of Attempts
    UDS_NRC_RTDNE   = 0x37,         // Required Time Delay Not Expired
    UDS_NRC_UDNA    = 0x70,         // Upload Download Not Accepted
    UDS_NRC_TDS     = 0x71,         // Transfer Data Suspended
    UDS_NRC_GPF     = 0x72,         // General Programming Failure
    UDS_NRC_WBSC    = 0x73,         // Wrong Block Sequence Counter
    UDS_NRC_RRRP    = 0x78,         // Request Correctly Received-Response Pending
    UDS_NRC_SFNSIAS = 0x7E,         // Sub-Function Not Supported In Active Session
    UDS_NRC_SFNSIDS = 0x7F,         // Service Not Supported In Active Session
    UDS_NRC_IVRSA   = 0xF0,         // Invalid RSA Signature
    UDS_NRC_IVTS    = 0xF1,         // Invalid value of timestamp
    UDS_NRC_IVCERT  = 0xF2,         // Invalid certificate
};

class ErrorMessage : public UdsMessage {
public:
    ErrorMessage(const Message& message) : UdsMessage(message) {
        uint8_t sid = get_service_id();
        set_service_id(0x7F);
        switch_source_target();
        clear_data();
        append_data(sid);
    }
};

#define DEFINE_UDS_NRC(nrc) \
class Errot##nrc : public ErrorMessage { \
public: \
    Error##nrc(const Message& message) : ErrorMessage(message) { \
        append_data(UDS_NRC_##nrc); \
    } \
}

DEFINE_UDS_NRC(GR);
DEFINE_UDS_NRC(SNS);
DEFINE_UDS_NRC(SFNS);
DEFINE_UDS_NRC(IMLOIFC);
DEFINE_UDS_NRC(RTL);
DEFINE_UDS_NRC(BRR);
DEFINE_UDS_NRC(CNC);
DEFINE_UDS_NRC(RSE);
DEFINE_UDS_NRC(NCS);
DEFINE_UDS_NRC(FPE);
DEFINE_UDS_NRC(ROOR);
DEFINE_UDS_NRC(SAD);
DEFINE_UDS_NRC(IK);
DEFINE_UDS_NRC(EA);
DEFINE_UDS_NRC(RTDNE);
DEFINE_UDS_NRC(UDNA);
DEFINE_UDS_NRC(TDS);
DEFINE_UDS_NRC(GPF);
DEFINE_UDS_NRC(WBSC);
DEFINE_UDS_NRC(RRRP);
DEFINE_UDS_NRC(SFNSIAS);
DEFINE_UDS_NRC(SFNSIDS);
DEFINE_UDS_NRC(IVRSA);
DEFINE_UDS_NRC(IVTS);
DEFINE_UDS_NRC(IVCERT);

} // namespace proto
} // namespace common
