#include "Texture.h"
#include <IL/il.h>
#include <IL/ilu.h>

Texture::Texture()
: m_texId(0),
  m_texWidth(0),
  m_texHeight(0),
  m_imgWidth(0),
  m_imgHeight(0),
  m_pixels(NULL)
{

}

Texture::~Texture()
{
    Clean();
}

bool Texture::LoadFromFile(const std::string& path)
{
    bool isTextureLoaded = false;
    ILuint imgID = 0;

    // generate image id
    ilGenImages(1, &imgID);

    // binding image id
    ilBindImage(imgID);

    // loading the image
    ILboolean success = ilLoadImage(path.c_str());

    if(success == IL_TRUE) 
    {
        // make sure the pixel data is RGBA
        success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    }

    if(success == IL_TRUE) 
    {
        // getting image dimensions
        GLuint imgWidth = (GLuint) ilGetInteger(IL_IMAGE_WIDTH);
        GLuint imgHeight = (GLuint) ilGetInteger(IL_IMAGE_HEIGHT);
        // getting texture dimensions (as nearest power of 2)
        GLuint texWidth = NearestPower2(imgWidth);
        GLuint texHeight = NearestPower2(imgHeight);

        if(imgWidth != texWidth || imgHeight != texHeight)
        {
            // place the image in the upper left
            iluImageParameter(ILU_PLACEMENT, ILU_UPPER_LEFT);   
            // resize the image
            iluEnlargeCanvas((int)texWidth, (int)texHeight, 1);
        }

        // load the texture in m_pixelsgi
        isTextureLoaded = LoadFromPixels32(
            (GLuint *) ilGetData(), // pixels array
            imgWidth,
            imgHeight,
            texWidth,
            texHeight
        );
    }

    // delete file from memory
    ilDeleteImages(1, &imgID);

    if(!isTextureLoaded)
    {
        printf( "Unable to load %s\n", path.c_str() );
    }

    return isTextureLoaded;
}

bool Texture::LoadFromPixels32(GLuint *pixels, 
    GLuint imgWidth, GLuint imgHeight, 
    GLuint texWidth, GLuint texHeight)
{
    Clean();

    // set dimensions
    m_texWidth = texWidth;
    m_texHeight = texHeight;
    m_imgWidth = imgWidth;
    m_imgHeight = imgHeight;

    // assign a texture id
    glGenTextures(1, &m_texId);

    // bind texture id
    glBindTexture(GL_TEXTURE_2D, m_texId);

    // generate texture
    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGBA, 
        m_texWidth, 
        m_texHeight,  
        0, 
        GL_RGBA, 
        GL_UNSIGNED_BYTE, 
        pixels
    );

    // set texture parameters 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // ubind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    GLenum error = glGetError();
    if(error != GL_NO_ERROR)
    {
        printf( "Error loading texture from %p pixels! %s\n", 
            pixels, gluErrorString( error ) ); 
        return false;
    }

    return true;
}

void Texture::Clean()
{
    // delete texture
    if(m_texId != 0) 
    {
        // delete texture from the GL context
        glDeleteTextures(1, &m_texId);
        m_texId = 0;
    }

    // delete pixels
    if(m_pixels != NULL)
    {
        delete[] m_pixels;
        m_pixels = NULL;
    }

    // reset the texture dimensions
    m_imgWidth = 0;
    m_imgHeight = 0;
    m_texWidth = 0;
    m_texHeight = 0;
}

GLuint Texture::GetTexId() const
{
    return m_texId;
}

GLuint Texture::GetTexWidth() const
{
    return m_texWidth;
}

GLuint Texture::GetTexHeight() const
{
    return m_texHeight;
}

GLuint Texture::GetImgWidth() const
{
    return m_imgWidth;
}

GLuint Texture::GetImgHeight() const
{
    return m_imgHeight;
}

GLuint* Texture::GetTexPixels() 
{
    return m_pixels;
}

GLuint Texture::NearestPower2(GLuint n)
{
    if( n != 0 ) 
    { 
        n--; 
        n |= (n >> 1);
        n |= (n >> 2);
        n |= (n >> 4);
        n |= (n >> 8);
        n |= (n >> 16);
        n++; 
    } 
    return n; 
}

