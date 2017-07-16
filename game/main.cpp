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
    float width = 512.0f;
    float height = 512.0f;
    Window window(argc, argv, width, height);
    
    MainScene* mainScene = new MainScene();
    mainScene->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    Director::getInstance()->runWithScene(mainScene);
    
    window.show();
    return 0;
}
