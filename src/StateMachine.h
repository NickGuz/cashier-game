#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "Texture.h"
#include "Input.h"
#include "Hand.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Interview;
class Store;
class TitleScreen;
class Results;

enum GameStates
{
    STATE_NULL,
    STATE_TITLE,
    STATE_INTERVIEW,
    STATE_STORE,
    STATE_RESULTS,
    STATE_QUIT
};

class StateMachine
{
    public:
        StateMachine();
        ~StateMachine();
        virtual void update(Input* input) = 0;
        //virtual void update(Scene& scene);
        virtual void render() = 0;
        virtual void free() = 0;

        static void init(SDL_Renderer* renderer);

        // state status manager
        static void setNextState(int newState);

        // state changer
        static void changeState();

        // hand stuff
        static void handleMouse(SDL_Event* e);
        static void renderHand();

        static Hand mHand;

        // state variables
        inline static int stateID = NULL;
        inline static int nextState = NULL;

        // game state object
        inline static StateMachine* currentState = NULL;

        static int mouse_x, mouse_y;

    protected:
        inline static SDL_Renderer* mRenderer = NULL;
};

#endif