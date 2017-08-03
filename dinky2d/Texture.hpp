//
//  Texture.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/28.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp
#include <unordered_map>
#include "Program.hpp"

namespace Dinky {

    class Texture {
        public:
            Texture(const std::string& key);
            ~Texture();
            GLuint getObject() {
                return _texture;
            }
        private:
            GLuint _texture = 0;
    };
}

#endif /* Texture_hpp */
