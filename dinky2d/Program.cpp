//
//  Program.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/15.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Program.hpp"

namespace Dinky {

    Program::Program(const std::string& vertFile, const std::string& fragFile) {
        // 创建程序容器
        _object = glCreateProgram();
        
        // 绑定着色器与容器
        glAttachShader(_object, Shader::loadShader(vertFile, GL_VERTEX_SHADER).getObject());
        glAttachShader(_object, Shader::loadShader(fragFile, GL_FRAGMENT_SHADER).getObject());
        
        // 连接
        glLinkProgram(_object);
        
        // 连接检测
        GLint status;
        glGetProgramiv(_object, GL_LINK_STATUS, &status);
        if (status == GL_FALSE) {
            std::string msg("容器连接失败：");
            
            GLint infoLogLength;
            glGetProgramiv(_object, GL_INFO_LOG_LENGTH, &infoLogLength);
            char* strInfoLog = new char[infoLogLength + 1];
            glGetProgramInfoLog(_object, infoLogLength, NULL, strInfoLog);
            msg += strInfoLog;
            delete[] strInfoLog;
            
            glDeleteProgram(_object);
            _object = 0;
            throw std::runtime_error(msg);
        }

        // 绑定一个ID用于激活和删除VAO
        glGenVertexArrays(1, &_vao);
        // 设置当前vao为活动状态
        glBindVertexArray(_vao);
        
        // 绑定一个ID用于激活和删除vbo
        GLuint vbo;
        glGenBuffers(1, &vbo);
        // 设置当前vbo为活动状态
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        
        // 绑定一个ID用于激活和删除ebo
        GLuint ebo;
        glGenBuffers(1, &ebo);
        // 设置当前ebo为活动状态
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        
        // 设置顶点信息
        // 顶点信息是以屏幕中心为原点，范围为-1 ~ 1
        GLfloat vertexData[] = {
            //  X     Y     Z
            -0.5f,  -0.5f,  0.0f,
            0.5f,   -0.5f,  0.0f,
            0.5f,   0.5f,   0.0f,
            -0.5f,  0.5f,   0.0f,
        };
        
        // opengl均以三角形来绘制，如要绘制正方形则需指定两个三角形六个顶点
        // 因其中顶点存在重复，故可使用ebo来复用顶点
        // 索引信息，两个三角形的顶点分别为vbo中的索引项
        GLuint elementData[] = {
            0, 1, 2,
            2, 3, 0,
        };
        
        // 将顶点信息传递给VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
        
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementData), elementData, GL_STATIC_DRAW);
        
        // 绑定顶点信息（attribute变量）
        glEnableVertexAttribArray(getAttribLocation("a_position"));
        glVertexAttribPointer(getAttribLocation("a_position"), 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    }
    
    Program::~Program() {
        glBindVertexArray(0);
        glDeleteProgram(_object);
    }
    
    GLint Program::getUniformLocation(const char *name) {
        GLint location = glGetUniformLocation(_object, name);
        assert(location != -1);
        return location;
    }
    
    GLint Program::getAttribLocation(const char *name) {
        GLint location = glGetAttribLocation(_object, name);
        assert(location != -1);
        return location;
    }
    
    void Program::use() {
        glUseProgram(_object);
        glBindVertexArray(_vao);
    }

}
