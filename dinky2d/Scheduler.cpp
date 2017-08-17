//
//  Scheduler.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/6.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Scheduler.hpp"
#include <sstream>
#include "Director.hpp"
namespace Dinky {
    Scheduler::Scheduler() {
        
    }
    
    Scheduler::~Scheduler() {
        _timers.clear();
        Director::getInstance()->ungisterScheduler(this);
    }
    
    std::string Scheduler::schedule(SEL_SCHEDULE callback, Node *target) {
        std::ostringstream oskey;
        oskey << target << callback;
        std::string key = oskey.str();
        auto iter = _timers.find(key);
        assert(iter == _timers.end() && "schedule fail, SEL_SCHEDULE already exists");
        if(iter == _timers.end()) {
            if(_timers.empty()) {
                Director::getInstance()->registerScheduler(this);
            }
            _timers[key] = std::make_pair(target, callback);
        }
        return key;
    }
    
    void Scheduler::unschedule(SEL_SCHEDULE callback, Node *target) {
        std::ostringstream oskey;
        oskey << target << callback;
        std::string key = oskey.str();
        unschedule(key);
    }
    
    void Scheduler::unschedule(const std::string &key) {
        auto iter = _timers.find(key);
//        assert(iter != _timers.end() && "unschedule fail, key not exists");
        if(iter != _timers.end()) {
            _timers.erase(iter);
            if(_timers.empty()) {
                Director::getInstance()->ungisterScheduler(this);
            }
        }
    }
    
    void Scheduler::unscheduleAll() {
        _timers.clear();
        Director::getInstance()->ungisterScheduler(this);
    }
    
    void Scheduler::update(float dt) {
        std::vector<std::string> list;
        for(auto const &pairs: _timers) {
            list.push_back(pairs.first);
        }
        for(auto const &value : list) {
            auto iter = _timers.find(value);
            if (iter != _timers.end()) {
                auto callback = iter->second;
                (callback.first->*callback.second)(dt);
            }
        }
    }
}
