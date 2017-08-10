//
//  Renderer.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/2.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Renderer.hpp"

namespace Dinky {
    void Renderer::initGLView() {
        setupVBOAndVAO();
    }
    
    void Renderer::setupVBOAndVAO() {
        // 绑定一个ID用于激活和删除VAO
        glGenVertexArrays(1, &_vao);
        // 设置当前vao为活动状态
        glBindVertexArray(_vao);
        
        // 绑定一个ID用于激活和删除vbo
        glGenBuffers(1, &_vbo);
        // 设置当前vbo为活动状态
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        
        // 绑定一个ID用于激活和删除ebo
        glGenBuffers(1, &_ebo);
        // 设置当前ebo为活动状态
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        
        // 将顶点信息传递给VBO
//        glBufferData(GL_ARRAY_BUFFER, sizeof(_verts[0]) * VBO_SIZE, _verts, GL_DYNAMIC_DRAW);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * INDEX_VBO_SIZE, _indices, GL_STATIC_DRAW);
        
        // 绑定顶点信息（attribute变量）
        glEnableVertexAttribArray(Program::VERTEX_ATTRIB_POSITION);
        glVertexAttribPointer(Program::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
        
        // 绑定UV信息（attribute变量）
        glEnableVertexAttribArray(Program::VERTEX_ATTRIB_TEX_COORD);
        glVertexAttribPointer(Program::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(sizeof(GLfloat) * 3));
        
        // 解绑vao,vbo,ebo
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
    void Renderer::addCommand(RenderCommand *command) {
        _commands.push_back(command);
    }
    
    void Renderer::clear() {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void Renderer::render() {
        if(_commands.empty()) {
            return;
        }
        
        _filledVertex = 0;
        _filledIndex = 0;
        int batchesTotal = 0;
        
        for(auto iter = _commands.begin(); iter != _commands.end(); ++iter) {
            RenderCommand *command = (*iter);
            
            Triangles& triangles = command->getTriangles();
            memcpy(&_verts[_filledVertex], triangles.verts, sizeof(Vertex) * triangles.vertCount);
            for(ssize_t i = 0; i < triangles.indexCount; ++i) {
                _indices[_filledIndex + i] = triangles.indices[i] + _filledVertex;
            }

            for(ssize_t i = 0; i < triangles.vertCount; ++i) {
                glm::vec3& vert = _verts[_filledVertex + i].vert;
                // 不要乘反了
                vert = command->getTransform() * glm::vec4(vert, 1.0f);
//                printf("%.2f, %.2f, %.2f\n", vert.x, vert.y, vert.z);
            }
            
            _filledVertex += triangles.vertCount;
            _filledIndex += triangles.indexCount;
            
            batchesTotal++;
        }
        // 重新绑定 vao vbo ebo
        glBindVertexArray(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        
        // 将顶点信息传递给VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(_verts[0]) * _filledVertex, _verts, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _filledIndex, _indices, GL_STATIC_DRAW);
        
        unsigned int offset = 0;
        // TODO:合并纹理相同的batchNode
        for(int i = 0; i != batchesTotal; ++i) {
            RenderCommand *command = _commands.at(i);
            command->useMaterial();
            Triangles& triangles = command->getTriangles();
            // 开始绘制
            glDrawElements(GL_TRIANGLES, triangles.indexCount, GL_UNSIGNED_INT, (void *)offset);
            offset += triangles.indexCount * sizeof(GLuint);
            delete command;
        }
        _commands.clear();
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
    
}
