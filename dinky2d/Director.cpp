//
//  Director.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Director.hpp"
#include <chrono>
#include <sstream>
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
        _globalScheduler = new Scheduler();
    }
    
    Director::~Director() {
        delete _renderer;
        delete _globalScheduler;
    }
    
    void Director::setOpenGLView() {
        _renderer->initGLView();
    }
    
    long Director::getTimeStamp() {
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epoch = now_ms.time_since_epoch();
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
        long duration = value.count();
        return duration;
    }
    
    void Director::registerScheduler(Scheduler *scheduler) {
        std::ostringstream oskey;
        oskey << scheduler;
        std::string key = oskey.str();
        auto iter = _schedulers.find(key);
        assert(iter == _schedulers.end() && "registerScheduler fail, scheduler already exists");
        if(iter == _schedulers.end()) {
            _schedulers[key] = scheduler;
        }
    }
    
    void Director::ungisterScheduler(Scheduler *scheduler) {
        std::ostringstream oskey;
        oskey << scheduler;
        std::string key = oskey.str();
        auto iter = _schedulers.find(key);
        // assert(iter != _schedulers.end() && "ungisterScheduler fail, scheduler not exists");
        if(iter != _schedulers.end()) {
            _schedulers.erase(iter);
        }
    }
    
    void Director::registerKeyboardDelegate(IMEDelegate *delegate) {
        std::ostringstream oskey;
        oskey << delegate;
        std::string key = oskey.str();
        auto iter = _keyListeners.find(key);
        assert(iter == _keyListeners.end() && "registerKeyboardDelegate fail, delegate already exists");
        if(iter == _keyListeners.end()) {
            _keyListeners[key] = delegate;
        }
    }
    
    void Director::unregisterKeyboardDelegate(IMEDelegate *delegate) {
        std::ostringstream oskey;
        oskey << delegate;
        std::string key = oskey.str();
        auto iter = _keyListeners.find(key);
        if(iter != _keyListeners.end()) {
            _keyListeners.erase(iter);
        }
    }
    
    void Director::onKeyUp(int key, bool isSpecialKey) {
        std::vector<std::string> list;
        for(auto const &pairs: _keyListeners) {
            list.push_back(pairs.first);
        }
        for(auto const &value : list) {
            auto iter = _keyListeners.find(value);
            if (iter != _keyListeners.end()) {
                iter->second->onKeyUp(key, isSpecialKey);
            }
        }
    }
    
    void Director::onKeyDown(int key, bool isSpecialKey) {
        std::vector<std::string> list;
        for(auto const &pairs: _keyListeners) {
            list.push_back(pairs.first);
        }
        for(auto const &value : list) {
            auto iter = _keyListeners.find(value);
            if (iter != _keyListeners.end()) {
                iter->second->onKeyDown(key, isSpecialKey);
            }
        }
    }
    
    void Director::registerTouchDelegate(TouchDelegate *delegate) {
        std::ostringstream oskey;
        oskey << delegate;
        std::string key = oskey.str();
        auto iter = _touchListeners.find(key);
        assert(iter == _touchListeners.end() && "registerTouchDelegate fail, delegate already exists");
        if(iter == _touchListeners.end()) {
            _touchListeners[key] = delegate;
        }
    }
    
    void Director::unregisterTouchDelegate(TouchDelegate *delegate) {
        std::ostringstream oskey;
        oskey << delegate;
        std::string key = oskey.str();
        auto iter = _touchListeners.find(key);
        if(iter != _touchListeners.end()) {
            _touchListeners.erase(iter);
        }
    }

    void Director::onTouchBegin(int x, int y) {
        std::vector<std::string> list;
        for(auto const &pairs: _touchListeners) {
            list.push_back(pairs.first);
        }
        for(auto const &value : list) {
            auto iter = _touchListeners.find(value);
            if (iter != _touchListeners.end()) {
                iter->second->onTouchBegin(x, y);
            }
        }
    }
    
    void Director::onTouchMove(int x, int y) {
        std::vector<std::string> list;
        for(auto const &pairs: _touchListeners) {
            list.push_back(pairs.first);
        }
        for(auto const &value : list) {
            auto iter = _touchListeners.find(value);
            if (iter != _touchListeners.end()) {
                iter->second->onTouchMove(x, y);
            }
        }
    }
    
    void Director::onTouchEnded(int x, int y) {
        std::vector<std::string> list;
        for(auto const &pairs: _touchListeners) {
            list.push_back(pairs.first);
        }
        for(auto const &value : list) {
            auto iter = _touchListeners.find(value);
            if (iter != _touchListeners.end()) {
                iter->second->onTouchEnded(x, y);
            }
        }
    }
    
    
    void Director::mainloop() {
        if(_lastTimeStamp == 0) {
            _lastTimeStamp = getTimeStamp();
        }
        long currentTimeStamp = getTimeStamp();
        float dt = (currentTimeStamp - _lastTimeStamp) / 1000.0f;
        _realFps = 1.0f / dt;
        // printf("dt = %f , fps = %f\n", dt, _realFps);
        _lastTimeStamp = currentTimeStamp;
        
        // 遍历定时器
        std::vector<std::string> list;
        for(auto const &pairs: _schedulers) {
            list.push_back(pairs.first);
        }
        for(auto const &value : list) {
            auto iter = _schedulers.find(value);
            if (iter != _schedulers.end()) {
                iter->second->update(dt);
            }
        }
        
        drawScene();
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
