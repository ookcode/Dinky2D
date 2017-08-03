//
//  TextureCache.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/3.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef TextureCache_hpp
#define TextureCache_hpp

#include "Texture.hpp"
#include <unordered_map>
namespace Dinky {
    class TextureCache {
    public:
        static TextureCache* getInstance();
        Texture* addTexture(const std::string& key);
        Texture* getTexture(const std::string& key);
        
    private:
        TextureCache();
        ~TextureCache();
        static TextureCache* _instance;
        std::unordered_map<std::string, Texture *> _textures;
    };
}

#endif /* TextureCache_hpp */
