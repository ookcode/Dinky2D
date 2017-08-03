//
//  Renderer.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/2.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <vector>
#include "RenderCommand.hpp"

namespace Dinky {
    class Renderer {
    public:
        void initGLView();
        void clear();
        void render();
        void addCommand(RenderCommand *command);
        
    private:
        void setupVBOAndVAO();
        GLuint _vao = 0;
        GLuint _vbo = 0;
        GLuint _ebo = 0;
        std::vector<RenderCommand *> _commands;
    };
}

#endif /* Renderer_hpp */
