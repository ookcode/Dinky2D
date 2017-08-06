//
//  mainScene.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "MainScene.hpp"
#define MAIN_SCENE_TIMER_KEY "MAIN_SCENE_TIMER_KEY"
MainScene::MainScene() {
    glm::vec2 winSize = Director::getInstance()->getWinSize();

    Sprite* red = new Sprite("../dinky2d/resources/image.jpg");
    red->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
//    red->setOpacity(0.5f);
    red->setSize(glm::vec2(100.0f, 100.0f));
    red->setPosition(winSize / 2.0f);
    red->setRotation(30.0f);
    this->addChild(red);
    _sp = red;

    Sprite* green = new Sprite("../dinky2d/resources/image.jpg");
    green->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
    green->setSize(glm::vec2(100.0f, 100.0f));
    green->setAnchorPoint(glm::vec2(1.0f, 1.0f));
    green->setRotation(-30.0f);
    red->addChild(green);
    
    Sprite* blue = new Sprite("../dinky2d/resources/image.jpg");
    blue->setColor(glm::vec3(0.0f, 0.0f, 1.0f));
    blue->setSize(glm::vec2(100.0f, 100.0f));
    blue->setPosition(glm::vec2(100.0f, 0.0f));
    blue->setAnchorPoint(glm::vec2(0.0f, 0.0f));
    blue->setRotation(60.0f);
    green->addChild(blue);
    
    std::function<void(int)> callback = std::bind(&MainScene::update, this, std::placeholders::_1);
    Director::getInstance()->getScheduler()->schedule(callback, MAIN_SCENE_TIMER_KEY);
}

void MainScene::update(int dt) {
    _sp->setRotation(_sp->getRotation() + 1.0f);
}

MainScene::~MainScene() {
    Director::getInstance()->getScheduler()->unschedule(MAIN_SCENE_TIMER_KEY);
}
