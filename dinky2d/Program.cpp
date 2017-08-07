//
//  Program.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/15.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Program.hpp"
#include <fstream>
#include <sstream>

namespace Dinky {
    const char* Program::DEFAULT_SHADER_PATH = "../dinky2d/shader/";
    
    const char* Program::SHADER_DEFAULT = "default";
    const char* Program::SHADER_DEFAULT_COLOR = "defaultColor";
    
    Program::Program(const std::string& key) {
        // 创建程序容器
        _object = glCreateProgram();
        
        // 绑定着色器与容器
        GLuint vertShader = loadShader(DEFAULT_SHADER_PATH + key + ".vert", GL_VERTEX_SHADER);
        GLuint fragShader = loadShader(DEFAULT_SHADER_PATH + key + ".frag", GL_FRAGMENT_SHADER);
        
        glAttachShader(_object, vertShader);
        glAttachShader(_object, fragShader);
        
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

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
    }
    
    Program::~Program() {
        glDeleteProgram(_object);
    }
    
    GLuint Program::loadShader(const std::string file, GLenum shaderType) {
        // 打开文件
        std::ifstream f;
        f.open(file.c_str(), std::ios::in | std::ios::binary);
        if(!f.is_open()){
            throw std::runtime_error(std::string("无法打开文件：") + file);
        }
        
        // 读取文件内容
        std::stringstream buffer;
        buffer << f.rdbuf();
        const std::string &bufferStr =  buffer.str();
        
        // 创建shader对象
        GLuint object = glCreateShader(shaderType);
        
        const GLchar* source = bufferStr.c_str();
        glShaderSource(object, 1, &source, NULL);
        
        // 编译
        glCompileShader(object);
        
        // 编译检测
        GLint status;
        glGetShaderiv(object, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            std::string msg("编译shader失败：\n");
            
            GLint infoLogLength;
            glGetShaderiv(object, GL_INFO_LOG_LENGTH, &infoLogLength);
            
            char* strInfoLog = new char[infoLogLength + 1];
            glGetShaderInfoLog(object, infoLogLength, NULL, strInfoLog);
            msg += strInfoLog;
            delete[] strInfoLog;
            
            glDeleteShader(object);
            object = 0;
            throw std::runtime_error(msg);
        }
        
        return object;
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
    }

}
