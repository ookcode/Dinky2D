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
    
    void AppController::mainloop() {
        Director::getInstance()->mainloop();
        glutSwapBuffers();
    }
    
    void AppController::update(int value) {
        glutPostRedisplay();
        glutTimerFunc(1, update, 1);
    }
    
    void AppController::startup() {
        glutDisplayFunc(&AppController::mainloop);
        glutTimerFunc(1, &AppController::update, 1);
        glutMainLoop();
    }
}
