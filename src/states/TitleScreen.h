#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "../Texture.h"
#include "../StateMachine.h"
#include "../Collider.h"

class TitleScreen : public StateMachine
{
    public:
        TitleScreen();
        void render();
        void update(Input* input);
        void free();

    private:
        Texture mStartButton;
        Texture mQuitButton;
        TTF_Font* mFont;
        SDL_Color textColor;

        // hitbox
        SDL_Rect startCollider;
        SDL_Rect quitCollider;
};

#endif