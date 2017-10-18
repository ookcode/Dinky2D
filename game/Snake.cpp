//
//  Snake.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/17.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Snake.hpp"
float Snake::speed = 6.0f;

#define AITurnAroundCD 180 // AI掉头CD
#define INIT_LENGTH 4 // 初始蛇身长度
#define PROTECTED_TIME_COUNT 60 // 无敌时间

Snake::Snake(Color color, glm::vec2 pos, Node *parent) {
    _color = color;
    srand((unsigned)time(0));
    _parent = parent;
    _bornPos = pos;
    born();
}

Snake::~Snake() {
    die();
}

void Snake::born() {
    _aiTurnAroundCD = AITurnAroundCD;
    _isReborning = false;
    switch (_color) {
        case Color::BLUE:
            _imgPrefix = "../game/res/snake/snk_b";
            break;
        case Color::GREEN:
            _imgPrefix = "../game/res/snake/snk_g";
            break;
        case Color::PINK:
            _imgPrefix = "../game/res/snake/snk_p";
            break;
        case Color::YELLOW:
            _imgPrefix = "../game/res/snake/snk_y";
            break;
    }
    _head = new SnakeNode(_imgPrefix + "1.png", _bornPos);
    _head->setRotation(-90.0f);
    _parent->addChild(_head);
    
    addProtect();
    
    for (int i = 0; i < INIT_LENGTH; ++i) {
        grow();
    }
}

void Snake::addProtect() {
    if (_protectMask) {
        removeProtect();
    }
    _protectMask = new Sprite("../game/res/snake/protected.png");
    _protectMask->setPosition(_head->getSize() / 2.0f);
    _head->addChild(_protectMask);
    _isProtected = true;
}

void Snake::removeProtect() {
    if (_protectMask) {
        _protectMask->removeFromParent();
        _protectMask = nullptr;
    }
    _protectedCD = 0;
    _isProtected = false;
}

void Snake::die() {
    _isReborning = true;
    _head->removeFromParent();
    _head = nullptr;
    _length = 0;
    _eatCount = 0;
    removeProtect();
}

void Snake::eat() {
    ++_score;
    ++_eatCount;
    if (_eatCount >= 3) {
        _eatCount = 0;
        grow();
    }
}

void Snake::grow() {
    SnakeNode *node = _head;
    while (node->next) {
        node = node->next;
    }
    glm::vec2 nextPos = glm::vec2(node->getPositionX(), node->getPositionY());
    SnakeNode *body = new SnakeNode(_imgPrefix + "2.png", nextPos);
    node->next = body;
    _parent->addChild(body);
    ++_length;
}

glm::vec2 Snake::update(float inputRadians) {
    if (_protectedCD < PROTECTED_TIME_COUNT) {
        ++_protectedCD;
    } else {
        removeProtect();
    }
    // 平滑旋转
    float speed = Snake::speed / 20.0f;
    float clockWiseDiff = inputRadians - _currentRadians;
    if(fabsf(clockWiseDiff) > speed) {
        if(clockWiseDiff < 0) clockWiseDiff += M_PI * 2;
        if(clockWiseDiff <= M_PI) {
            if(_currentRadians + speed >= M_PI * 2) _currentRadians = 0;
            _currentRadians += speed;
        } else {
            if(_currentRadians - speed <= 0.0f) _currentRadians = M_PI * 2;
            _currentRadians -= speed;
        }
    }
    
    // 执行旋转和移动操作
    float degrees = _currentRadians * (180.0f / M_PI);
    getHead()->setRotation(degrees - 90.0f);
    float x = sinf(_currentRadians) * Snake::speed;
    float y = cosf(_currentRadians) * Snake::speed;
    
    glm::vec2 snakePos = _head->getPosition() + glm::vec2(x, y);
    _head->move(snakePos);
    
    return glm::vec2(x, y);
}

void Snake::aiUpdate() {
    if (_aiTurnAroundCD < AITurnAroundCD) {
        _aiTurnAroundCD++;
    } else if(rand() % 100 == 0) {
        _aiTargetRadians = rand() % 628 / 100.0f;
    }
    update(_aiTargetRadians);
}

void Snake::aiTurnAround() {
    if (_aiTurnAroundCD < AITurnAroundCD) {
        return;
    }
    _aiTurnAroundCD = 0;
    if (_currentRadians > M_PI) {
        _aiTargetRadians = _currentRadians - M_PI;
    } else {
        _aiTargetRadians = _currentRadians + M_PI;
    }
    aiUpdate();
}
