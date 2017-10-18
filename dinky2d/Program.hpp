//
//  Program.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/15.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef Program_hpp
#define Program_hpp

#include <string>
#include <OpenGl/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Dinky {
    
class Program {
    public:
        // vertex attribute序列
        enum
        {
            // 0 a_position
            VERTEX_ATTRIB_POSITION,
            // 1 a_texCoord
            VERTEX_ATTRIB_TEX_COORD,
        };
        // 默认路径
        static const char* DEFAULT_SHADER_PATH;
        // 默认着色器
        static const char* SHADER_DEFAULT;
        // 颜色着色器
        static const char* SHADER_DEFAULT_COLOR;
        // 文本着色器
        static const char* SHADER_DEFAULT_LABEL;
    
    public:
        Program(const std::string& key);
        ~Program();
    
        void use(); // 使用容器与着色器
    
        GLint getUniformLocation(const char* name);
        GLint getAttribLocation(const char* name);
    
    private:
        GLuint loadShader(const std::string file, GLenum shaderType);
        GLuint _object = 0;
};
    
}

#endif /* Program_hpp */
