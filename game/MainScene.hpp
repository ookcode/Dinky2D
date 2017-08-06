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
using namespace Dinky;

class MainScene: public Scene {
public:
    MainScene();
    ~MainScene();
    void update(int dt);
    
private:
    Sprite* _sp = nullptr;
};

#endif /* mainScene_hpp */
