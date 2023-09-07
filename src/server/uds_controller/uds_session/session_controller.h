#pragma once

#include <vector>
#include <cstdint>
#include <unordered_map>
#include "src/common/utils/cfg_loader/cfg_loader.h"
#include "src/common/utils/converter.h"

namespace server {
namespace service {

enum Session {
    SESSION_DEFAULT         = 0x01,
    SESSION_PROGRAMMING     = 0x02,
    SESSION_EXTENDED        = 0x03,
    SESSION_SAFETY          = 0x04,
    SESSION_INVALID         = 0xFF,
};

class SessionController {
public:
    SessionController();

    SessionController(const Session& session,
                      const std::vector<Session>& supported_sessions);

    SessionController(const common::utils::Config& cfg);

    ~SessionController() = default;

    Session get_current_session() const;

    bool set_current_session(const Session& session);

    std::vector<Session> get_supported_sessions() const;

    bool set_supported_sessions(const std::vector<Session>& supported_sessions);

    bool is_supported_session(const Session& session) const;

private:
    Session current_session_;
    std::vector<Session> supported_sessions_;
    std::unordered_map<uint32_t, std::vector<Session>> session_limitation_map_;
};

} // namespace service
} // namespace server