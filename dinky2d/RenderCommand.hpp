//
//  RenderCommand.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/2.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef RenderCommand_hpp
#define RenderCommand_hpp

#include "Program.hpp"

namespace Dinky {
    class RenderCommand {
    public:
        RenderCommand(Program *program, glm::mat4& transform);
        Program* getProgram() {
            return _program;
        }
        
        void setTexture(GLuint texture);
        GLuint getTexture() {
            return _texture;
        }
        
        void setTransform(glm::mat4& transform);
        glm::mat4& getTransform() {
            return _transform;
        }
        
        void setColor(glm::vec4& color);
        glm::vec4& getColor() {
            return _color;
        }
        
        void setSize(glm::vec2& size);
        glm::vec2& getSize() {
            return _size;
        }
    private:
        Program *_program = nullptr;
        glm::mat4& _transform;
        glm::vec4 _color;
        glm::vec2 _size;
        GLuint _texture = 0;
    };
}

#endif /* RenderCommand_hpp */
