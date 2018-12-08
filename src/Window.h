#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Input.h"
#include "Texture.h"
#include "Hand.h"
#include "Person.h"
#include "DialogueBox.h"
#include "StateMachine.h"
#include "states/Interview.h"
#include "states/TitleScreen.h"
#include "states/Store.h"

class Window
{
    public:
        Window();
        ~Window();
        bool init();
        bool loadMedia();
        void close();
        void update();
        //TTF_Font* mFont;
        //TTF_Font* gFont;
        
        // the window renderer
        SDL_Renderer* mRenderer;

    private:
        // the window to render to
        SDL_Window* mWindow;

        // the window renderer
        //SDL_Renderer* mRenderer;

        TTF_Font* gFont;

        // textures
        Hand mCursor;
        Texture mTextTexture;

        // these prob will be in state
        StateMachine* state;

        // input
        int mouse_x, mouse_y;
};

#endif