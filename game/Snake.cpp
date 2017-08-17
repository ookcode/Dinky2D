//
//  Snake.cpp
//  dinky2d
//
//  Created by vincent on 2017/8/17.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Snake.hpp"

void Snake::add(int x, int y) {
    _snakeList.add(x, y);
}

void Snake::move(DIRECTION direction, bool isGrow) {
    Snode head = _snakeList.getHead();
    int x = head->x;
    int y = head->y;
    switch (direction) {
        case DIRECTION::UP:
            y++;
            break;
        case DIRECTION::DOWN:
            y--;
            break;
        case DIRECTION::LEFT:
            x--;
            break;
        case DIRECTION::RIGHT:
            x++;
            break;
        default:
            return;
    }
    _snakeList.add(x, y);
    if (not isGrow) {
        _snakeList.removeTail();
    }
}

Snake::iterator Snake::begin() {
    return iterator(_snakeList.getHead());
}

Snake::iterator Snake::end() {
    return iterator(nullptr);
}
