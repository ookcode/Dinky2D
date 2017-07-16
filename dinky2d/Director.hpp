//
//  Director.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef Director_hpp
#define Director_hpp

#include <string>
#include "Scene.hpp"

namespace Dinky {
    
class Director {
public:
    static Director* getInstance();
    void mainloop();
    void runWithScene(Scene *scene);
    void setWinSize(float width, float height);
    glm::vec2 getWinSize() {
        return _winSize;
    }
private:
    Director() = default;
    ~Director() = default;
    Scene *_runningScene;
    glm::vec2 _winSize;
};

}

#endif /* Director_hpp */
