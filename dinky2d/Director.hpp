//
//  Director.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef Director_hpp
#define Director_hpp

#include <string>
#include "Renderer.hpp"
#include "Scene.hpp"
#include "Scheduler.hpp"
#include "IMEDelegate.h"
#include "TouchDelegate.h"
namespace Dinky {
    
    class Director {
    public:
        static Director* getInstance();
        void setOpenGLView();
        void mainloop();
        void runWithScene(Scene *scene);
        void setWinSize(float width, float height);
        glm::vec2 getWinSize() {
            return _winSize;
        }
        void registerScheduler(Scheduler *scheduler);
        void ungisterScheduler(Scheduler *scheduler);
        Scheduler* getScheduler() {
            return _globalScheduler;
        }
        void onKeyDown(int key, bool isSpecialKey);
        void onKeyUp(int key, bool isSpecialKey);
        void registerKeyboardDelegate(IMEDelegate *delegate);
        void unregisterKeyboardDelegate(IMEDelegate *delegate);
        
        void onTouchBegin(int x, int y);
        void onTouchMove(int x, int y);
        void onTouchEnded(int x, int y);
        void registerTouchDelegate(TouchDelegate *delegate);
        void unregisterTouchDelegate(TouchDelegate *delegate);
        
    private:
        Director();
        ~Director();
        void drawScene();
        long getTimeStamp();
        
        glm::vec2 _winSize;
        Scene *_runningScene = nullptr;
        Renderer *_renderer = nullptr;
        long _lastTimeStamp = 0;
        float _realFps = 0.0f;
        static Director *_instance;
        Scheduler *_globalScheduler = nullptr;
        std::map<std::string, Scheduler*> _schedulers;
        std::map<std::string, IMEDelegate*> _keyListeners;
        std::map<std::string, TouchDelegate*> _touchListeners;
    };

}

#endif /* Director_hpp */
