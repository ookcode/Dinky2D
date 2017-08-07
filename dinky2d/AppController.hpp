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
        static void mainloop();
        static AppController* _instance;
        
        static unsigned int _fps;
        static unsigned int _refreshInterval;
    };
}

#endif /* AppController_hpp */
