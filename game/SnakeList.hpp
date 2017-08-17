//
//  SnakeList.hpp
//  dinky2d
//
//  Created by vincent on 2017/8/17.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef SnakeList_hpp
#define SnakeList_hpp

#include <iostream>
class SnakeNode;
typedef std::shared_ptr<SnakeNode> Snode;

class SnakeNode {
public:
    SnakeNode(int _x, int _y):x(_x), y(_y){};
    int x;
    int y;
    Snode pre = nullptr;
    Snode next = nullptr;
};

class SnakeList {
public:
    void add(int x, int y);
    void removeTail();
    Snode getHead() {
        return _head;
    }
    Snode getTail() {
        return _tail;
    }
private:
    Snode _head = nullptr;
    Snode _tail = nullptr; // before tail
};

#endif /* SnakeList_hpp */
