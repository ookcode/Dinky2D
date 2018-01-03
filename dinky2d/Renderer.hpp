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
    struct BatchCommand {
        RenderCommand *command;
        GLuint indexCount;
    };
    class Renderer {
    public:
        static const int VBO_SIZE = 65536;
        static const int INDEX_VBO_SIZE = VBO_SIZE * 6 / 4; // 每4个顶点有6个索引（两个三角形可复用2个顶点）
        
        void initGLView();
        void clear();
        void render();
        void addCommand(RenderCommand *command);
        
    private:
        void setupVBOAndVAO();
        Vertex _verts[VBO_SIZE]; // 每一帧的所有顶点的缓存
        GLuint _indices[INDEX_VBO_SIZE]; // 每一帧所有索引的缓存
        int _filledVertex; // 已经填充进_verts中的顶点数量
        int _filledIndex; // 已经填充进_indices中的索引数量
        GLuint _vao = 0;
        GLuint _vbo = 0;
        GLuint _ebo = 0;
        std::vector<RenderCommand *> _commands;
        std::vector<BatchCommand> _batchCommands;
    };
}

#endif /* Renderer_hpp */
