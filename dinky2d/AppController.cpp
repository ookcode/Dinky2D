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
    int AppController::_pressedKey = 0;
    float AppController::_width = 0.0f;
    float AppController::_height = 0.0f;
    AppController* AppController::_instance = new AppController();
    AppController* AppController::createWindowAndGLView(int argc, char** argv, float width, float height) {
        // 初始化GLUT窗口
        _width = width;
        _height = height;
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
    
    void AppController::onSpecialKeyDown(int key, int x, int y) {
        if (key != _pressedKey) {
            Director::getInstance()->onKeyDown(key, true);
            _pressedKey = key;
        }
    }
    
    void AppController::onSpecialKeyUp(int key, int x, int y) {
        Director::getInstance()->onKeyUp(key, true);
        _pressedKey = 0;
    }
    
    void AppController::onKeyDown(unsigned char key, int x, int y) {
        if (key != _pressedKey) {
            Director::getInstance()->onKeyDown(key, false);
            _pressedKey = key;
        }
    }
    
    void AppController::onKeyUp(unsigned char key, int x, int y) {
        Director::getInstance()->onKeyUp(key, false);
        _pressedKey = 0;
    }
    
    void AppController::onMouseClickEvent(int button, int state, int x, int y) {
        y = _height - y;
        if(button == GLUT_LEFT_BUTTON) {
            if(state == GLUT_DOWN) {
                Director::getInstance()->onTouchBegin(x, y);
            } else if(state == GLUT_UP) {
                Director::getInstance()->onTouchEnded(x, y);
            }
        }
    }
    
    void AppController::onMouseMoveEvent(int x, int y) {
        y = _height - y;
        Director::getInstance()->onTouchMove(x, y);
    }
    
    void AppController::startup() {
        glutDisplayFunc(&AppController::mainloop);
        glutTimerFunc(_refreshInterval, &AppController::update, 0);
        glutSpecialFunc(&AppController::onSpecialKeyDown);
        glutSpecialUpFunc(&AppController::onSpecialKeyUp);
        glutKeyboardFunc(&AppController::onKeyDown);
        glutKeyboardUpFunc(&AppController::onKeyUp);
        glutMouseFunc(&AppController::onMouseClickEvent);
        glutMotionFunc(&AppController::onMouseMoveEvent);
        glutMainLoop();
    }
}
