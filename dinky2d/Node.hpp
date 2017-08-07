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
#include "ProgramCache.hpp"
#include "Renderer.hpp"
#include "Scheduler.hpp"

namespace Dinky {
    
    class Node {
    public:
        Node();
        virtual ~Node();
        
        void addChild(Node *node);
        std::vector<Node *> getChildren() {
            return _children;
        }
        
        void setParent(Node *node);
        Node* getParent() {
            return _parent;
        }
        
        void setSize(glm::vec2 size);
        glm::vec2& getSize() {
            return _size;
        }
        
        void setVisible(bool visible);
        bool getVisible() {
            return _visible;
        }
        
        void setPosition(glm::vec2 position);
        glm::vec2& getPosition() {
            return _position;
        }
        
        void setColor(glm::vec3 color);
        glm::vec3& getColor() {
            return _color;
        }
        
        void setRotation(float degrees);
        float getRotation() {
            return _rotation;
        }
        
        void setScale(glm::vec2 scale);
        glm::vec2& getScale() {
            return _scale;
        }
        
        void setAnchorPoint(glm::vec2 anchorPoint);
        glm::vec2& getAnchorPoint() {
            return _anchorPoint;
        }
        
        void setOpacity(float opacity);
        float getOpacity() {
            return _opacity;
        }
        
        void updateCascadeOpacity();
        void updateDisplayedOpacity(float parentOpacity);
        float getDisplayedOpacity() {
            return _displayedOpacity;
        }
        
        void setProgram(Program* program);
        Program* getProgram() {
            return _program;
        }
        
        void removeChild(Node *node);
        void removeFromParent();
        
        virtual void updateVertices();
        virtual void draw(Renderer* renderer, glm::mat4 &transform);
        void visit(Renderer* renderer, glm::mat4 &parentTransform, bool isAncestor);
        
        std::string schedule(Scheduler::SEL_SCHEDULE callback);
        void unschedule(Scheduler::SEL_SCHEDULE callback);
        void unschedule(const std::string& key);
        void unscheduleAll();
        
        glm::mat4& getParentToNodeTransform();
        glm::mat4& getModelViewTransform() {
            return _modelViewTransform;
        }
        
    private:
        std::vector<Node *> _children;
        bool _visible = true;
        Node *_parent = nullptr;
        Program* _program = nullptr;
        glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec2 _size = glm::vec2(0.0f, 0.0f);
        glm::vec2 _position = glm::vec2(0.0f, 0.0f);
        glm::vec2 _scale = glm::vec2(1.0f, 1.0f);
        glm::vec2 _anchorPoint = glm::vec2(0.5f, 0.5f);
        float _rotation = 0.0f;
        float _displayedOpacity = 1.0f;
        float _opacity = 1.0f;
        glm::mat4 _modelViewTransform; // 节点的最终变换
        glm::mat4 _transform; // 节点自身的变换
        Scheduler *_scheduler = nullptr;
    };
    
    
}

#endif /* Node_hpp */
