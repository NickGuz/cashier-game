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
        bool isMousePressed(); // SDL_Keycode sym);
        bool isMouseReleased();
        bool onMButtonUp(SDL_Event* e);
        void free();

        std::vector<bool> keysPressed;
        std::vector<bool> buttonsPressed;

    private:
        bool mousePressed;
        bool mouseReleased;
};


#endif