//
//  ProgramCache.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/2.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef ProgramCache_hpp
#define ProgramCache_hpp

#include <unordered_map>
#include "Program.hpp"

namespace Dinky {
    class ProgramCache {
    public:
        static ProgramCache *getInstance();
        void addProgram(const std::string &key);
        Program* getProgram(const std::string &key);
        
    private:
        ProgramCache();
        ~ProgramCache();
        static ProgramCache *_instance;
        std::unordered_map<std::string, Program *> _programs;
    };
}

#endif /* ProgramCache_hpp */
