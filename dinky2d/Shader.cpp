//
//  Shader.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/15.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Shader.hpp"
#include <fstream>
#include <sstream>

namespace Dinky {

    Shader Shader::loadShader(const std::string& shaderFile, GLenum shaderType) {
        // 打开文件
        std::ifstream f;
        f.open(shaderFile.c_str(), std::ios::in | std::ios::binary);
        if(!f.is_open()){
            throw std::runtime_error(std::string("无法打开文件：") + shaderFile);
        }
        
        // 读取文件内容
        std::stringstream buffer;
        buffer << f.rdbuf();
        
        // 构造shader对象
        Shader shader(buffer.str(), shaderType);
        return shader;
    }
    
    Shader::Shader(const std::string& shaderCode, GLenum shaderType) {
        // 创建shader对象
        _object = glCreateShader(shaderType);

        const GLchar* source = shaderCode.c_str();
        glShaderSource(_object, 1, &source, NULL);
        
        // 编译
        glCompileShader(_object);
        
        // 编译检测
        GLint status;
        glGetShaderiv(_object, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            std::string msg("编译shader失败：\n");
            
            GLint infoLogLength;
            glGetShaderiv(_object, GL_INFO_LOG_LENGTH, &infoLogLength);
            
            char* strInfoLog = new char[infoLogLength + 1];
            glGetShaderInfoLog(_object, infoLogLength, NULL, strInfoLog);
            msg += strInfoLog;
            delete[] strInfoLog;
            
            glDeleteShader(_object);
            _object = 0;
            throw std::runtime_error(msg);
        }
    }
    
    Shader::~Shader() {
        
    }
    
}
