//
//  Renderer.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/2.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Renderer.hpp"
#include "Director.hpp"

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
        
        // 设置顶点信息
        // 顶点信息是以屏幕中心为原点，范围为-1 ~ 1
        GLfloat vertex_data[] = {
            //  X     Y     Z
            -0.5f,  -0.5f,  0.0f,   0.0f,   0.0f,
            0.5f,   -0.5f,  0.0f,   1.0f,   0.0f,
            0.5f,   0.5f,   0.0f,   1.0f,   1.0f,
            -0.5f,  0.5f,   0.0f,   0.0f,   1.0f,
        };
        
        // opengl均以三角形来绘制，如要绘制正方形则需指定两个三角形六个顶点
        // 因其中顶点存在重复，故可使用ebo来复用顶点
        // 索引信息，两个三角形的顶点分别为vbo中的索引项
        GLuint element_index[] = {
            0, 1, 2,
            2, 3, 0,
        };
        
        // 将顶点信息传递给VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
        
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element_index), element_index, GL_STATIC_DRAW);
        
        // 绑定顶点信息（attribute变量）
        glEnableVertexAttribArray(Program::VERTEX_ATTRIB_POSITION);
        glVertexAttribPointer(Program::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)0);
        
        // 绑定UV信息（attribute变量）
        glEnableVertexAttribArray(Program::VERTEX_ATTRIB_TEX_COORD);
        glVertexAttribPointer(Program::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(sizeof(GLfloat) * 3));
        
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
        for(auto iter = _commands.begin(); iter != _commands.end(); ++iter) {
            RenderCommand *command = (*iter);
            Program *program = command->getProgram();
            GLuint texture = command->getTexture();
            
            // 重新绑定 vao vbo ebo
            glBindVertexArray(_vao);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
            
            if(texture != 0) {
                // 激活纹理
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture);
            }
            
            program->use();
            
            // 正射投影
            glm::vec2 winSize = Director::getInstance()->getWinSize();
            // 左边界，右边界，下边界，上边界
            glm::mat4 projection = glm::ortho(0.0f, winSize.x, 0.0f, winSize.y, -1.0f, 1.0f);
            glUniformMatrix4fv(program->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
            
            // 颜色
            glUniform4fv(program->getUniformLocation("fragColor"), 1, glm::value_ptr(command->getColor()));

            // 节点的矩阵变换
            auto transform = glm::scale(command->getTransform(), glm::vec3(command->getSize(), 1.0f));
            glUniformMatrix4fv(program->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(transform));
            
            // 开始绘制
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            
            delete command;
        }
        _commands.clear();
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
    
}
