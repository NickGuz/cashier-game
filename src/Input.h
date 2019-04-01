#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

#define MAX_KEYS 284

class Input
{
    public:
        Input();
        ~Input();
        void onEvent(SDL_Event* e);
        void onExit();
        void onKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 scancode);
        bool isKeyPressed(SDL_Keycode sym);
        bool isMousePressed();
        bool isMouseReleased();
        void free();
        
        std::vector<bool> keysPressed;

    private:
        bool mousePressed;
        bool mouseReleased;
};


#endif