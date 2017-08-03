//
//  RenderCommand.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/2.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "RenderCommand.hpp"

namespace Dinky {
    RenderCommand::RenderCommand(Program *program, glm::mat4& transform)
    :_program(program),
    _transform(transform) {
        
    }
    
    void RenderCommand::setTexture(GLuint texture){
        _texture = texture;
    }
    
    void RenderCommand::setColor(glm::vec4 &color) {
        _color = color;
    }
    
    void RenderCommand::setSize(glm::vec2 &size) {
        _size = size;
    }
}
