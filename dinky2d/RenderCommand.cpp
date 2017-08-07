//
//  RenderCommand.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/2.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "RenderCommand.hpp"
#include "Director.hpp"

namespace Dinky {
    RenderCommand::RenderCommand(Program *program, glm::mat4& transform, Triangles& triangles)
    :_program(program),
    _transform(transform),
    _triangles(triangles) {
        
    }
    
    void RenderCommand::setTexture(GLuint texture){
        _texture = texture;
    }
    
    void RenderCommand::setColor(glm::vec3 &color, float opacity) {
        _color = glm::vec4(color, opacity);
    }
    
    void RenderCommand::useMaterial() {
        // 激活纹理
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _texture);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        _program->use();
        
        // 正射投影{左边界，右边界，下边界，上边界}
        glm::vec2 winSize = Director::getInstance()->getWinSize();
        glm::mat4 projection = glm::ortho(0.0f, winSize.x, 0.0f, winSize.y, -1.0f, 1.0f);
        glUniformMatrix4fv(_program->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
        // 颜色
        glUniform4fv(_program->getUniformLocation("fragColor"), 1, glm::value_ptr(_color));
    }
}
