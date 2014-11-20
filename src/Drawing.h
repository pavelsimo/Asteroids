#ifndef __DRAWING_H_
#define __DRAWING_H_
#include <vector>

#include "LOpenGL.h"
#include "Vector2.h"
#include "BitmapFont.h"

enum LineType {
    SOLID,
    DOTTED = 0x0101,
    DASHED = 0x00FF
};

struct Rect
{
    Rect()
    : x(0), y(0), w(0), h(0)
    {

    }

    Rect(GLfloat _x, GLfloat _y, GLfloat _w, GLfloat _h)
    : x(_x), y(_y), w(_w), h(_h)
    {

    }

    GLfloat x;
    GLfloat y;
    GLfloat w;
    GLfloat h;
};

void DrawLine(
    const Vector2& origin,
    const Vector2& end,
    LineType type,
    GLfloat width
);

void DrawQuad(
    GLfloat minX, GLfloat minY,
    GLfloat maxX, GLfloat maxY
);

void DrawTriangle(
    GLfloat x1, GLfloat y1,
    GLfloat x2, GLfloat y2,
    GLfloat x3, GLfloat y3
);

void DrawPolygon(
    const std::vector<Vector2> &points,
    GLfloat x = 0.f,
    GLfloat y = 0.f,
    GLfloat degrees = 0.f,
    GLfloat lineWidth = 2.f
);

void DrawCircle(
    GLfloat x,
    GLfloat y,
    GLfloat radius = 5,
    GLfloat sides = 20,
    GLfloat lineWidth = 1.f
);

void DrawTexture(
        GLfloat x, GLfloat y,
        GLuint texId,
        GLuint imgWidth, GLuint imgHeight,
        GLuint texWidth, GLuint texHeight,
        Rect* clip = NULL,
        GLfloat scale = 1.0
);

void DrawText(
        GLfloat x, GLfloat y,
        const std::string &text,
        BitmapFont* font,
        GLfloat scale = 1.0,
        GLfloat glyphOffset = 3,
        GLfloat spaceOffset = 32,
        GLfloat lineSeparatorOffset = 100
);

#endif // __DRAWING_H_