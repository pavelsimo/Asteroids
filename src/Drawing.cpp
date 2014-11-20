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

void DrawPolygon(
    const std::vector<Vector2> &points,
    GLfloat x,
    GLfloat y,
    GLfloat degrees,
    GLfloat lineWidth
)
{
    glPushMatrix();
    glLineWidth(lineWidth);
    glTranslatef(x, y, 0.f);
    glRotatef(degrees, 0.f, 0.f, 1.f);
    glBegin(GL_LINE_LOOP);
    for(auto it = points.begin(); it != points.end(); it++)
    {
        Vector2 p = *it;
        glVertex2d(p.x, p.y);
    }
    glEnd();
    glPopMatrix();
}

void DrawCircle(
    GLfloat x,
    GLfloat y,
    GLfloat radius,
    GLfloat sides,
    GLfloat lineWidth
)
{
    assert(sides != 0);

    glPushMatrix();
    glLineWidth(lineWidth);
    glTranslatef(x, y, 0.f);
    glBegin(GL_LINE_LOOP);
    int offset = 360 / sides;
    for(int angle = 0; angle < 360; angle+=offset)
    {
        GLfloat heading = angle * PI  / 180;
        glVertex2d(cos(heading) * radius, sin(heading) * radius);
    }
    glEnd();
    glPopMatrix();
}

void DrawTexture(
        GLfloat x, GLfloat y,
        GLuint texId,
        GLuint imgWidth, GLuint imgHeight,
        GLuint texWidth, GLuint texHeight,
        Rect* clip,
        GLfloat scale
)
{
    if(texId != 0)
    {
        glPushMatrix();

        GLfloat texTop = 0.f;
        GLfloat texBottom = (GLfloat)imgHeight / (GLfloat)texHeight;
        GLfloat texLeft = 0.f;
        GLfloat texRight = (GLfloat)imgWidth / (GLfloat)texWidth;
        GLfloat quadWidth = imgWidth;
        GLfloat quadHeight = imgHeight;

        if(clip != NULL)
        {
            texLeft = clip->x / texWidth;
            texRight = (clip->x + clip->w) / texWidth;
            texTop = clip->y / texHeight;
            texBottom = (clip->y + clip->h) / texHeight;

            // vertex coordinates
            quadWidth = clip->w;
            quadHeight = clip->h;
        }

        quadWidth  *= scale;
        quadHeight *= scale;

        // move to rendering point
        glTranslatef(x, y, 0.f);

        // set texture id
        glBindTexture(GL_TEXTURE_2D, texId);

        // render texture quad
        glBegin(GL_QUADS);
        glTexCoord2f(texLeft,  texTop);    glVertex2f(0.f,       0.f);
        glTexCoord2f(texRight, texTop);    glVertex2f(quadWidth, 0.f);
        glTexCoord2f(texRight, texBottom); glVertex2f(quadWidth, quadHeight);
        glTexCoord2f(texLeft,  texBottom); glVertex2f(0.f,       quadHeight);
        glEnd();

        // unbind the texture
        glBindTexture(GL_TEXTURE_2D, 0);

        glPopMatrix();
    }
}

void DrawText(
        GLfloat x, GLfloat y,
        const std::string &text,
        BitmapFont* font,
        GLfloat scale,
        GLfloat glyphOffset,
        GLfloat spaceOffset,
        GLfloat lineSeparatorOffset
)
{
    GLuint texId = font->GetTexture()->GetTexId();
    GLuint imgWidth = font->GetTexture()->GetImgWidth();
    GLuint imgHeight = font->GetTexture()->GetImgHeight();
    GLuint texWidth = font->GetTexture()->GetTexWidth();
    GLuint texHeight = font->GetTexture()->GetTexHeight();

    GLfloat curX = x;
    GLfloat curY = y;
    for(int i = 0; i < text.size(); ++i)
    {
        if(text[i] == '\n' || text[i] == '\r')
        {
            curX = x;
            curY += lineSeparatorOffset;
            continue;
        }

        if(isspace(text[i])) {
            curX += spaceOffset;
            continue;
        }

        BitmapFontGlyph glyph = font->GetGlyph(text[i]);
        Rect clip;
        clip.x = glyph.x;
        clip.y = glyph.y;
        clip.w = glyph.width;
        clip.h = glyph.height;

        DrawTexture(
            curX, curY,
            texId,
            imgWidth, imgHeight,
            texWidth, texHeight,
            &clip,
            scale
        );

        curX += clip.w + glyphOffset;
    }
}
