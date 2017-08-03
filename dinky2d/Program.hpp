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
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

namespace Dinky {
    
class Program {
    public:
        // vertex attribute序列
        enum
        {
            // Index 0 Position
            VERTEX_ATTRIB_POSITION,
            // Index 1 Tex coord 0
            VERTEX_ATTRIB_TEX_COORD,
        };
        // 默认路径
        static const char* DEFAULT_SHADER_PATH;
        // 默认着色器
        static const char* SHADER_DEFAULT;
    
    public:
        Program(const std::string& key);
        ~Program();
    
        void use();
        GLint getUniformLocation(const char* name);
        GLint getAttribLocation(const char* name);
        const std::string& getFileByKey(const std::string& name);
    
    private:
        GLuint loadShader(const std::string file, GLenum shaderType);
        GLuint _object = 0;
};
    
}

#endif /* Program_hpp */
