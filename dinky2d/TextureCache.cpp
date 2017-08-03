//
//  TextureCache.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/3.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "TextureCache.hpp"

namespace Dinky {
    TextureCache* TextureCache::_instance = nullptr;
    TextureCache* TextureCache::getInstance() {
        if (_instance == nullptr) {
            _instance = new TextureCache();
        }
        return _instance;
    }
    
    TextureCache::TextureCache() {
        
    }
    
    TextureCache::~TextureCache() {
        
    }
    
    Texture* TextureCache::addTexture(const std::string& key) {
        auto iter = _textures.find(key);
        if (iter != _textures.end()) {
            return iter->second;
        }
        Texture *texture = new Texture(key);
        _textures[key] = texture;
        return texture;
    }
    
    Texture* TextureCache::getTexture(const std::string& key) {
        return addTexture(key);
    }
}
