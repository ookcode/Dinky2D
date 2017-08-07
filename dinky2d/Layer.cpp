//
//  Layer.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/7.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Layer.hpp"

namespace Dinky {
    
    Layer::Layer(float width, float height, glm::vec4 color) {
        
        setAnchorPoint(glm::vec2(0.0f, 0.0f));
        setSize(glm::vec2(width, height));
        setColor(color);
        setOpacity(color.a);
        
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
        
        setProgram(ProgramCache::getInstance()->getProgram(Program::SHADER_DEFAULT_COLOR));
    }
    
    Layer::~Layer() {
    }
    
    void Layer::updateVertices() {
        glm::vec2 anchorPoint = getAnchorPoint();
        glm::vec2 size = getSize();
        _triangles.verts[0].vert = glm::vec3(-anchorPoint * size, 0.0f);
        _triangles.verts[1].vert = glm::vec3((-anchorPoint + glm::vec2(1.0f, 0.0f)) * size, 0.0f);
        _triangles.verts[2].vert = glm::vec3((-anchorPoint + glm::vec2(1.0f, 1.0f)) * size, 0.0f);
        _triangles.verts[3].vert = glm::vec3((-anchorPoint + glm::vec2(0.0f, 1.0f)) * size, 0.0f);
    }
    
    void Layer::draw(Renderer* renderer, glm::mat4 &transform) {
        if(getOpacity() > 0) {
            updateVertices();
            RenderCommand* command = new RenderCommand(getProgram(), transform, _triangles);
            command->setColor(getColor(), getDisplayedOpacity());
            renderer->addCommand(command);
        }
    }
}
