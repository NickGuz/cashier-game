#include "Input.h"

Input::Input()
{
    /*
    for (int i = 0; i < MAX_KEYS; i++)
    {
        keysPressed[i] = false;
    }
    */
    std::vector<bool> keysPressed = std::vector<bool>(MAX_KEYS);
}

Input::~Input()
{
    free();
}

void Input::onEvent(SDL_Event* e)
{
    switch (e->type)
    {
        case SDL_QUIT:
            onExit();
            break;

        case SDL_KEYDOWN:
            onKeyDown(e->key.keysym.sym, e->key.keysym.mod, e->key.keysym.scancode);
            break;
    }
}

void Input::onExit()
{

}

void Input::onKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 scancode)
{
    keysPressed[sym] = true;
}

bool Input::isKeyPressed(SDL_Keycode sym)
{
    return keysPressed[sym];
}

void Input::free()
{
    keysPressed.clear();
}
