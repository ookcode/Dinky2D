//
//  AppController.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/2.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "AppController.hpp"

#include <GLUT/GLUT.h>
#include "Director.hpp"

namespace Dinky {
    unsigned int AppController::_fps = 60;
    unsigned int AppController::_refreshInterval = 1000 / _fps;
    AppController* AppController::_instance = new AppController();
    AppController* AppController::createWindowAndGLView(int argc, char** argv, float width, float height) {
        // 初始化GLUT窗口
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_3_2_CORE_PROFILE);
        glutInitWindowPosition(500.0f, 100.0f);
        glutInitWindowSize(width, height);
        glutCreateWindow("Dinky2D");
        Director::getInstance()->setWinSize(width, height);
        return _instance;
    }
    
    void AppController::setFps(unsigned int fps) {
        _fps = fps;
        _refreshInterval = 1000 / fps;
    }
    
    void AppController::mainloop() {
        Director::getInstance()->mainloop();
        glutSwapBuffers();
    }
    
    void AppController::update(int value) {
        glutPostRedisplay();
        glutTimerFunc(_refreshInterval, update, 0);
    }
    
    void AppController::startup() {
        glutDisplayFunc(&AppController::mainloop);
        glutTimerFunc(_refreshInterval, &AppController::update, 0);
        glutMainLoop();
    }
}
