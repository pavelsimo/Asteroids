#ifndef __WORLD_H_
#define __WORLD_H_

namespace asteroids {

    class World {
        public:
            World();
            World(const float width, const float height);
            ~World();

            void Render();
            void Update();
            void OnKeyDown(unsigned char key);
            void OnKeyUp(unsigned char key);
            void OnMouseMove(int x, int y);
            void OnMouseClick(int button, int state, int x, int y);
            float GetWidth() const;
            float GetHeight() const;
            float GetLeft() const;
            float GetRight() const;
            float GetBottom() const;
            float GetTop() const;

        private:
            float m_width;
            float m_height;
    };
}




#endif //__WORLD_H_
