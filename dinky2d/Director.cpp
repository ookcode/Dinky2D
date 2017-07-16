//
//  Director.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Director.hpp"

namespace Dinky {
    static Director* g_instance = nullptr;
    Director* Director::getInstance() {
        if(g_instance == nullptr) {
            g_instance = new Director();
        }
        return g_instance;
    }
    
    void Director::mainloop() {
        if(_runningScene) {
            _runningScene->draw();
        }
    }
    
    void Director::runWithScene(Scene *scene) {
        if(_runningScene) {
            delete _runningScene;
        }
        _runningScene = scene;
    }
    
    void Director::setWinSize(float width, float height) {
        _winSize = glm::vec2(width, height);
    }
}
