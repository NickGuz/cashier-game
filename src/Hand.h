#ifndef HAND_H
#define HAND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include "Texture.h"

enum states
        {
            NEUTRAL,
            GRABBING,
        };

extern states state;

class Hand : public Texture
{
    public:
        Hand();
        ~Hand();

        // handle open and close animation on hand
        void handleEvent(SDL_Event* e);
        void render(int x, int y, SDL_Renderer* renderer);
        bool collides(SDL_Rect food);
        SDL_Rect getCollider();

        // maybe just use texture class in future?
        SDL_Texture* loadFromFile(std::string path, SDL_Renderer* renderer);
        bool loadHands(SDL_Renderer* renderer);

        // simple state stuff
        void setState(int state);
        int getState();

    private:
        // the actual hardware texture
        SDL_Texture* mClosedHand;
        SDL_Texture* mOpenHand;
        int mWidth;
        int mHeight;
        bool mIsClosed;

        // maybe use statemachine or something
        int mState;

        // collision box
        SDL_Rect collider;
};

#endif