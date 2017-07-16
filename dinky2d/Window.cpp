//
//  Window.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Window.hpp"
#include <OpenGl/gl3.h>
#include <GLUT/GLUT.h>
#include "Director.hpp"

namespace Dinky {
    
    Window::Window(int argc, char** argv, float width, float height) {
        // 初始化GLUT窗口
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_3_2_CORE_PROFILE);
        glutInitWindowPosition(500.0f, 100.0f);
        glutInitWindowSize(width, height);
        glutCreateWindow("Dinky2D");
        Director::getInstance()->setWinSize(width, height);
        glutDisplayFunc(&Window::mainloop);
        glutTimerFunc(1, &Window::update, 1);
    }
    
    Window::~Window() {
        
    }
    
    void Window::mainloop() {
        // 清除窗口
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        Director::getInstance()->mainloop();
        
        // 强制刷新缓冲，显示图形
        glutSwapBuffers();
    }
    
    void Window::update(int value) {
        glutPostRedisplay();
        glutTimerFunc(1, update, 1);
    }

    void Window::show() {
        // 开始执行
        glutMainLoop();
    }

}
