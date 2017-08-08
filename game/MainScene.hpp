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
#include "IMEDelegate.h"
using namespace Dinky;

class MainScene: public Scene, public IMEDelegate {
public:
    MainScene();
    ~MainScene();
    void update(float dt);
    virtual void onKeyDown(int key) override;
    virtual void onKeyUp(int key) override;
private:
    Sprite* _sp = nullptr;
};

#endif /* mainScene_hpp */
