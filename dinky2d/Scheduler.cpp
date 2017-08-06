//
//  Scheduler.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/6.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Scheduler.hpp"

namespace Dinky {
    Scheduler::Scheduler() {
        
    }
    
    Scheduler::~Scheduler() {
        _timers.clear();
    }
    
    void Scheduler::schedule(std::function<void (int)> &callback, const std::string &key) {
        auto iter = _timers.find(key);
        if(iter != _timers.end()) {
            std::string msg("schedule key already exists ");
            throw std::runtime_error(msg + key);
        }
        _timers[key] = callback;
    }
    
    void Scheduler::unschedule(const std::string &key) {
        auto iter = _timers.find(key);
        if(iter != _timers.end()) {
            _timers.erase(iter);
        }
    }
    
    void Scheduler::update() {
        for (auto iter = _timers.begin(); iter != _timers.end(); ++iter) {
            (iter->second)(0);
        }
    }
}
