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
    
    std::string Scheduler::schedule(SEL_SCHEDULE &callback) {
        std::ostringstream oskey;
        oskey << &callback;
        std::string key = oskey.str();
        auto iter = _timers.find(key);
        assert(iter == _timers.end() && "schedule fail, SEL_SCHEDULE already exists");
        if(iter == _timers.end()) {
            if(_timers.empty()) {
                Director::getInstance()->registerScheduler(this);
            }
            _timers[key] = callback;
        }
        return key;
    }
    
    void Scheduler::unschedule(SEL_SCHEDULE &callback) {
        std::ostringstream oskey;
        oskey << &callback;
        std::string key = oskey.str();
        unschedule(key);
    }
    
    void Scheduler::unschedule(const std::string &key) {
        auto iter = _timers.find(key);
        assert(iter != _timers.end() && "unschedule fail, key not exists");
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
        for (auto iter = _timers.begin(); iter != _timers.end(); ++iter) {
            (iter->second)(dt);
        }
    }
}
