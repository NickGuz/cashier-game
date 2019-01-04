#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class Texture
{
    public:
        // initializes variables
        Texture();

        // deallocates memory
        ~Texture();

        // loads image at specified path
        bool loadFromFile(std::string path, SDL_Renderer* renderer);

        // creates image from font string
        bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer);

        // deallocates texture
        virtual void free();

        // set blending
        void setBlendMode(SDL_BlendMode blending);

        // set alpha modulation
        void setAlpha(Uint8 alpha);

        // render texture at given point
        void render(int x, int y, int w, int h, SDL_Renderer* renderer);

        // gets image dimensions
        int getWidth();
        int getHeight();

        // hitbox stuff
        bool collides();

    private:
        // the actual hardware texture
        SDL_Texture* mTexture;

        // the renderer
        //SDL_Renderer* mRenderer;

        // image dimensions
        int mWidth;
        int mHeight;
};

#endif