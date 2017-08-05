//
//  Node.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Node.hpp"
#include "Director.hpp"
namespace Dinky {
    
    Node::Node() {
    }
    
    Node::~Node() {
        for(auto iter = _children.begin(); iter != _children.end(); ++iter) {
            delete *iter;
        }
    }
    
    void Node::addChild(Node *node) {
        if(node->getParent()) {
            throw std::runtime_error("Node can not be added twice");
        }
        _children.push_back(node);
        node->setParent(this);
    }
    
    void Node::removeChild(Node *node) {
        if(node->getParent() != this) {
            throw std::runtime_error("Node not added");
        }
        for(auto iter = _children.begin(); iter != _children.end(); ++iter) {
            if(node == *iter) {
                _children.erase(iter);
                delete *iter;
                break;
            }
        }
    }
    
    void Node::setProgram(Program *program) {
        _program = program;
    }
    
    void Node::removeFromParent() {
        if(_parent) {
            _parent->removeChild(this);
        }
    }
    
    void Node::setParent(Node *node) {
        _parent = node;
    }
    
    void Node::setSize(glm::vec2 size) {
        _size = size;
    }
    
    void Node::setVisible(bool visible) {
        _visible = visible;
    }
    
    void Node::setPosition(glm::vec2 position) {
        _position = position;
    }
    
    void Node::setColor(glm::vec4 color) {
        _color = color;
    }
    
    void Node::setRotation(float degrees) {
        _rotation = degrees;
    }
    
    void Node::setScale(glm::vec2 scale) {
        _scale = scale;
    }
    
    void Node::setAnchorPoint(glm::vec2 anchorPoint) {
        // FIXME: 锚点需要能影响旋转，目前旋转恒以0.5,0.5为原点
        _anchorPoint = anchorPoint;
    }
    
    void Node::updateVertices() {
        
    }
    
    glm::mat4& Node::getParentToNodeTransform() {
        // 节点的矩阵变换
        glm::mat4 transform;
        _transform = transform;
        // 子节点强制以父节点左下角为原点
        glm::vec2 offset = -_parent->getSize() * _parent->getAnchorPoint();
        _transform = glm::translate(_transform, glm::vec3(_position + offset , 0.0f));
        _transform = glm::scale(_transform, glm::vec3(_scale, 1.0f));
        _transform = glm::rotate(_transform, glm::radians(-_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        return _transform;
    }
    
    void Node::visit(Renderer* renderer, glm::mat4 &parentTransform, bool isAncestor) {
        if (!_visible) {
            return;
        }
        
        if(isAncestor == false) {
            // 不要乘反了
            _modelViewTransform = parentTransform * getParentToNodeTransform();
        }
        
        this->draw(renderer, _modelViewTransform);
        
        for(auto iter = _children.cbegin(); iter != _children.cend(); ++iter) {
            (*iter)->visit(renderer, _modelViewTransform, false);
        }
    }
    
    void Node::draw(Renderer* renderer, glm::mat4 &transform) {
        
    }

}
