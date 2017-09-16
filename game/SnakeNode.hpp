//
//  SnakeNode.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/9/15.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef SnakeNode_hpp
#define SnakeNode_hpp
#include <list>
#include "Sprite.hpp"
using namespace Dinky;

class SnakeNode : public Sprite {
public:
    SnakeNode(const std::string& file, glm::vec2 pos);
    virtual ~SnakeNode() override;
    void grow();
    void move(glm::vec2 pos);
    SnakeNode *next = nullptr;
    
private:
    // 最大路径数
    static int recordSize;
    // 路径列表
    std::list<glm::vec2> _points;
    
};

#endif /* SnakeNode_hpp */
