//
//  mainScene.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "mainScene.hpp"

MainScene::MainScene() {
    glm::vec2 winSize = Director::getInstance()->getWinSize();
    
    Node * redBox = new Node();
    redBox->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    redBox->setSize(glm::vec2(100.0f, 100.0f));
    redBox->setPosition(winSize / 2.0f);
    this->addChild(redBox);
    
    Node * greenBox = new Node();
    greenBox->setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    greenBox->setSize(glm::vec2(50.0f, 50.0f));
    greenBox->setPosition(glm::vec2(0.0f, 0.0f));
    greenBox->setAnchor(glm::vec2(0.0f, 0.0f));
    redBox->addChild(greenBox);
    
    Node * blueBox = new Node();
    blueBox->setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    blueBox->setSize(glm::vec2(25.0f, 25.0f));
    blueBox->setPosition(glm::vec2(0.0f, 0.0f));
    blueBox->setAnchor(glm::vec2(0.0f, 0.0f));
    greenBox->addChild(blueBox);
}

MainScene::~MainScene() {
    
}
