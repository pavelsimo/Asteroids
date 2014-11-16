#include <iostream>
#include <string>
#include "vector_battle_regular_20.hxx"

using namespace std;

int main (int argc, char* argv[])
{
    try
    {
        auto_ptr<Font> font (Font_("vector_battle_regular_20.xml", xml_schema::flags::dont_validate));

        cout << font->family() << endl;
        cout << font->size() << endl;
        cout << font->height() << endl;
        cout << font->style() << endl;
        
        
        Font::Char_sequence& cs (font->Char());
        
        for (Font::Char_iterator ch (cs.begin()); ch != cs.end(); ++ch)
        {
            cout << "code=" << ch->code() << endl;
            cout << "offset=" << ch->offset() << endl;
            cout << "rect=" << ch->rect() << endl;
            cout << "width=" << ch->width() << endl;
        }
        
    }
    catch (const xml_schema::exception& e)
    {
        cerr << e << endl;
        return 1;
    }
}