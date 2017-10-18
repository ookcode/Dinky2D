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
        int channels;
        unsigned char *data = SOIL_load_image(key.c_str(), &_width, &_height, &channels, SOIL_LOAD_AUTO);
        if (data == NULL) {
            std::string msg("SOIL loading error: ");
            msg = msg + SOIL_last_result() + " " + key;
            throw std::runtime_error(msg);
        }
        GLuint texture = SOIL_create_OGL_texture(data, _width, _height, channels,
                                                 SOIL_CREATE_NEW_ID,
                                                 SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
                                                 SOIL_FLAG_NTSC_SAFE_RGB |SOIL_FLAG_COMPRESS_TO_DXT
                                                 );
        SOIL_free_image_data(data);
        
        _texture = texture;
    }
    
    Texture::~Texture() {
        
    }
}
