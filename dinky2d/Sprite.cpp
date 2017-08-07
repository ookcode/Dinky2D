//
//  Sprite.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Sprite.hpp"

namespace Dinky {
    
    Sprite::Sprite(const std::string& filePath) {
        _texture = TextureCache::getInstance()->getTexture(filePath);
        
        _triangles.vertCount = 4;
        _triangles.indexCount = 6;
        
        _triangles.verts = new Vertex[_triangles.vertCount] {
            //     X        Y       Z       U       V
            Vertex(0.0f,    0.0f,   0.0f,   0.0f,   0.0f),
            Vertex(1.0f,    0.0f,   0.0f,   1.0f,   0.0f),
            Vertex(1.0f,    1.0f,   0.0f,   1.0f,   1.0f),
            Vertex(0.0f,    1.0f,   0.0f,   0.0f,   1.0f)
        };
        
        _triangles.indices = new GLuint[_triangles.indexCount] {
            0, 1, 2,
            2, 3, 0,
        };
        
        setProgram(ProgramCache::getInstance()->getProgram(Program::SHADER_DEFAULT));
    }
    
    Sprite::~Sprite() {
    }
    
    void Sprite::updateVertices() {
        glm::vec2 anchorPoint = getAnchorPoint();
        glm::vec2 size = getSize();
        _triangles.verts[0].vert = glm::vec3(-anchorPoint * size, 0.0f);
        _triangles.verts[1].vert = glm::vec3((-anchorPoint + glm::vec2(1.0f, 0.0f)) * size, 0.0f);
        _triangles.verts[2].vert = glm::vec3((-anchorPoint + glm::vec2(1.0f, 1.0f)) * size, 0.0f);
        _triangles.verts[3].vert = glm::vec3((-anchorPoint + glm::vec2(0.0f, 1.0f)) * size, 0.0f);
    }
    
    void Sprite::draw(Renderer* renderer, glm::mat4 &transform) {
        if(_texture) {
            updateVertices();
            RenderCommand* command = new RenderCommand(getProgram(), transform, _triangles);
            command->setTexture(_texture->getObject());
            command->setColor(getColor(), getDisplayedOpacity());
            renderer->addCommand(command);
        }
    }
}
