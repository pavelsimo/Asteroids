#ifndef TEXTURE_H
#define TEXTURE_H

#include "LOpenGL.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include <cstdio>
#include <iostream>

class Texture 
{
    public:
        Texture();
        ~Texture();

        bool LoadFromFile(const std::string& path);
        bool LoadFromPixels32(GLuint *pixels, 
            GLuint imgWidth, GLuint imgHeight, 
            GLuint texWidth, GLuint texHeight);
        void Clean();
        GLuint GetTexId() const;
        GLuint GetTexWidth() const;
        GLuint GetTexHeight() const;
        GLuint GetImgWidth() const;
        GLuint GetImgHeight() const;
        GLuint* GetTexPixels();
    private:
        GLuint NearestPower2(GLuint n);

        GLuint m_texId;
        GLuint* m_pixels;
        GLuint m_texWidth;
        GLuint m_texHeight;
        GLuint m_imgWidth;
        GLuint m_imgHeight;
};

#endif