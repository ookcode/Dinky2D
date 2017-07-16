//
//  Program.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/15.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef Program_hpp
#define Program_hpp

#include "Shader.hpp"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

namespace Dinky {
    
    class Program {
    public:
        Program(const std::string& vertFile, const std::string& fragFile);
        ~Program();
        void use();
        GLint getUniformLocation(const char* name);
        GLint getAttribLocation(const char* name);
        
    private:
        GLuint _object = 0;
        GLuint _vao = 0;
    };
    
    
}

#endif /* Program_hpp */
