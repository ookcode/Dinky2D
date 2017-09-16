//
//  mainScene.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef mainScene_hpp
#define mainScene_hpp

#include "Dinky2D.h"
#include "Snake.hpp"
#define MAX_SNAKE 4

using namespace Dinky;

class MainScene: public Scene, public IMEDelegate, public TouchDelegate {
public:
    enum class Status {
        PLAYING,
        END
    };
    MainScene();
    ~MainScene();
    void update(float dt);
    virtual void onKeyDown(int key, bool isSpecialKey) override;
    virtual void onKeyUp(int key, bool isSpecialKey) override;
    virtual void onTouchBegin(int x, int y) override;
    virtual void onTouchMove(int x, int y) override;
    virtual void onTouchEnded(int x, int y) override;
    
private:
    bool wallCollisionCheck(int id, glm::vec2 pos);
    bool snakeCollisionCheck(int id, glm::vec2 pos);
    void fruitCollisionCheck(int id, glm::vec2 pos);
    void genFruit(Snake *snake);
    
    Sprite *_input = nullptr;
    Sprite *_inputBall = nullptr;
    Layer *_mask = nullptr;
    Label *_tips = nullptr;
    Node *_background = nullptr;
    Node *_fruitLayer = nullptr;
    std::vector<Snake::Color> _colors;
    std::vector<std::string> _names;
    std::vector<glm::vec3> _nameColors;
    float _inputRadians = 0.0f;
    Status _gameStatus = Status::END;
    glm::vec2 _beginPoint;
    int _reborning = 0;
    std::map<int, Snake*> _snakes;
    std::map<int, int> _rebornCounts;
    std::vector<Label *> _scores;
};

#endif /* mainScene_hpp */
