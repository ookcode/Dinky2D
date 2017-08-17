//
//  GameScene.hpp
//  dinky2d
//
//  Created by vincent on 2017/8/17.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "Dinky2D.h"
#include "IMEDelegate.h"
#include "Snake.hpp"
using namespace Dinky;

class GameScene: public Scene, public IMEDelegate {
public:
    GameScene();
    ~GameScene();
    void update(float dt);
    void updateScoreLbl();
    virtual void onKeyDown(int key, bool isSpecialKey) override;
    virtual void onKeyUp(int key, bool isSpecialKey) override;
private:
    void init();
    void genFruit();
    Snake* _snakeA = nullptr;
    Snake* _snakeB = nullptr;
    int _tileWidth = 0;
    int _tileHeight = 0;
    int _timeCount = 0;
    int _speed = 0; // x帧走1格
    int _score = 0; // 分数
    Layer *gameLayer = nullptr;
    Label *_tips = nullptr;
    Label *_scoreLbl = nullptr;
    bool _isGameOver = false;
    glm::vec2 _fruit;
    DIRECTION _directionA = DIRECTION::NONE;
    DIRECTION _directionB = DIRECTION::NONE;
};

#endif /* GameScene_hpp */
