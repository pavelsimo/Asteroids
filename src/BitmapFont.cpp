#include "BitmapFont.h"

BitmapFont::BitmapFont()
: m_texture(nullptr)
{

}

BitmapFont::~BitmapFont()
{
    Clean();
}

bool BitmapFont::LoadBitmap(const std::string& filename)
{
    Clean();
    if(m_texture == nullptr)
    {
        m_texture = new Texture();
        if(m_texture->LoadFromFile(filename)) {
            return true;
        }
    }
    return false;
}

bool BitmapFont::LoadGlyphsFromXML(const std::string& filename)
{
    try
    {
        std::unique_ptr<Font> font (Font_(filename,
                xml_schema::flags::dont_validate));

        m_family = static_cast<std::string>(font->family());
        m_size = font->size();
        m_height = font->height();
        m_style = static_cast<std::string>(font->style());

        Font::Char_sequence& cs(font->Char());

        for (Font::Char_iterator ch (cs.begin()); ch != cs.end(); ++ch)
        {
            std::string code = static_cast<std::string>(ch->code());
            std::string offset = static_cast<std::string>(ch->offset());
            std::string rect = static_cast<std::string>(ch->rect());
            int width = ch->width();

            BitmapFontGlyph bitmapFontGlyph;
            ParseGlyphRect(rect, bitmapFontGlyph.x, bitmapFontGlyph.y,
                    bitmapFontGlyph.width, bitmapFontGlyph.height);
            ParseGlyphOffset(offset, bitmapFontGlyph.xOffset, bitmapFontGlyph.yOffset);

            AddGlyph(code[0], bitmapFontGlyph);
        }
    }
    catch (const xml_schema::exception& e)
    {
        std::cerr << e << std::endl;
        return false;
    }

    return true;
}

void BitmapFont::AddGlyph(unsigned int glyph,
    float x, float y,
    float w, float h,
    float xOffset, float yOffset
)
{
    BitmapFontGlyph bitmapFontGlyph;
    bitmapFontGlyph.x = x;
    bitmapFontGlyph.y = y;
    bitmapFontGlyph.width = w;
    bitmapFontGlyph.height = h;
    bitmapFontGlyph.xOffset = xOffset;
    bitmapFontGlyph.yOffset = yOffset;

    AddGlyph(glyph, bitmapFontGlyph);
}

void BitmapFont::AddGlyph(unsigned int glyph, const BitmapFontGlyph& bitmapFontGlyph)
{
    m_glyphs[glyph] = bitmapFontGlyph;
}

void BitmapFont::RemoveGlyph(unsigned int glyph)
{
    if(m_glyphs.size() > 0)
    {
        std::map<unsigned int, BitmapFontGlyph>::iterator it;
        it = m_glyphs.find(glyph);
        if(it != m_glyphs.end())
        {
            m_glyphs.erase(it);
        }
    }
}

BitmapFontGlyph BitmapFont::GetGlyph(unsigned int glyph)
{
    if(m_glyphs.size() > 0)
    {
        std::map<unsigned int, BitmapFontGlyph>::iterator it;
        it = m_glyphs.find(glyph);
        if(it != m_glyphs.end())
        {
            return it->second;
        }
    }

    BitmapFontGlyph bitmapFontGlyph;
    bitmapFontGlyph.x = 0;
    bitmapFontGlyph.y = 0;
    bitmapFontGlyph.width = 0;
    bitmapFontGlyph.height = 0;
    bitmapFontGlyph.xOffset = 0;
    bitmapFontGlyph.yOffset = 0;

    return bitmapFontGlyph;
}

const Texture* BitmapFont::GetTexture() const
{
    return m_texture;
}

void BitmapFont::Clean()
{
    if(m_texture != nullptr)
    {
        delete m_texture;
        m_texture = nullptr;
    }

    m_glyphs.clear();
}

void BitmapFont::ParseGlyphRect(const std::string &str, float &x, float &y, float &width, float &height)
{
    std::string token;
    std::istringstream ss(str);

    ss >> token;
    x = std::stof(token);

    ss >> token;
    y = std::stof(token);

    ss >> token;
    width = std::stof(token);

    ss >> token;
    height = std::stof(token);
}

void BitmapFont::ParseGlyphOffset(const std::string &str, float &xOffset, float &yOffset)
{
    std::string token;
    std::istringstream ss(str);

    ss >> token;
    xOffset = std::stof(token);

    ss >> token;
    yOffset = std::stof(token);
}

int BitmapFont::GetSize() const
{
    return m_size;
}

void BitmapFont::SetSize(int size)
{
    m_size = size;
}

void BitmapFont::SetHeight(int height)
{
    m_height = height;
}

int BitmapFont::GetHeight() const
{
    return m_height;
}

void BitmapFont::SetFamily(const std::string& family)
{
    m_family = family;
}

const std::string BitmapFont::GetFamily() const
{
    return m_family;
}

void BitmapFont::SetStyle(const std::string& style)
{
    m_style = style;
}

const std::string BitmapFont::GetStyle() const
{
    return m_style;
}
