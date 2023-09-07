#include <algorithm>
#include "session_controller.h"

namespace server {
namespace service {

SessionController::SessionController() :
        current_session_(Session::SESSION_DEFAULT),
        supported_sessions_({Session::SESSION_DEFAULT,
                             Session::SESSION_PROGRAMMING,
                             Session::SESSION_EXTENDED,
                             Session::SESSION_SAFETY}) {}

SessionController::SessionController(const Session& session,
                                     const std::vector<Session>& supported_sessions) :
        current_session_(session),
        supported_sessions_(supported_sessions) {}

SessionController::SessionController(common::utils::Config& cfg) {
    if (cfg.find("Supported_Sessions") != cfg.end()) {
        std::string val = cfg["Supported_Sessions"];
        std::vector<int> local_address_tmp = common::utils::string_to_vector<int>(val);
        for (auto& address : local_address_tmp) {
            supported_sessions_.push_back(static_cast<Session>(address));
        }
        current_session_ = supported_sessions_[0];
    }
}

Session SessionController::get_current_session() const {
    return current_session_;
}

bool SessionController::set_current_session(const Session& session) {
    if (std::find(supported_sessions_.begin(), supported_sessions_.end(), session) !=
        supported_sessions_.end()) {
        current_session_ = session;
        return true;
    }
    return false;
}

std::vector<Session> SessionController::get_supported_sessions() const {
    return supported_sessions_;
}

bool SessionController::set_supported_sessions(const std::vector<Session>& supported_sessions) {
    supported_sessions_ = supported_sessions;
    return true;
}

bool SessionController::is_supported_session(const Session& session) const {
    return std::find(supported_sessions_.begin(), supported_sessions_.end(), session) !=
           supported_sessions_.end();
}

} // namespace service
} // namespace server