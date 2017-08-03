//
//  Sprite.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Sprite.hpp"

namespace Dinky {
    
    Sprite::Sprite(const std::string& filePath) {
        _texture = TextureCache::getInstance()->getTexture(filePath);
    }

    Sprite::~Sprite() {
    }
    
    void Sprite::draw(Renderer* renderer, glm::mat4 &parentTransform) {
        if(_texture) {
            RenderCommand* command = new RenderCommand(getProgram(), parentTransform);
            command->setTexture(_texture->getObject());
            command->setColor(getColor());
            command->setSize(getSize());
            renderer->addCommand(command);
        }
    }
}
