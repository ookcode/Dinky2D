//
//  SnakeList.cpp
//  dinky2d
//
//  Created by vincent on 2017/8/17.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "SnakeList.hpp"

void SnakeList::add(int x, int y) {
    Snode node = std::make_shared<SnakeNode>(x, y);
    if (_head == nullptr) {
        _head = node;
        _tail = _head;
    } else {
        _head->pre = node;
        node->next = _head;
        _head = node;
    }
}

void SnakeList::removeTail() {
    if (_tail && _tail->pre) {
        auto pre = _tail->pre;
        pre->next = nullptr;
        _tail->pre = nullptr;
        _tail = pre;
    } else {
        _head = nullptr;
        _tail = nullptr;
    }
}
