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
        void schedule(std::function<void(int)> &callback, const std::string& key);
        void unschedule(const std::string& key);
        void update();
        
    private:
        std::map<std::string, std::function<void(int)> > _timers;
    };
}

#endif /* Scheduler_hpp */
