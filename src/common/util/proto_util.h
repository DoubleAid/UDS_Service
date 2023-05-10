//
// Created by guanggang.bian on 2023/5/9.
//

#pragma once

#include <google/protobuf/message.h>

namespace guanggang {
namespace common {
namespace util {

bool loadProtoFile(const std::string& filename, ::google::protobuf::Message* msg);

bool loadProtoTextFile(const std::string& filename, ::google::protobuf::Message* msg);

bool loadProtoBinaryFile(const std::string& filename, ::google::protobuf::Message* msg);

bool writeProtoFile(const std::string& filename, const ::google::protobuf::Message& msg);

bool writeProtoTextFile(const std::string& filename, const ::google::protobuf::Message& msg);

bool writeProtoBinaryFile(const std::string& filename, const ::google::protobuf::Message& msg);



}
}
}