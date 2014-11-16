// Copyright (c) 2005-2014 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "vector_battle_regular_20.hxx"

// Font
// 

const Font::Char_sequence& Font::
Char () const
{
  return this->Char_;
}

Font::Char_sequence& Font::
Char ()
{
  return this->Char_;
}

void Font::
Char (const Char_sequence& s)
{
  this->Char_ = s;
}

const Font::family_type& Font::
family () const
{
  return this->family_.get ();
}

Font::family_type& Font::
family ()
{
  return this->family_.get ();
}

void Font::
family (const family_type& x)
{
  this->family_.set (x);
}

void Font::
family (::std::auto_ptr< family_type > x)
{
  this->family_.set (x);
}

const Font::height_type& Font::
height () const
{
  return this->height_.get ();
}

Font::height_type& Font::
height ()
{
  return this->height_.get ();
}

void Font::
height (const height_type& x)
{
  this->height_.set (x);
}

const Font::size_type& Font::
size () const
{
  return this->size_.get ();
}

Font::size_type& Font::
size ()
{
  return this->size_.get ();
}

void Font::
size (const size_type& x)
{
  this->size_.set (x);
}

const Font::style_type& Font::
style () const
{
  return this->style_.get ();
}

Font::style_type& Font::
style ()
{
  return this->style_.get ();
}

void Font::
style (const style_type& x)
{
  this->style_.set (x);
}

void Font::
style (::std::auto_ptr< style_type > x)
{
  this->style_.set (x);
}


// Char
// 

const Char::code_type& Char::
code () const
{
  return this->code_.get ();
}

Char::code_type& Char::
code ()
{
  return this->code_.get ();
}

void Char::
code (const code_type& x)
{
  this->code_.set (x);
}

void Char::
code (::std::auto_ptr< code_type > x)
{
  this->code_.set (x);
}

const Char::offset_type& Char::
offset () const
{
  return this->offset_.get ();
}

Char::offset_type& Char::
offset ()
{
  return this->offset_.get ();
}

void Char::
offset (const offset_type& x)
{
  this->offset_.set (x);
}

void Char::
offset (::std::auto_ptr< offset_type > x)
{
  this->offset_.set (x);
}

const Char::rect_type& Char::
rect () const
{
  return this->rect_.get ();
}

Char::rect_type& Char::
rect ()
{
  return this->rect_.get ();
}

void Char::
rect (const rect_type& x)
{
  this->rect_.set (x);
}

void Char::
rect (::std::auto_ptr< rect_type > x)
{
  this->rect_.set (x);
}

const Char::width_type& Char::
width () const
{
  return this->width_.get ();
}

Char::width_type& Char::
width ()
{
  return this->width_.get ();
}

void Char::
width (const width_type& x)
{
  this->width_.set (x);
}


#include <xsd/cxx/xml/dom/parsing-source.hxx>

// Font
//

Font::
Font (const family_type& family,
      const height_type& height,
      const size_type& size,
      const style_type& style)
: ::xml_schema::type (),
  Char_ (this),
  family_ (family, this),
  height_ (height, this),
  size_ (size, this),
  style_ (style, this)
{
}

Font::
Font (const Font& x,
      ::xml_schema::flags f,
      ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  Char_ (x.Char_, f, this),
  family_ (x.family_, f, this),
  height_ (x.height_, f, this),
  size_ (x.size_, f, this),
  style_ (x.style_, f, this)
{
}

Font::
Font (const ::xercesc::DOMElement& e,
      ::xml_schema::flags f,
      ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  Char_ (this),
  family_ (this),
  height_ (this),
  size_ (this),
  style_ (this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false, true);
    this->parse (p, f);
  }
}

void Font::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_content (); p.next_content (false))
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // Char
    //
    if (n.name () == "Char" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< Char_type > r (
        Char_traits::create (i, f, this));

      this->Char_.push_back (r);
      continue;
    }

    break;
  }

  while (p.more_attributes ())
  {
    const ::xercesc::DOMAttr& i (p.next_attribute ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    if (n.name () == "family" && n.namespace_ ().empty ())
    {
      this->family_.set (family_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "height" && n.namespace_ ().empty ())
    {
      this->height_.set (height_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "size" && n.namespace_ ().empty ())
    {
      this->size_.set (size_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "style" && n.namespace_ ().empty ())
    {
      this->style_.set (style_traits::create (i, f, this));
      continue;
    }
  }

  if (!family_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "family",
      "");
  }

  if (!height_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "height",
      "");
  }

  if (!size_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "size",
      "");
  }

  if (!style_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "style",
      "");
  }
}

Font* Font::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class Font (*this, f, c);
}

Font& Font::
operator= (const Font& x)
{
  if (this != &x)
  {
    static_cast< ::xml_schema::type& > (*this) = x;
    this->Char_ = x.Char_;
    this->family_ = x.family_;
    this->height_ = x.height_;
    this->size_ = x.size_;
    this->style_ = x.style_;
  }

  return *this;
}

Font::
~Font ()
{
}

// Char
//

Char::
Char (const code_type& code,
      const offset_type& offset,
      const rect_type& rect,
      const width_type& width)
: ::xml_schema::type (),
  code_ (code, this),
  offset_ (offset, this),
  rect_ (rect, this),
  width_ (width, this)
{
}

Char::
Char (const Char& x,
      ::xml_schema::flags f,
      ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  code_ (x.code_, f, this),
  offset_ (x.offset_, f, this),
  rect_ (x.rect_, f, this),
  width_ (x.width_, f, this)
{
}

Char::
Char (const ::xercesc::DOMElement& e,
      ::xml_schema::flags f,
      ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  code_ (this),
  offset_ (this),
  rect_ (this),
  width_ (this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, false, false, true);
    this->parse (p, f);
  }
}

void Char::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  while (p.more_attributes ())
  {
    const ::xercesc::DOMAttr& i (p.next_attribute ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    if (n.name () == "code" && n.namespace_ ().empty ())
    {
      this->code_.set (code_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "offset" && n.namespace_ ().empty ())
    {
      this->offset_.set (offset_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "rect" && n.namespace_ ().empty ())
    {
      this->rect_.set (rect_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "width" && n.namespace_ ().empty ())
    {
      this->width_.set (width_traits::create (i, f, this));
      continue;
    }
  }

  if (!code_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "code",
      "");
  }

  if (!offset_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "offset",
      "");
  }

  if (!rect_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "rect",
      "");
  }

  if (!width_.present ())
  {
    throw ::xsd::cxx::tree::expected_attribute< char > (
      "width",
      "");
  }
}

Char* Char::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class Char (*this, f, c);
}

Char& Char::
operator= (const Char& x)
{
  if (this != &x)
  {
    static_cast< ::xml_schema::type& > (*this) = x;
    this->code_ = x.code_;
    this->offset_ = x.offset_;
    this->rect_ = x.rect_;
    this->width_ = x.width_;
  }

  return *this;
}

Char::
~Char ()
{
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

::std::auto_ptr< ::Font >
Font_ (const ::std::string& u,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  return ::std::auto_ptr< ::Font > (
    ::Font_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::Font >
Font_ (const ::std::string& u,
       ::xml_schema::error_handler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::auto_ptr< ::Font > (
    ::Font_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::Font >
Font_ (const ::std::string& u,
       ::xercesc::DOMErrorHandler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::auto_ptr< ::Font > (
    ::Font_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::Font >
Font_ (::std::istream& is,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::Font_ (isrc, f, p);
}

::std::auto_ptr< ::Font >
Font_ (::std::istream& is,
       ::xml_schema::error_handler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::Font_ (isrc, h, f, p);
}

::std::auto_ptr< ::Font >
Font_ (::std::istream& is,
       ::xercesc::DOMErrorHandler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::Font_ (isrc, h, f, p);
}

::std::auto_ptr< ::Font >
Font_ (::std::istream& is,
       const ::std::string& sid,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::Font_ (isrc, f, p);
}

::std::auto_ptr< ::Font >
Font_ (::std::istream& is,
       const ::std::string& sid,
       ::xml_schema::error_handler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::Font_ (isrc, h, f, p);
}

::std::auto_ptr< ::Font >
Font_ (::std::istream& is,
       const ::std::string& sid,
       ::xercesc::DOMErrorHandler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::Font_ (isrc, h, f, p);
}

::std::auto_ptr< ::Font >
Font_ (::xercesc::InputSource& i,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  return ::std::auto_ptr< ::Font > (
    ::Font_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::Font >
Font_ (::xercesc::InputSource& i,
       ::xml_schema::error_handler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::auto_ptr< ::Font > (
    ::Font_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::Font >
Font_ (::xercesc::InputSource& i,
       ::xercesc::DOMErrorHandler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::auto_ptr< ::Font > (
    ::Font_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::Font >
Font_ (const ::xercesc::DOMDocument& doc,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  if (f & ::xml_schema::flags::keep_dom)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      static_cast< ::xercesc::DOMDocument* > (doc.cloneNode (true)));

    return ::std::auto_ptr< ::Font > (
      ::Font_ (
        d, f | ::xml_schema::flags::own_dom, p));
  }

  const ::xercesc::DOMElement& e (*doc.getDocumentElement ());
  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (n.name () == "Font" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::Font > r (
      ::xsd::cxx::tree::traits< ::Font, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "Font",
    "");
}

::std::auto_ptr< ::Font >
Font_ (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d,
       ::xml_schema::flags f,
       const ::xml_schema::properties&)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
    ((f & ::xml_schema::flags::keep_dom) &&
     !(f & ::xml_schema::flags::own_dom))
    ? static_cast< ::xercesc::DOMDocument* > (d->cloneNode (true))
    : 0);

  ::xercesc::DOMDocument& doc (c.get () ? *c : *d);
  const ::xercesc::DOMElement& e (*doc.getDocumentElement ());

  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (f & ::xml_schema::flags::keep_dom)
    doc.setUserData (::xml_schema::dom::tree_node_key,
                     (c.get () ? &c : &d),
                     0);

  if (n.name () == "Font" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::Font > r (
      ::xsd::cxx::tree::traits< ::Font, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "Font",
    "");
}

::std::auto_ptr< ::Char >
Char_ (const ::std::string& u,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  return ::std::auto_ptr< ::Char > (
    ::Char_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::Char >
Char_ (const ::std::string& u,
       ::xml_schema::error_handler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::auto_ptr< ::Char > (
    ::Char_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::Char >
Char_ (const ::std::string& u,
       ::xercesc::DOMErrorHandler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::auto_ptr< ::Char > (
    ::Char_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::Char >
Char_ (::std::istream& is,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::Char_ (isrc, f, p);
}

::std::auto_ptr< ::Char >
Char_ (::std::istream& is,
       ::xml_schema::error_handler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::Char_ (isrc, h, f, p);
}

::std::auto_ptr< ::Char >
Char_ (::std::istream& is,
       ::xercesc::DOMErrorHandler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::Char_ (isrc, h, f, p);
}

::std::auto_ptr< ::Char >
Char_ (::std::istream& is,
       const ::std::string& sid,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::Char_ (isrc, f, p);
}

::std::auto_ptr< ::Char >
Char_ (::std::istream& is,
       const ::std::string& sid,
       ::xml_schema::error_handler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::Char_ (isrc, h, f, p);
}

::std::auto_ptr< ::Char >
Char_ (::std::istream& is,
       const ::std::string& sid,
       ::xercesc::DOMErrorHandler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::Char_ (isrc, h, f, p);
}

::std::auto_ptr< ::Char >
Char_ (::xercesc::InputSource& i,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  return ::std::auto_ptr< ::Char > (
    ::Char_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::Char >
Char_ (::xercesc::InputSource& i,
       ::xml_schema::error_handler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::auto_ptr< ::Char > (
    ::Char_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::Char >
Char_ (::xercesc::InputSource& i,
       ::xercesc::DOMErrorHandler& h,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::auto_ptr< ::Char > (
    ::Char_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::Char >
Char_ (const ::xercesc::DOMDocument& doc,
       ::xml_schema::flags f,
       const ::xml_schema::properties& p)
{
  if (f & ::xml_schema::flags::keep_dom)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      static_cast< ::xercesc::DOMDocument* > (doc.cloneNode (true)));

    return ::std::auto_ptr< ::Char > (
      ::Char_ (
        d, f | ::xml_schema::flags::own_dom, p));
  }

  const ::xercesc::DOMElement& e (*doc.getDocumentElement ());
  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (n.name () == "Char" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::Char > r (
      ::xsd::cxx::tree::traits< ::Char, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "Char",
    "");
}

::std::auto_ptr< ::Char >
Char_ (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d,
       ::xml_schema::flags f,
       const ::xml_schema::properties&)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
    ((f & ::xml_schema::flags::keep_dom) &&
     !(f & ::xml_schema::flags::own_dom))
    ? static_cast< ::xercesc::DOMDocument* > (d->cloneNode (true))
    : 0);

  ::xercesc::DOMDocument& doc (c.get () ? *c : *d);
  const ::xercesc::DOMElement& e (*doc.getDocumentElement ());

  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (f & ::xml_schema::flags::keep_dom)
    doc.setUserData (::xml_schema::dom::tree_node_key,
                     (c.get () ? &c : &d),
                     0);

  if (n.name () == "Char" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::Char > r (
      ::xsd::cxx::tree::traits< ::Char, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "Char",
    "");
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

