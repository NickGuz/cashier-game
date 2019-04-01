#include "Store.h"

std::vector<std::string> Food::usedFoods(1);

Store::Store()
{
    mRenderer = StateMachine::mRenderer;
    mBackground.loadFromFile("img/store/store_bg.png", mRenderer);
    mCashRegister.loadFromFile("img/store/cash_reg.png", mRenderer);
    dbox.setRenderer(mRenderer);
    dbox.addText("Day 1");
    dbox.init();
    food.init(mRenderer);
    mScanner.load(mRenderer);
    mBag.load(mRenderer);

    foodsBagged = 0;

    // init clock font and color
    clockFont = TTF_OpenFont("fonts/comic.ttf", 32);

    if (clockFont == NULL)
    {
        printf("Failed to load clock font! SDL_ttf Error: %s\n", TTF_GetError());
    }

    clockColor = {255, 255, 255, 255};

    // init clock
    clock.loadFromRenderedText("9:00 AM", clockColor, clockFont, mRenderer);
    clockHour = 9;
    clockMinute = 0;
}

void Store::handleEvent(SDL_Event* e)
{

}

void Store::spawnCustomer()
{
    Food::usedFoods.clear();
    mCustomer.free();
    foodsBagged = 0;

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

    // save old vals to render foods in correct place
    int old_x = 0;
    int prevWidth = 0;

    for (int i = 0; i < randInt; i++)
    {
        foods[i].init(mRenderer);
        foods[i].load(old_x, prevWidth);

        // save old vals to render foods in correct place
        old_x = foods[i].getX();
        prevWidth = foods[i].getWidth();
    }

    // display and increment customer dialogue
    dbox.addText(mCustomer.getOpener());
    dbox.next();
}

void Store::update(Input* input)
{
    if (input->isKeyPressed(SDL_SCANCODE_SPACE))
    {
        if (!dbox.next())
        {
            //dbox.free();
            spawnCustomer();
            if (!timer.isStarted())
                timer.start();
        }
    }

    // check if day is over
    if (clockHour == 5)
    {
        StateMachine::setNextState(STATE_RESULTS);
    }

    // handle food movement/grabbing
    if (!foods.empty())
    {
        for (int i = 0; i < foods.size(); i++)
        {
            if (mHand.collides(foods[i].getCollider()))
            {
                // getState 0 is neutral hand. so if grabbing, don't allow to grab more
                if (input->isMousePressed())
                {
                    foods[i].move(mHand.getCollider());
                    SDL_Rect c = foods[i].getCollider();

                    // check for scanning
                    if (foods[i].collides(mScanner.getCollider()))
                    {
                        std::cout << "scanned" << std::endl;
                        mScanner.scanned = true;
                    }
                    else
                    {
                        mScanner.scanned = false;
                    }

                    // check for dropping food in bag
                    if (foods[i].collides(mBag.getCollider()) && input->isMousePressed())
                    {
                        mBag.isOverBag = true;
                    }
                    else
                    {
                        mBag.isOverBag = false;  
                    }

                    // set state to grabbing
                    mHand.setState(GRABBING);
                }

                // check if user bags item
                if (mBag.isOverBag && input->isMouseReleased())
                {
                    std::cout << "bagged" << std::endl;
                    foods[i].free();
                    foodsBagged++;
                    mBag.isOverBag = false;
                }
            }
        }

        // spawn new customer if all items are bagged
        if (foodsBagged == foods.size())
        {
            //dbox.free();
            spawnCustomer();
        }
    }
}

void Store::render()
{
    mBackground.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, mRenderer);
    mCustomer.render(650, 50, NULL, NULL, mRenderer);
    mCashRegister.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, mRenderer);
    mScanner.render(); // count frames
    mBag.render();

    for (int i = 0; i < foods.size(); i++)
    {
        foods[i].render();
    }

    // maybe clear on spacebar and then only render if customer has text, don't check for dbox.next()
    dbox.render();

    // reset timer if hour passes
    if (clockMinute > 59) 
    {
        timer.stop();
        timer.start();

        clockHour++;
        if (clockHour > 12)
            clockHour = 1;
    }

    // this determines how fast time passes (currently fast for testing purposes)
    clockMinute = timer.getTicks() / 100;

    std::stringstream time_str;
    time_str << clockHour << ":" << std::setfill('0') << std::setw(2) << clockMinute;

    // change render text on clock, might be terrible for performance
    clock.loadFromRenderedText(time_str.str(), clockColor, clockFont, mRenderer);
    clock.render(SCREEN_WIDTH - clock.getWidth(), 0, clock.getWidth(), clock.getHeight(), mRenderer);
}

void Store::free()
{
    mBackground.free();
    mCashRegister.free();
    mRenderer = NULL;
    dbox.free();
    mBag.free();
    mScanner.free();
    Food::usedFoods.clear();

    for (int i = 0; i < foods.size(); i++)
    {
        foods[i].free();
    }
}