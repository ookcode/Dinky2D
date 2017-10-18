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
    
    void TextureCache::removeTexture(const std::string& key) {
        auto iter = _textures.find(key);
        if (iter != _textures.end()) {
            Texture *tex = iter->second;
            GLuint texId = tex->getObject();
            glDeleteTextures(1, &texId);
            _textures.erase(iter);
            delete tex;
        }
    }
    
    void TextureCache::removeAllTexture() {
        for (auto iter = _textures.begin(); iter != _textures.end(); ++iter) {
            Texture *tex = iter->second;
            GLuint texId = tex->getObject();
            glDeleteTextures(1, &texId);
            delete tex;
        }
        _textures.clear();
    }
    
    Texture* TextureCache::getTexture(const std::string& key) {
        return addTexture(key);
    }
}
