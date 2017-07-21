//
//  Node.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <string>
#include <vector>
#include "Program.hpp"

namespace Dinky {
    
    class Node {
    public:
        Node();
        ~Node();
        void setShader(const std::string& vertFile, const std::string& fragFile);
        
        void addChild(Node *node);
        std::vector<Node *> getChildren() {
            return _children;
        }
        
        void setParent(Node *node);
        Node* getParent() {
            return _parent;
        }
        
        void setSize(glm::vec2 size);
        glm::vec2 getSize() {
            return _size;
        }
        
        void setPosition(glm::vec2 position);
        glm::vec2 getPosition() {
            return _position;
        }
        
        void setColor(glm::vec4 color);
        glm::vec4 getColor() {
            return _color;
        }
        
        void setRotation(float degrees);
        float getRotation() {
            return _rotation;
        }
        
        void setAnchor(glm::vec2 anchor);
        glm::vec2 getAnchor() {
            return _anchor;
        }
        
        glm::vec2 getWorldPos() {
            return _worldPos;
        }
        
        Program* getProgram() {
            return _program;
        }
        
        void removeChild(Node *node);
        void removeFromParent();
        virtual void draw();
 
    private:
        std::vector<Node *> _children;
        Node *_parent = nullptr;
        Program* _program = nullptr;
        glm::vec2 _size = glm::vec2(0.0f, 0.0f);
        glm::vec2 _position = glm::vec2(0.0f, 0.0f);
        glm::vec2 _worldPos = glm::vec2(0.0f, 0.0f);
        glm::vec4 _color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
        glm::vec2 _anchor = glm::vec2(0.5f, 0.5f);
        float _rotation = 0;
    };
    
    
}

#endif /* Node_hpp */
