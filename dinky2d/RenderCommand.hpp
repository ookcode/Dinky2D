//
//  RenderCommand.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/2.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef RenderCommand_hpp
#define RenderCommand_hpp

#include "Program.hpp"

namespace Dinky {
    
    struct Vertex {
        Vertex() {};
        Vertex(GLfloat x, GLfloat y, GLfloat z, GLfloat u, GLfloat v):vert(x, y, z),coord(u,v){}
        glm::vec3 vert;
        glm::vec2 coord;
    };
    
    struct Triangles
    {
        Vertex* verts;
        GLuint* indices;
        int vertCount;
        int indexCount;
        Triangles() = default;
        ~Triangles() {
            delete verts;
            delete indices;
        }
    };
    
    class RenderCommand {
    public:
        RenderCommand(Program *program, glm::mat4& transform, Triangles& triangles) ;
        Program* getProgram() {
            return _program;
        }
        
        void setTexture(GLuint texture);
        GLuint getTexture() {
            return _texture;
        }
        
        void setColor(glm::vec3& color, float opaticy);
        glm::vec4& getColor() {
            return _color;
        }
        
        glm::mat4& getTransform() {
            return _transform;
        }
        
        Triangles& getTriangles() {
            return _triangles;
        }
        
        void useMaterial();
        
    private:
        Program *_program = nullptr;
        Triangles& _triangles;
        glm::mat4& _transform;
        glm::vec4 _color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        GLuint _texture = 0;
    };
}

#endif /* RenderCommand_hpp */
