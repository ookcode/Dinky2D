//
//  Scheduler.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/6.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef Sheduler_hpp
#define Sheduler_hpp

#include <string>
#include <map>
#include <functional>
#define SCHEDULE(_SELECTOR) static_cast<Scheduler::SEL_SCHEDULE>(&_SELECTOR)
namespace Dinky {
    class Node;
    class Scheduler {
    public:
        Scheduler();
        ~Scheduler();
        typedef void(Node::*SEL_SCHEDULE)(float);
        std::string schedule(SEL_SCHEDULE callback, Node *target);
        void unschedule(SEL_SCHEDULE callback, Node *target);
        void unschedule(const std::string &key);
        void unscheduleAll();
        void update(float dt);
        
    private:
        std::map<std::string, std::pair<Node*, SEL_SCHEDULE>> _timers;
    };
}

#endif /* Scheduler_hpp */
