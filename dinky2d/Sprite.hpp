//
//  Sprite.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include "Node.hpp"
#include "TextureCache.hpp"

namespace Dinky {
    
    class Sprite : public Node {
    public:
        Sprite(const std::string& filePath);
        ~Sprite();
        virtual void draw(Renderer* renderer, glm::mat4 &parentTransform) override;
        
    private:
        Texture* _texture = nullptr;
    };
    
    
}

#endif /* Sprite_hpp */
