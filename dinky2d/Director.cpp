//
//  Director.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Director.hpp"

namespace Dinky {
    Director* Director::_instance = nullptr;
    Director* Director::getInstance() {
        if(_instance == nullptr) {
            _instance = new Director();
        }
        return _instance;
    }
    
    Director::Director() {
        _renderer = new Renderer();
        _scheduler = new Scheduler();
    }
    
    Director::~Director() {
        delete _renderer;
        delete _scheduler;
    }
    
    void Director::setOpenGLView() {
        _renderer->initGLView();
    }
    
    void Director::mainloop() {
        drawScene();
        _scheduler->update();
    }
    
    void Director::drawScene() {
        _renderer->clear();
        if(_runningScene) {
            _runningScene->render(_renderer);
        }
        _renderer->render();
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
