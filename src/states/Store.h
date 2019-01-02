#ifndef STORE_H
#define STORE_H

/* TODO:
** 
** 1. Start day, person comes on screen, gives food.
** 2. Implement grabbing.
** 3. Implement scanning or physics.
*/

#include "../StateMachine.h"
#include "../DialogueBox.h"
#include "../Input.h"
#include "../Food.h"
#include "../Person.h"
#include "../Hand.h"
#include "../Scanner.h"
#include "../Window.h"
#include <SDL2/SDL.h>

class Store : public StateMachine
{
    public:
        Store();
        // virtual destructor but idk what to do with it yet
        //~Store();
        void render();
        void free();
        void handleEvent(SDL_Event* e);
        void update(Input* input);
        void dayStart();
        void spawnCustomer();

    private:
        Food food;
        Person mCustomer;
        Texture mBackground;
        Texture mCashRegister;
        DialogueBox dbox;
        Scanner mScanner;
        // inherit this from statemachine
        //SDL_Renderer* mRenderer;

        // create vector of customer's foods
        std::vector<Food> foods;

        //Hand* mHand;
};

#endif