//
//  Sprite.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <string>
#include "Node.hpp"

namespace Dinky {
    
    class Sprite : public Node {
    public:
        Sprite(const std::string& filePath);
        ~Sprite();
        void draw();
        
    private:
        GLuint _texture = 0;
    };
    
    
}

#endif /* Sprite_hpp */
