//
//  Label.cpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/8/9.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#include "Label.hpp"
#include <locale>
#include <codecvt>
namespace Dinky {
#define MAX_TEXTURE_SIZE 1024.0f
#define DEFAULT_FONT "../dinky2d/resources/yahei.ttf"
    Label::Label(const std::string& text, int fontSize, std::string font) {
        if (FT_Init_FreeType(&_ft))
            throw std::runtime_error("ERROR::FREETYPE: Could not init FreeType Library");
        
        // 初始化一张1024x1024的纹理
        glGenTextures(1, &_texture);
        glBindTexture(GL_TEXTURE_2D, _texture);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, MAX_TEXTURE_SIZE, MAX_TEXTURE_SIZE, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
        
        setProgram(ProgramCache::getInstance()->getProgram(Program::SHADER_DEFAULT_LABEL));
        
        if (font.length() == 0) {
            font = DEFAULT_FONT;
        }
        setFont(font);
        setFontSize(fontSize);
        setText(text);
    }
    
    Label::~Label() {
    }
    
    void Label::setFont(const std::string &font) {
        // 加载字体文件
        if (FT_New_Face(_ft, font.c_str(), 0, &_face))
            throw std::runtime_error("ERROR::FREETYPE: Failed to load font");
        _isDirty = true;
    }
    
    void Label::setFontSize(int fontSize) {
        _fontSize = fontSize;
        FT_Set_Pixel_Sizes(_face, 0, fontSize);
        _isDirty = true;
    }
    
    void Label::setText(const std::string &text) {
        _text = text;
        _isDirty = true;
    }
    
    void Label::refresh() {
        // 转化为unicode字符串
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        std::wstring wtext = conv.from_bytes(_text);

        // 初始化顶点信息（分配内存）
        int length = (int)wtext.length();
        if(_triangles.vertCount)
            delete _triangles.verts;
        if(_triangles.indices)
            delete _triangles.indices;
        _triangles.vertCount = 4 * length;
        _triangles.indexCount = 6 * length;
        _triangles.indices = new GLuint[_triangles.indexCount];
        _triangles.verts = new Vertex[_triangles.vertCount];
        GLuint defaultIndices[6] = {0,1,2,2,3,0};
        for (int i = 0; i < _triangles.indexCount; ++i) {
            _triangles.indices[i] = defaultIndices[i % 6] + (i / 6) * 4;
        }
        
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        
        float vertOffsetX = 0.0f; // 顶点x偏移
        float vertOffsetY = -_fontSize; // 顶点y偏移
        float texOffsetX = 0.0f; // 纹理x偏移
        float texOffsetY = 0.0f; // 纹理y偏移
        float maxVertWidth = 0.0f; // 最大宽度
        // 循环所有字符
        for (int i = 0; i < length; ++i) {
            FT_Load_Glyph(_face, FT_Get_Char_Index(_face, wtext.at(i)), FT_LOAD_DEFAULT);
            FT_Glyph glyph;
            FT_Get_Glyph(_face->glyph, &glyph);
            FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1 );
            FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
            FT_Bitmap& bitmap = bitmap_glyph->bitmap;
            
            // 以左下角为0, 0的坐标系
            float width = bitmap.width;
            float height = bitmap.rows;
            
            // 纹理：写满一行，换行
            if (texOffsetX + _fontSize > MAX_TEXTURE_SIZE) {
                texOffsetX = 0.0f;
                texOffsetY += _fontSize;
                if(texOffsetY > MAX_TEXTURE_SIZE)
                    throw std::runtime_error("label texture is over max size");
            }
            
            // 顶点：发现\n，换行
            if (wtext.at(i) == '\n') {
                if (vertOffsetX > maxVertWidth) {
                    maxVertWidth = vertOffsetX;
                }
                vertOffsetX = 0;
                vertOffsetY -= _fontSize;
            }
            
            // 写入纹理
            glTexSubImage2D(GL_TEXTURE_2D, 0, texOffsetX, texOffsetY, width, height, GL_RED, GL_UNSIGNED_BYTE, bitmap.buffer);
            
            // 顶点
            float vertLeft = vertOffsetX + bitmap_glyph->left;
            float vertRight = vertLeft + width;
            float vertTop = vertOffsetY + bitmap_glyph->top;
            float vertBottom = vertTop - height;

            // UV
            float texLeft = texOffsetX / MAX_TEXTURE_SIZE;
            float texRight = (texOffsetX + width) / MAX_TEXTURE_SIZE;
            float texTop = texOffsetY / MAX_TEXTURE_SIZE;
            float texBottom = (texOffsetY + height) / MAX_TEXTURE_SIZE;
            
            // 顶点数据                                 X           Y           Z       U           V
            _triangles.verts[i * 4 + 0] =   Vertex(vertLeft,    vertBottom, 0.0f,   texLeft,    texBottom);
            _triangles.verts[i * 4 + 1] =   Vertex(vertRight,   vertBottom, 0.0f,   texRight,   texBottom);
            _triangles.verts[i * 4 + 2] =   Vertex(vertRight,   vertTop,    0.0f,   texRight,   texTop);
            _triangles.verts[i * 4 + 3] =   Vertex(vertLeft,    vertTop,    0.0f,   texLeft,    texTop);
            
            // 偏移
            vertOffsetX = vertRight;
            texOffsetX += width;
        }
        if (vertOffsetX > maxVertWidth) {
            maxVertWidth = vertOffsetX;
        }
        setSize(glm::vec2(maxVertWidth, - vertOffsetY));
    }
    
    void Label::updateVertices() {
        if (_isDirty or isNodeDirty()) {
            refresh();
            glm::vec2 anchorPoint = getAnchorPoint();
            glm::vec2 size = getSize();
            for (int i = 0; i < _triangles.vertCount; ++i) {
                _triangles.verts[i].vert += glm::vec3(-anchorPoint.x * size.x, (1 - anchorPoint.y) * size.y, 0.0f);
            }
        }
        Node::updateVertices();
    }
    
    void Label::draw(Renderer* renderer, glm::mat4 &transform) {
        if(_text.length() > 0) {
            updateVertices();
            RenderCommand* command = new RenderCommand(getProgram(), transform, _triangles);
            command->setColor(getColor(), getDisplayedOpacity());
            command->setTexture(_texture);
            renderer->addCommand(command);
        }
    }
}
