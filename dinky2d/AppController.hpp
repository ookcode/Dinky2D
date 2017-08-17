//
//  AppController.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/2.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef AppController_hpp
#define AppController_hpp

namespace Dinky {
    class AppController {
    public:
        static AppController* createWindowAndGLView(int argc, char** argv, float width, float height);
        static void setFps(unsigned int fps);
        
        void startup();
        
    private:
        AppController() = default;
        static void update(int value);
        static void onSpecialKeyDown(int key,int x,int y);
        static void onSpecialKeyUp(int key, int x, int y);
        static void onKeyDown(unsigned char key,int x,int y);
        static void onKeyUp(unsigned char key, int x, int y);
        static void onMouseClickEvent(int button,int state,int x,int y);
        static void onMouseMoveEvent(int x, int y);
        static void mainloop();
        static AppController* _instance;
        static int _pressedKey;
        static unsigned int _fps;
        static unsigned int _refreshInterval;
    };
}

#endif /* AppController_hpp */
