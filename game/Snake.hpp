//
//  Snake.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/17.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef Snake_hpp
#define Snake_hpp

#include "SnakeNode.hpp"
#include "Helper.hpp"
using namespace Dinky;

// AI感应距离
#define AI_REACTION_DISTANCE 100.0f

class Snake {
public:
    // 颜色
    enum class Color {
        BLUE,
        GREEN,
        PINK,
        YELLOW
    };

    // 移动速度
    static float speed;
    
    Snake(Color color, glm::vec2 pos, Node *parent);
    ~Snake();
    
    void grow();
    void born();
    void die();
    void eat();
    
    glm::vec2 update(float inputRadians);
    void aiUpdate();
    void aiTurnAround();
    
    SnakeNode *getHead() {
        return _head;
    }
    bool isReborning() {
        return _isReborning;
    }
    std::string getImgPrefix() {
        return _imgPrefix;
    }
    int getScore() {
        return _score;
    }
    bool isProtected() {
        return _isProtected;
    }
    
private:
    void addProtect();
    void removeProtect();
    
    SnakeNode *_head = nullptr;
    Node *_parent = nullptr;
    float _currentRadians = 0.0f;
    float _aiTargetRadians = 0.0f;
    Color _color;
    glm::vec2 _bornPos;
    std::string _imgPrefix;
    bool _isReborning = false;
    bool _isProtected = false;
    int _score = 0;
    int _eatCount = 0;
    int _length = 0;
    int _protectedCD = 0;
    int _aiTurnAroundCD = 0;
    Sprite *_protectMask = nullptr;
};

#endif /* Snake_hpp */
