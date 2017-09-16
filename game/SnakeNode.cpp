//
//  SnakeNode.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/9/15.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "SnakeNode.hpp"
#include "Snake.hpp"
int SnakeNode::recordSize = SNAKE_SIZE / Snake::speed;

SnakeNode::SnakeNode(const std::string& file, glm::vec2 pos):Sprite(file) {
    setPosition(pos);
}

SnakeNode::~SnakeNode() {
    if (next) {
        next->removeFromParent();
    }
}

void SnakeNode::move(glm::vec2 pos) {
    setPosition(pos);
    if (next) {
        _points.push_back(pos);
        if (_points.size() >= recordSize) {
            glm::vec2 point = _points.front();
            _points.pop_front();
            next->setPosition(point);
            next->move(point);
        }
    }
}
