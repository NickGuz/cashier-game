#ifndef BAG_H
#define BAG_H

#include "Texture.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Bag
{
    public:
        Bag();
        ~Bag();
        void free();
        void load(SDL_Renderer* renderer);
        void update();
        void render();
        SDL_Rect getCollider();

        bool isOverBag;

        private:
            Texture closedBag;
            Texture openBag;
            SDL_Rect collider;
            int bagHeight, bagWidth;
            SDL_Renderer* mRenderer;

};

#endif