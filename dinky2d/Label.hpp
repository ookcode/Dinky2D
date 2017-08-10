//
//  Label.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/9.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef Label_hpp
#define Label_hpp

#include "Node.hpp"
#include <ft2build.h>
#include <ftglyph.h>

namespace Dinky {
    class Label : public Node {
    public:
        Label(const std::string& text, int fontSize, std::string font = "");
        virtual ~Label() override;
        virtual void updateVertices() override;
        virtual void draw(Renderer* renderer, glm::mat4 &transform) override;
        
        void setFontSize(int fontSize);
        void setText(const std::string& text);
        void setFont(const std::string& font);
        
    private:
        void refresh();
        
        Triangles _triangles;
        GLuint _texture = 0;
        FT_Face _face;
        FT_Library _ft;
        std::string _text;
        std::string _font;
        bool _isDirty = false;
        int _fontSize = 0;
        
    };
}

#endif /* Label_hpp */
