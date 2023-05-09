//
// Created by guanggang.bian on 2023/5/9.
//

#pragma once

#include <condition_variable>
#include <queue>
#include <memory>
#include <mutex>
#include <thread>

namespace guanggang {
namespace common {
namespace thread {

template <typename T>
class ThreadSafeQueue {
public:

    void push(T new_val);
};

}
}
}
