//
//  Helper.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/9/14.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Helper.hpp"

glm::vec2 Helper::mapSize = glm::vec2(TILE_SIZE * X_TILE_COUNT, TILE_SIZE * Y_TILE_COUNT);
glm::vec2 Helper::winSize = glm::vec2(0.0f, 0.0f);
int Helper::gridXSize = 1 + mapSize.x / GRID_SIZE;

int Helper::getGridID(glm::vec2 pos) {
    int x = pos.x / GRID_SIZE;
    int y = pos.y / GRID_SIZE;
    int id = x + y * gridXSize;
    return id;
}

float Helper::getDistance(glm::vec2 posA, glm::vec2 posB) {
    float diffX = posA.x - posB.x;
    float diffY = posA.y - posB.y;
    float distance = sqrtf(diffX * diffX + diffY * diffY);
    return distance;
}
