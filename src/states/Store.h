#ifndef STORE_H
#define STORE_H

#include "../StateMachine.h"
#include "../DialogueBox.h"
#include "../Input.h"
#include "../Food.h"
#include "../Person.h"
#include "../Hand.h"
#include "../Scanner.h"
#include "../Window.h"
#include "../Bag.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iomanip>

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
        Bag mBag;

        // create vector of customer's foods
        std::vector<Food> foods;
        int foodsBagged;

        // for clock timer
        Timer timer;
        TTF_Font* clockFont;
        SDL_Color clockColor;
        Texture clock;
        int clockHour, clockMinute;
};

#endif