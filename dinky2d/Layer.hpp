//
//  Layer.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/7.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef Layer_hpp
#define Layer_hpp

#include "Node.hpp"
#include "TextureCache.hpp"

namespace Dinky {
    
    class Layer : public Node {
    public:
        Layer(float width, float height, glm::vec4 color);
        virtual ~Layer() override;
        virtual void updateVertices() override;
        virtual void draw(Renderer* renderer, glm::mat4 &transform) override;
        
    private:
        void refresh();
        
        Triangles _triangles;
    };
    
    
}

#endif /* Layer_hpp */
