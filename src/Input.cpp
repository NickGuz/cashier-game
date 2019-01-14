#include "Input.h"

Input::Input()
{
    std::vector<bool> keysPressed = std::vector<bool>(MAX_KEYS);

    // change to max buttons
    //std::vector<bool> buttonsPressed = std::vector<bool>(MAX_KEYS);
}

Input::~Input()
{
    free();
}

void Input::onEvent(SDL_Event* e)
{
    //onMButtonUp(e);
    mouseReleased = false;
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
            //buttonsPressed[e->button.button] = true;
            //std::cout << e->button.button << std::endl;
            mousePressed = true;
            mouseReleased = false;
            break;

        case SDL_MOUSEBUTTONUP:
            //buttonsPressed[e->button.button] = false;
            //onMButtonUp();
            mousePressed = false;
            mouseReleased = true;
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

bool Input::isMouseReleased()
{
    return mouseReleased;
}

bool Input::onMButtonUp(SDL_Event* e)
{
    if (e->type == SDL_MOUSEBUTTONUP)
        return true;

    return false;
}

void Input::free()
{
    keysPressed.clear();
}
