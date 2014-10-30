#ifndef __DRAWING_H_
#define __DRAWING_H_

#include "LOpenGL.h"
#include "Vector2.h"

enum LineType {
    SOLID,
    DOTTED = 0x0101,
    DASHED = 0x00FF
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


#endif // __DRAWING_H_