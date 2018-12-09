#include "Store.h"

//std::vector<std::string> Food::usedFoods();
std::vector<std::string> Food::usedFoods(1);

Store::Store(SDL_Renderer* renderer)
{
    mRenderer = renderer;
    mBackground.loadFromFile("img/store/store_bg.png", mRenderer);
    mCashRegister.loadFromFile("img/store/cash_reggie.png", mRenderer);
    dbox.setRenderer(mRenderer);
    dbox.addText("Day 1");
    dbox.init();
    food.init(mRenderer);
}

void Store::handleEvent(SDL_Event* e)
{
    std::cout << "event" << std::endl;
}

void Store::dayStart()
{
    //dbox.addText("Start");
    //dbox.init();
}

void Store::spawnCustomer()
{
    // maybe?
    Food::usedFoods.clear();
    mCustomer.free();

    // initialize (seed) engine
    std::random_device rd;

    // random number engine used (mersenne-twister)
    std::mt19937 rng(rd());

    // get random int from 0 to 3 inclusive
    std::uniform_int_distribution<int> uni(1, 3);

    int randInt = uni(rng);

    // create vector of customer's foods
    foods.resize(0);

    for (int i = 0; i < randInt; i++)
    {
        foods.push_back(Food());
    }

    mCustomer.create(mRenderer);
    for (int i = 0; i < randInt; i++)
    {
        foods[i].init(mRenderer);
        foods[i].load();
    }
}

void Store::update(Input input)
{
    if (input.isKeyPressed(SDLK_SPACE))
    {
        std::cout << "yes" << std::endl;
        if (!dbox.next())
        {
            dbox.free();
            spawnCustomer();
        }
    }
}

void Store::render()
{
    mBackground.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, mRenderer);
    mCustomer.render(650, 50, NULL, NULL, mRenderer);
    mCashRegister.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, mRenderer);
    //food.render(SCREEN_WIDTH * 0.65, (SCREEN_HEIGHT * 0.7) - food.getHeight(), NULL, NULL);

    int xval = SCREEN_WIDTH * 0.55;
    for (int i = 0; i < foods.size(); i++)
    {
        foods[i].render(xval, (SCREEN_HEIGHT * 0.72) - foods[i].getHeight(), NULL, NULL);
        xval = (xval + foods[i].getWidth()) + 30;
    }

    dbox.render();
}

void Store::free()
{
    mBackground.free();
    mCashRegister.free();
    mRenderer = NULL;
    dbox.free();
}