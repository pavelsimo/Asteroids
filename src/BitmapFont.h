#ifndef BITMAPFONT_H
#define BITMAPFONT_H

#include <iostream>
#include <map>
#include <string>

#include "Texture.h"
#include "vector_battle_regular_20.hxx"


struct BitmapFontGlyph
{
    float x;
    float y;
    float width;
    float height;
    float xOffset;
    float yOffset;
};


class BitmapFont
{
    public:
        // ctor & dtor
        BitmapFont();
        virtual ~BitmapFont();

        // methods
        virtual bool LoadBitmap(const std::string& filename);
        virtual bool LoadGlyphsFromXML(const std::string& filename);
        void AddGlyph(unsigned int glyph,
            float x, float y,
            float w, float h,
            float xOffset, float yOffset
        );
        void AddGlyph(unsigned int glyph, BitmapFontGlyph bitmapFontGlyph);
        void RemoveGlyph(unsigned int glyph);
        BitmapFontGlyph GetGlyph(unsigned int glyph);
        const Texture* GetTexture() const;
        void Clean();
        
    private:
        void ParseGlyphRect(const std::string& str, float &x, float &y, float &width, float &height);
        void ParseGlyphOffset(const std::string &str, float &xOffset, float &yOffset);

        int m_size;
        int m_height;
        std::string m_family;
        std::string m_style;
        Texture* m_texture;
        std::map<unsigned int, BitmapFontGlyph> m_glyphs;
};

#endif