//
//  Texture.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/28.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Texture.hpp"
#include "SOIL.h"

namespace Dinky {
    
    Texture::Texture(const std::string& key) {
        // 通过SOIL库将图片载入成纹理
        GLuint texture = SOIL_load_OGL_texture(key.c_str(),
                                               SOIL_LOAD_AUTO,
                                               SOIL_CREATE_NEW_ID,
                                               SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
                                               SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                                               );
        // 检查纹理是否正确
        if(0 == texture) {
            std::string msg("SOIL loading error: ");
            msg = msg + SOIL_last_result() + key;
            throw std::runtime_error(msg);
        }
        _texture = texture;
    }
    
    Texture::~Texture() {
        
    }
}
