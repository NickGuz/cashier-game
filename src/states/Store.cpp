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

    //mHand = &Globals::gHand;
}

/*
Store::~Store()
{
    free();
}
*/

void Store::handleEvent(SDL_Event* e)
{

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
}

void Store::update(Input* input)
{
    if (input->isKeyPressed(SDLK_SPACE))
    {
        if (!dbox.next())
        {
            dbox.free();
            spawnCustomer();
        }
    }

    // handle food movement/grabbing
    if (!foods.empty())
    {
        for (int i = 0; i < foods.size(); i++)
        {
            if (mHand.collides(foods[i].getCollider()))
            {
                //std::cout << "colliding" << std::endl;

                // getState 0 is neutral hand. so if grabbing, don't allow to grab more
                if (input->isMousePressed()) // && mHand.getState() == NEUTRAL)
                {
                    //std::cout << "grabbing" << std::endl;

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

                // doesn't work because old foods are still over bag and being bagged again

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

        //std::cout << "bagged: " << foodsBagged << " foods size: " << foods.size() << std::endl;
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

    /*
    int xval = SCREEN_WIDTH * 0.55;
    for (int i = 0; i < foods.size(); i++)
    {
        foods[i].render(xval, (SCREEN_HEIGHT * 0.72) - foods[i].getHeight(), NULL, NULL);
        xval = (xval + foods[i].getWidth()) + 30;
    }
    */

    dbox.render();
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