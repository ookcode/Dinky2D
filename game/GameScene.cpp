//
//  GameScene.cpp
//  dinky2d
//
//  Created by vincent on 2017/8/17.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "GameScene.hpp"

#include<ctime>
#define NODE_LEN 20.0f
#define LOST_WORD "胜败乃兵家常事, 少侠请重新来过"
GameScene::GameScene() {
    init();
}

void GameScene::init() {
    glm::vec2 winSize = Director::getInstance()->getWinSize();
    
    _tileWidth = winSize.x / NODE_LEN;
    _tileHeight = winSize.y / NODE_LEN;
    
    _speed = 10;
    
    gameLayer = new Layer(winSize.x, winSize.y, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    this->addChild(gameLayer);
    
    _snakeA = new Snake();
    _snakeA->add(15, 3);
    _snakeA->add(15, 4);
    _snakeA->add(15, 5);
    
    _snakeB = new Snake();
    _snakeB->add(3, 3);
    _snakeB->add(3, 4);
    _snakeB->add(3, 5);
    
    genFruit();
    
    _tips = new Label("", 20);
    _tips->setPosition(winSize / 2.0f);
    _tips->setVisible(false);
    this->addChild(_tips);
    
    _scoreLbl = new Label("", 48);
    _scoreLbl->setAnchorPoint(glm::vec2(1.0f, 1.0f));
    _scoreLbl->setPosition(winSize - glm::vec2(20.0f, 20.0f));
    this->addChild(_scoreLbl);
    
    updateScoreLbl();
    this->schedule(SCHEDULE(GameScene::update));
    Director::getInstance()->registerKeyboardDelegate(this);
}

void GameScene::onKeyUp(int key, bool isSpecialKey) {
    printf("onKeyUp %d, %d\n", key, isSpecialKey);
    if (_isGameOver) {
        Director::getInstance()->runWithScene(new GameScene());
        return;
    }
    if (isSpecialKey) {
        switch (key) {
            case 101: // ↑
                _directionA = DIRECTION::UP;
                break;
            case 103: // ↓
                _directionA = DIRECTION::DOWN;
                break;
            case 100: // ←
                _directionA = DIRECTION::LEFT;
                break;
            case 102: // →
                _directionA = DIRECTION::RIGHT;
                break;
            default:
                break;
        }
    } else {
        switch (key) {
            case 119: // W
                _directionB = DIRECTION::UP;
                break;
            case 115: // S
                _directionB = DIRECTION::DOWN;
                break;
            case 97: // A
                _directionB = DIRECTION::LEFT;
                break;
            case 100: // D
                _directionB = DIRECTION::RIGHT;
                break;
            default:
                break;
        }
    }
    if (_directionA == DIRECTION::NONE) {
        _directionA = _directionB;
    } else if(_directionB == DIRECTION::NONE) {
        _directionB = _directionA;
    }
}

void GameScene::onKeyDown(int key, bool isSpecialKey) {
    //    printf("onKeyDown %d\n", key);
}

void GameScene::genFruit() {
    srand((int)time(NULL));
    int x = rand()%_tileWidth;
    srand((int)time(NULL));
    int y = rand()%_tileHeight;
    _fruit = glm::vec2(x, y);
}

void GameScene::updateScoreLbl() {
    _scoreLbl->setText(std::to_string(_score));
}

void GameScene::update(float dt) {
    if (++_timeCount != _speed) {
        return;
    }
    _timeCount = 0;
    int headAX = (*_snakeA->begin())->x;
    int headAY = (*_snakeA->begin())->y;
    int headBX = (*_snakeB->begin())->x;
    int headBY = (*_snakeB->begin())->y;
    if (headAX >= _tileWidth || headAX < 0 || headAY >= _tileHeight || headAY < 0 ||
        headBX >= _tileWidth || headBX < 0 || headBY >= _tileHeight || headBY < 0) {
        this->unschedule(SCHEDULE(GameScene::update));
        _isGameOver = true;
        _tips->setText(LOST_WORD);
        _tips->setVisible(true);
        return;
    }
    if (headAX == _fruit.x && headAY == _fruit.y) {
        _snakeA->move(_directionA, true);
        _score++;
        updateScoreLbl();
        genFruit();
    } else {
        _snakeA->move(_directionA, false);
    }
    
    if (headBX == _fruit.x && headBY == _fruit.y) {
        _snakeB->move(_directionB, true);
        _score++;
        updateScoreLbl();
        genFruit();
    } else {
        _snakeB->move(_directionB, false);
    }
    
    // clean
    gameLayer->removeAllChildren();
    
    // draw fruit
    Layer *fruit = new Layer(NODE_LEN - 3.0f, NODE_LEN - 3.0f, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    fruit->setAnchorPoint(glm::vec2(0.5f, 0.5f));
    fruit->setPosition(glm::vec2(_fruit.x * NODE_LEN + NODE_LEN / 2.0f, _fruit.y * NODE_LEN + NODE_LEN / 2.0f));
    gameLayer->addChild(fruit);
    
    // draw snake
    for (Snake::iterator iter = _snakeA->begin(); iter != _snakeA->end(); ++iter) {
        int x = (*iter)->x;
        int y = (*iter)->y;
        Layer *node = new Layer(NODE_LEN - 3.0f, NODE_LEN - 3.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        node->setAnchorPoint(glm::vec2(0.5f, 0.5f));
        node->setPosition(glm::vec2(x * NODE_LEN + NODE_LEN / 2.0f, y * NODE_LEN + NODE_LEN / 2.0f));
        gameLayer->addChild(node);
    }
    for (Snake::iterator iter = _snakeB->begin(); iter != _snakeB->end(); ++iter) {
        int x = (*iter)->x;
        int y = (*iter)->y;
        Layer *node = new Layer(NODE_LEN - 3.0f, NODE_LEN - 3.0f, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        node->setAnchorPoint(glm::vec2(0.5f, 0.5f));
        node->setPosition(glm::vec2(x * NODE_LEN + NODE_LEN / 2.0f, y * NODE_LEN + NODE_LEN / 2.0f));
        gameLayer->addChild(node);
    }
}

GameScene::~GameScene() {
    Director::getInstance()->unregisterKeyboardDelegate(this);
    this->unschedule(SCHEDULE(GameScene::update));
    delete _snakeA;
    _snakeA = nullptr;
}
