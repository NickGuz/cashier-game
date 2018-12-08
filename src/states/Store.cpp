#include "Store.h"

Store::Store(SDL_Renderer* renderer)
{
    mRenderer = renderer;
    mBackground.loadFromFile("img/store/store_bg.png", mRenderer);
    mCashRegister.loadFromFile("img/store/cash_reggie.png", mRenderer);
    dbox.setRenderer(mRenderer);
    dbox.addText("Day 1");
    dbox.init();
}

void Store::handleEvent(SDL_Event* e)
{
    std::cout << "event" << std::endl;
    /*
    if (e->type == SDL_KEYDOWN)
    {
        switch (e->key.keysym.sym)
        {
            case SDLK_SPACE:
                dayStart();
                dbox.next();
                std::cout << "day start" << std::endl;
                break;
        }
    }
    */
}

void Store::dayStart()
{
    //dbox.addText("Start");
    //dbox.init();
}

void Store::update(Input input)
{
    if (input.isKeyPressed(SDLK_SPACE))
    {
        std::cout << "yes" << std::endl;
        if (!dbox.next())
        {
            dbox.free();
        }
    }
}

void Store::render()
{
    mBackground.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, mRenderer);
    mCashRegister.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, mRenderer);
    dbox.render();
}

void Store::free()
{
    mBackground.free();
    mCashRegister.free();
    mRenderer = NULL;
    dbox.free();
}