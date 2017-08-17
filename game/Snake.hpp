//
//  Snake.hpp
//  dinky2d
//
//  Created by vincent on 2017/8/17.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef Snake_hpp
#define Snake_hpp

#include "SnakeList.hpp"

enum class DIRECTION {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

template<typename T>
class Iterator {
public:
    Iterator(T ptr) {
        _ptr = ptr;
    }
    T& operator*(){
        return _ptr;
    }
    bool operator!=(const Iterator &s) {
        return s._ptr != _ptr;
    }
    bool operator==(const Iterator &s) {
        return s._ptr == _ptr;
    }
    Iterator& operator++(){
        _ptr = _ptr->next;
        return *this;
    }
private:
    T _ptr;
};

class Snake {
public:
    typedef Iterator<Snode> iterator;
    iterator begin();
    iterator end();
    void add(int x, int y);
    void move(DIRECTION direction, bool isGrow);
    
private:
    SnakeList _snakeList;
};

#endif /* Snake_hpp */
