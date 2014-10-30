#include "Drawing.h"
#include <cassert>

void DrawLine(
    const Vector2& origin,
    const Vector2& end,
    LineType type,
    GLfloat width
)
{
    glPushMatrix();
    glLineWidth( width );

    if( type != SOLID )
    {
        glEnable ( GL_LINE_STIPPLE );
        glLineStipple (1, type);
    }

    glBegin( GL_LINES );
        glVertex2f(origin.x, origin.y);
        glVertex2f(end.x, end.y);
    glEnd();

    if( type != SOLID )
    {
        glDisable(GL_LINE_STIPPLE);
    }

    glPopMatrix();
}

void DrawQuad(
    GLfloat minX, GLfloat minY,
    GLfloat maxX, GLfloat maxY
)
{
    glPushMatrix();
    glBegin( GL_QUADS );
        glColor3f(1.f, 1.f, 1.f); // white
        glVertex2f(minX, minY);
        glVertex2f(maxX, minY);
        glVertex2f(maxX, maxY);
        glVertex2f(minX, maxY);
    glEnd();
    glPopMatrix();
}

void DrawTriangle(
    GLfloat x1, GLfloat y1,
    GLfloat x2, GLfloat y2,
    GLfloat x3, GLfloat y3
)
{
    glPushMatrix();
    glBegin(GL_TRIANGLES);
        glColor3f(1.f, 1.f, 1.f); // white
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
        glVertex2d(x3, x3);
    glEnd();
    glPopMatrix();
}

void DrawPolygon(const std::vector<Vector2> &points, GLfloat lineWidth)
{
    glPushMatrix();
    glLineWidth(lineWidth);
    glBegin(GL_LINE_LOOP);
    for(auto it = points.begin(); it != points.end(); it++)
    {
        Vector2 p = *it;
        glVertex2d(p.x, p.y);
    }
    glEnd();
    glPopMatrix();
}
