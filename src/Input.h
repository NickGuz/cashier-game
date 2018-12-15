#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <vector>

#define MAX_KEYS 255

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
        void free();

        std::vector<bool> keysPressed;

    private:
        bool mousePressed;
};


#endif