//
//  mainScene.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "MainScene.hpp"
#include <math.h>
#include "Helper.hpp"
// 当前玩家ID
#define PLAYER_ID 0

MainScene::MainScene() {
    Helper::winSize = Dinky::Director::getInstance()->getWinSize();
    
    _colors = {Snake::Color::BLUE,Snake::Color::YELLOW,Snake::Color::PINK,Snake::Color::GREEN};
    _nameColors = {glm::vec3(0.0, 0.72, 0.93),glm::vec3(1.0, 1.0, 0.0),glm::vec3(0.92, 0.4, 0.47),glm::vec3(0.2, 0.69, 0.42)};
    _names = {"蓝色小蛇", "黄色小蛇", "红色小蛇", "绿色小蛇"};

    _background = new Node();
    this->addChild(_background);
    
    for (int j = 0; j < X_TILE_COUNT / 2; ++j) {
        for (int i = 0; i < X_TILE_COUNT; ++i) {
            Sprite *background = new Sprite("../game/res/background.png");
            background->setAnchorPoint(glm::vec2(0.0f, 0.0f));
            background->setSize(glm::vec2(TILE_SIZE, TILE_SIZE));
            background->setPosition(glm::vec2(i * TILE_SIZE, j * TILE_SIZE));
            _background->addChild(background);
        }
    }
    
    _fruitLayer = new Node();
    _background->addChild(_fruitLayer);
    
    _input = new Sprite("../game/res/input/movbg.png");
    _input->setSize(glm::vec2(150.0f, 150.0f));
    _input->setVisible(false);
    this->addChild(_input);
    
    _inputBall = new Sprite("../game/res/input/movball.png");
    _inputBall->setSize(glm::vec2(58.0f, 58.0f));
    _inputBall->setPosition(_input->getSize() / 2.0f);
    _input->addChild(_inputBall);
    
    for (int i = 0; i < 4; ++i) {
        Snake *snake = new Snake(_colors.at(i), Helper::winSize / 2.0f + glm::vec2(200.0f * i, 0.0f), _background);
        _snakes[i] = snake;
        _rebornCounts[i] = 0;
        
        Label *score = new Label("", 20);
        score->setAnchorPoint(glm::vec2(0.0f, 0.5f));
        score->setColor(_nameColors.at(i));
        score->setPosition(glm::vec2(Helper::winSize.x - 140, Helper::winSize.y - 30 * i - 30));
        _scores.push_back(score);
        this->addChild(score);
    }

    _mask = new Layer(Helper::winSize.x, Helper::winSize.y, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    _mask->setVisible(false);
    this->addChild(_mask);
    
    _tips = new Label(END_WORDS, 20);
    _tips->setPosition(Helper::winSize / 2.0f);
    _mask->addChild(_tips);
    
    this->schedule(SCHEDULE(MainScene::update));
    Director::getInstance()->registerKeyboardDelegate(this);
    Director::getInstance()->registerTouchDelegate(this);
    
    _gameStatus = Status::PLAYING;
}

void MainScene::onKeyUp(int key, bool isSpecialKey) {
    printf("onKeyUp %d\n", key);
}

void MainScene::onKeyDown(int key, bool isSpecialKey) {
    printf("onKeyDown %d\n", key);
    _inputRadians = rand() % 314 / 100.0f;
}

void MainScene::onTouchBegin(int x, int y) {
    if (_gameStatus != Status::PLAYING) {
        return;
    }
    _beginPoint = glm::vec2(x, y);
    _input->setPosition(glm::vec2(x, y));
    _input->setVisible(true);
}

void MainScene::onTouchMove(int posX, int posY) {
    if (_gameStatus != Status::PLAYING) {
        return;
    }
    float x = posX - _beginPoint.x;
    float y = posY - _beginPoint.y;
    if(y == 0) y = 0.001f;
    if(x == 0) x = 0.001f;
    float radians = atanf((float)x / y);
    if(y < 0) {
        radians += M_PI;
    } else if(x < 0) {
        radians += M_PI * 2;
    }
    _inputRadians = radians;
    
    float distance = sqrtf(x * x + y * y);
    if(distance > 60.0f) distance = 60.0f;
    _inputBall->setPosition(_input->getSize() / 2.0f + glm::vec2(sinf(radians) * distance, cosf(radians) * distance));
}

void MainScene::onTouchEnded(int x, int y) {
    _input->setVisible(false);
}

void MainScene::update(float dt) {
    for (int i = 0; i < _snakes.size(); ++i) {
        Snake *snake = _snakes.at(i);
        _scores.at(i)->setText(_names.at(i) + "+" + std::to_string(snake->getScore()));
    }
    if (_gameStatus != Status::PLAYING) {
        float opacity = _mask->getOpacity();
        if(_mask->isVisible() && opacity <= 1.0f) {
            _mask->setOpacity(opacity + 0.01f);
        }
        return;
    }
    
    // 移动
    for (auto iter = _snakes.begin(); iter != _snakes.end(); ++iter) {
        Snake *snake = iter->second;
        int id = iter->first;
        if (snake->isReborning()) {
            _rebornCounts[id] ++;
            if(_rebornCounts[id] > REBORN_TIME_COUNT) {
                _rebornCounts[id] = 0;
                snake->born();
                if (iter->first == PLAYER_ID) {
                    _inputRadians = 0.0f;
                    _background->setPosition(glm::vec2(0.0f, 0.0f));
                }
            }
            continue;
        }
        if (id == PLAYER_ID) {
            glm::vec2 movePos = snake->update(_inputRadians);
            glm::vec2 mapPos = _background->getPosition() - movePos;
            _background->setPosition(mapPos);
        } else {
            glm::vec2 pos = snake->getHead()->getPosition();
            float snakeLeft = pos.x - AI_REACTION_DISTANCE;
            float snakeRight = pos.x + AI_REACTION_DISTANCE;
            float snakeBottom = pos.y - AI_REACTION_DISTANCE;
            float snakeTop = pos.y + AI_REACTION_DISTANCE;
            if (snakeLeft < 0.0f || snakeRight > Helper::mapSize.x || snakeBottom < 0.0f || snakeTop > Helper::mapSize.y) {
                snake->aiTurnAround();
            }
            snake->aiUpdate();
        }
    }
    // 碰撞检测
    for (auto iter = _snakes.begin(); iter != _snakes.end(); ++iter) {
        Snake *snake = iter->second;
        if (snake->isReborning()) {
            continue;
        }
        glm::vec2 pos = snake->getHead()->getPosition();
        if (wallCollisionCheck(iter->first, pos)) {
            continue;
        }
        if (snakeCollisionCheck(iter->first, pos)) {
            continue;
        }
        fruitCollisionCheck(iter->first, pos);
    }
}

bool MainScene::snakeCollisionCheck(int id, glm::vec2 pos) {
    Snake *target = _snakes.at(id);
    if (target->isProtected()) {
        return false;
    }
    for (auto iter = _snakes.begin(); iter != _snakes.end(); ++iter) {
        Snake *snake = iter->second;
        if (iter->first == id || snake->isReborning()) {
            continue;
        }
        SnakeNode *node = snake->getHead();
        int index = 0;
        while (node) {
            float distance = Helper::getDistance(pos, node->getPosition());
            if (distance <= SNAKE_SIZE / 2) {
                printf("Snake %d hit snake %d at %d\n", id, iter->first, index);
                genFruit(target);
                target->die();
                return true;
            }
            index++;
            node = node->next;
        }
        
    }
    return false;
}

bool MainScene::wallCollisionCheck(int id, glm::vec2 pos) {
    Snake *snake = _snakes[id];
    glm::vec2 snakeSize = snake->getHead()->getSize();
    float snakeLeft = pos.x - snakeSize.x / 2.0f;
    float snakeRight = pos.x + snakeSize.x / 2.0f;
    float snakeBottom = pos.y - snakeSize.x / 2.0f;
    float snakeTop = pos.y + snakeSize.x / 2.0f;
    if (snakeLeft < 0.0f || snakeRight > Helper::mapSize.x || snakeBottom < 0.0f || snakeTop > Helper::mapSize.y) {
        genFruit(snake);
        snake->die();
        printf("Snake %d hit the wall\n", id);
        return true;
    }
    return false;
}

void MainScene::fruitCollisionCheck(int id, glm::vec2 pos) {
    Snake *target = _snakes.at(id);
    int gridId = Helper::getGridID(pos);
    std::vector<Node *> children = _fruitLayer->getChildren();
    for (int i = 0; i < children.size();) {
        Node *fruit = children.at(i);
        int tag = fruit->getTag();
        if (tag == gridId) {
            _fruitLayer->removeChild(i);
            children.erase(children.begin() + i);
            target->eat();
        } else {
            ++i;
        }
    }
}

void MainScene::genFruit(Snake *snake) {
    SnakeNode *node = snake->getHead();
    std::string img = snake->getImgPrefix() + "2.png";
    while (node->next) {
        node = node->next;
        for (int i = 0; i < 2; ++i) {
            int randX = rand() % SNAKE_SIZE - SNAKE_SIZE / 2;
            int randY = rand() % SNAKE_SIZE - SNAKE_SIZE / 2;
            glm::vec2 pos = node->getPosition() + glm::vec2(randX, randY);
            Sprite *fruit = new Sprite(img);
            fruit->setSize(glm::vec2(20.0f, 20.0f));
            fruit->setPosition(pos);
            int gridId = Helper::getGridID(pos);
            fruit->setTag(gridId);
            _fruitLayer->addChild(fruit);
        }
    }
}

MainScene::~MainScene() {
    Director::getInstance()->unregisterKeyboardDelegate(this);
    this->unschedule(SCHEDULE(MainScene::update));
}
