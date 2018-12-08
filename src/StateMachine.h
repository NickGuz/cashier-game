#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "Texture.h"
//#include "states/Store.h"
//#include "states/Interview.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Interview;
class Store;

class StateMachine
{
    public:
        StateMachine();
        virtual ~StateMachine();
        // maybe use enum or something for this arg
        StateMachine* setState(StateMachine* state);
        virtual void free();
        void setRenderer(SDL_Renderer* renderer);

        Interview* getInterview();

        // no idea how it knows interview exists here
        Interview* interview;
        static Store store;

    protected:
        SDL_Renderer* mRenderer;
        
};

#endif