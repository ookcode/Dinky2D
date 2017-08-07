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

namespace Dinky {
    class Scheduler {
    public:
        Scheduler();
        ~Scheduler();
        typedef std::function<void(float)> SEL_SCHEDULE;
        std::string schedule(SEL_SCHEDULE &callback);
        void unschedule(SEL_SCHEDULE &callback);
        void unschedule(const std::string& key);
        void unscheduleAll();
        void update(float dt);
        
    private:
        std::map<std::string, SEL_SCHEDULE> _timers;
    };
}

#endif /* Scheduler_hpp */
