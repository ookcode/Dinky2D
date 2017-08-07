//
//  Scene.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include "Node.hpp"

namespace Dinky {
    
    class Scene: public Node {
    public:
        Scene();
        virtual ~Scene() override;
        void render(Renderer* renderer);
    };
    
}

#endif /* Scene_hpp */
