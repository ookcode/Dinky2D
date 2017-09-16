//
//  Helper.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/9/14.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef Helper_hpp
#define Helper_hpp

#include "Director.hpp"
#define END_WORDS "胜败乃兵家常事，少侠请重新来过！"
// 地图块大小
#define TILE_SIZE 76.0f
// 地图x轴格子数
#define X_TILE_COUNT 42
// 地图y轴格子数
#define Y_TILE_COUNT 21
// 网格格子大小
#define GRID_SIZE 64.0f;
// 复活耗时
#define REBORN_TIME_COUNT 60
// 蛇节点的大小
#define SNAKE_SIZE 32

class Helper {
public:
    // 获取坐标所在网格
    static int getGridID(glm::vec2 pos);
    // 计算两点间距离
    static float getDistance(glm::vec2 posA, glm::vec2 posB);
    // 地图大小
    static glm::vec2 mapSize;
    // 屏幕大小
    static glm::vec2 winSize;
    
private:
    // 网格x轴格子数
    static int gridXSize;
};
#endif /* Helper_hpp */
