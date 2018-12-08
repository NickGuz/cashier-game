#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include "Texture.h"

class Hand : public Texture
{
    public:
        Hand();
        ~Hand();

        // handle open and close animation on hand
        void handleEvent(SDL_Event* e);

        void render(int x, int y, SDL_Renderer* renderer);

        //void free();

        // maybe just use texture class in future?
        SDL_Texture* loadFromFile(std::string path, SDL_Renderer* renderer);
        bool loadHands(SDL_Renderer* renderer);

        // simplified render function since we won't ever need to scale hand
        // (yet)
        //void render(int x, int y, SDL_Renderer* renderer);

        // ideally handle hand open and close logic in here
        // + movement tracking
        // but that needs to be in main game loop for now

    private:
        // the actual hardware texture
        SDL_Texture* mClosedHand;
        SDL_Texture* mOpenHand;
        int mWidth;
        int mHeight;
        bool mIsClosed;

        // doesnt work because in loadFromFile we are writing to parent mTexture
        // so then when overriding render, the texture doesnt exist
};