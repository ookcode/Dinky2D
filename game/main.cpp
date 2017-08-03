//
//  main.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/15.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Dinky2D.h"
#include "MainScene.hpp"
using namespace Dinky;

int main(int argc, char** argv){
    float width = 568.0f;
    float height = 320.0f;
    AppController* app = AppController::createWindowAndGLView(argc, argv, width, height);
    Director::getInstance()->setOpenGLView();
    MainScene* mainScene = new MainScene();
    Director::getInstance()->runWithScene(mainScene);
    app->startup();
    return 0;
}
