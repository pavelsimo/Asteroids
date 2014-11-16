#ifndef __BITMAPFONT_H_
#define __BITMAPFONT_H_

#include <iostream>
#include <map>
#include <string>

#include "Texture.h"
#include "BitmapFontXMLParser.hxx"

struct BitmapFontGlyph
{
    float x;
    float y;
    float width;
    float height;
    float xOffset;
    float yOffset;
};

// TODO: (Pavel) Change to <unsigned int, BitmapFontGlyph*>
typedef std::map<unsigned int, BitmapFontGlyph> GlyphMap;

class BitmapFont
{
    public:
        // ctor & dtor
        //
        BitmapFont();
        virtual ~BitmapFont();

        // methods
        //
        virtual bool LoadBitmap(const std::string& filename);
        virtual bool LoadGlyphsFromXML(const std::string& filename);
        void AddGlyph(unsigned int glyph, const BitmapFontGlyph& bitmapFontGlyph);
        void AddGlyph(unsigned int glyph, float x, float y, float w, float h,
            float xOffset, float yOffset
        );
        void RemoveGlyph(unsigned int glyph);
        BitmapFontGlyph GetGlyph(unsigned int glyph);
        const Texture* GetTexture() const;
        void Clean();

        // getters & setters
        //
        int GetSize() const;
        void SetSize(int size);

        void SetHeight(int height);
        int GetHeight() const;

        void SetFamily(const std::string& family);
        const std::string GetFamily() const;

        void SetStyle(const std::string& style);
        const std::string GetStyle() const;
    private:
        int m_size;
        int m_height;
        std::string m_family;
        std::string m_style;
        Texture* m_texture;
        GlyphMap m_glyphs;

        void ParseGlyphRect(const std::string& str, float &x, float &y, float &width, float &height);
        void ParseGlyphOffset(const std::string &str, float &xOffset, float &yOffset);
};

#endif // __BITMAPFONT_H_