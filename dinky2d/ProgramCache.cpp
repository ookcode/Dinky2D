//
//  ProgramCache.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/2.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "ProgramCache.hpp"

namespace Dinky {
    ProgramCache* ProgramCache::_instance = nullptr;
    ProgramCache* ProgramCache::getInstance() {
        if(_instance == nullptr) {
            _instance = new ProgramCache();
        }
        return _instance;
    }
    
    ProgramCache::ProgramCache() {
        addProgram(Program::SHADER_DEFAULT);
        addProgram(Program::SHADER_DEFAULT_COLOR);
    }
    
    ProgramCache::~ProgramCache() {
        
    }
    
    void ProgramCache::addProgram(const std::string &key) {
        if(getProgram(key) == nullptr) {
            Program* program = new Program(key);
            _programs[key] = program;
        }
    }
    
    Program* ProgramCache::getProgram(const std::string &key) {
        auto iter = _programs.find(key);
        if(iter != _programs.end())
            return iter->second;
        return nullptr;
    }
}
