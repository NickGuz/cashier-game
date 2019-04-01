#ifndef SCANNER_H
#define SCANNER_H

#include "Texture.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Scanner : public Texture
{
    public:
        Scanner();
        ~Scanner();
        void free();
        void load(SDL_Renderer* renderer);
        void update();
        void render();
        SDL_Rect getCollider();
        bool scanned;
        int scannedFrames;

    private:
        Texture scanDefault;
        Texture scanScanned;
        int scanHeight, scanWidth;
        SDL_Rect collider;
        SDL_Renderer* mRenderer;
};

#endif