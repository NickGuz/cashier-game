#ifndef COLLIDER_H
#define COLLIDER_H

#include <SDL2/SDL.h>

class Collider
{
    public:
        Collider();
        ~Collider();
        void init(int w, int h, int x, int y);
        bool collides(SDL_Rect obj);
        SDL_Rect getCollider();

    private:
        SDL_Rect collider_rect;
};

#endif