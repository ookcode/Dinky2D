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
        setShader("../dinky2d/shader/default.vert", "../dinky2d/shader/default.frag");
    }
    
    void Node::setShader(const std::string &vertFile, const std::string &fragFile) {
        if(_program) {
            delete _program;
        }
        _program = new Program(vertFile, fragFile);
        _program->use();
    }
    
    Node::~Node() {
        delete _program;
        _program = nullptr;
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
    
    void Node::setPosition(glm::vec2 position) {
        _position = position;
    }
    
    void Node::setColor(glm::vec4 color) {
        _color = color;
    }
    
    void Node::setRotation(float degrees) {
        _rotation = degrees;
    }
    
    void Node::setAnchor(glm::vec2 anchor) {
        _anchor = anchor;
    }
    
    void Node::draw() {
        if(_parent) {
            // 正射投影
            glm::vec2 winSize = Director::getInstance()->getWinSize();
            // 左边界，右边界，下边界，上边界
            glm::mat4 projection = glm::ortho(0.0f, winSize.x, 0.0f, winSize.y, -1.0f, 1.0f);
            glUniformMatrix4fv(_program->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
            
            // 左下角的世界坐标
            _worldPos = _parent->getWorldPos() + _position - _anchor * _size;
            // 节点的矩阵变换
            glm::mat4 model;
            model = glm::translate(model, glm::vec3(_worldPos + _size / 2.0f, 0.0f));
            model = glm::rotate(model, glm::radians(_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(_size, 1.0f));
            glUniformMatrix4fv(_program->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
            
            // 颜色
            glUniform4fv(_program->getUniformLocation("fragColor"), 1, glm::value_ptr(_color));
            
            // 开始绘制
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        // 遍历绘制子节点
        for(auto iter = _children.begin(); iter != _children.end(); ++iter) {
            (*iter)->draw();
        }
    }
    
}
