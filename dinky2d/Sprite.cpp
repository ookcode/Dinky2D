//
//  Sprite.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Sprite.hpp"
#include "SOIL.h"
namespace Dinky {
    
    Sprite::Sprite(const std::string& filePath) {
        // 通过SOIL库将图片载入成纹理
        _texture = SOIL_load_OGL_texture(filePath.c_str(),
                                        SOIL_LOAD_AUTO,
                                        SOIL_CREATE_NEW_ID,
                                        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
                                        SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                                        );
        
        // 检查纹理是否正确
        if(0 == _texture) {
            printf("SOIL loading error: '%s'\n", SOIL_last_result());
        }
    }

    Sprite::~Sprite() {
        printf("delete\n");
        glDeleteTextures(1, &_texture);
    }
    
    void Sprite::draw() {
        if(_texture) {
            // 绑定纹理
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _texture);
            glUniform1i(this->getProgram()->getUniformLocation("tex"), 0); // 0表示绑定到GL_TEXTURE0
        }
        Node::draw();
    }
}
