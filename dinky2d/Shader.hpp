//
//  Shader.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/15.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <string>
#include <OpenGL/gl3.h>

namespace Dinky {

class Shader {
public:
    static Shader loadShader(const std::string& shaderFile, GLenum shaderType);
    Shader(const std::string& shaderCode, GLenum shaderType);
    ~Shader();
    GLuint getObject() {
        return _object;
    }
    
private:
    GLuint _object = 0;
};
    
}

#endif /* Shader_hpp */
