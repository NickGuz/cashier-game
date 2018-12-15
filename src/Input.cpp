#include "Input.h"

Input::Input()
{
    std::vector<bool> keysPressed = std::vector<bool>(MAX_KEYS);
    mousePressed = false;
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
            if (e->key.repeat == 0)
                onKeyDown(e->key.keysym.sym, e->key.keysym.mod, e->key.keysym.scancode);
            break;

        case SDL_MOUSEBUTTONDOWN:
            mousePressed = true;
            break;

        case SDL_MOUSEBUTTONUP:
            mousePressed = false;
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

bool Input::isMousePressed() //SDL_Keycode sym)
{
    return mousePressed;
}

void Input::free()
{
    keysPressed.clear();
}
