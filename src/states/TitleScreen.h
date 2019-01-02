#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "../Texture.h"
#include "../StateMachine.h"

class TitleScreen : public StateMachine
{
    public:
        TitleScreen();
        //~TitleScreen();
        void render();
        void update(Input* input);
        void free();
        //bool handleStart(SDL_Event* e, int *mouse_x, int *mouse_y);
        //bool handleQuit(SDL_Event* e, int *mouse_x, int *mouse_y);

    private:
        //SDL_Renderer* mRenderer;
        Texture mStartButton;
        Texture mQuitButton;
        TTF_Font* mFont;
        SDL_Color textColor;
};



#endif