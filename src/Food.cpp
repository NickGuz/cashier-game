#include "Food.h"

Food::Food()
{
    xpos = 0;
    ypos = 0;

    xvel = 0;
    yvel = 0;
}

Food::~Food()
{

}


void Food::init(SDL_Renderer* renderer)
{
    mRenderer = renderer;
}

// makes texture out of random food item
void Food::load(int old_x, int prevWidth)
{
    std::string foodFile = getRandFile("img/food");
    std::cout << foodFile << std::endl;

    if (!usedFoods.empty())
    {
        for (int i = 0; i < usedFoods.size(); i++)
        {
            if (usedFoods[i] == foodFile)
            {
                // infinite recursion very possible
                load(old_x, prevWidth);
                return;
            }
        }
    }

    usedFoods.push_back(foodFile);
    mFoodItem.loadFromFile(foodFile, mRenderer);

    // setup collision box
    collider.w = this->getWidth();
    collider.h = this->getHeight();

    // set position variables
    if (usedFoods.size() == 1)
    {
        xpos = SCREEN_WIDTH * 0.55;
    }
    else
    {
        // maybe use static variable or some shit
        // like nextxpos
        xpos = (old_x + prevWidth) + 30;
    }

    //next_xpos = (xpos + mFoodItem.getWidth()) + 30;
    ypos = (SCREEN_HEIGHT * 0.72) - mFoodItem.getHeight();
}

void Food::render()
{
    collider.x = xpos;
    collider.y = ypos;
    mFoodItem.render(xpos, ypos, NULL, NULL, mRenderer);
}

void Food::free()
{
    mRenderer = NULL;
    mFoodItem.free();
    collider.x = NULL;
    collider.y = NULL;
    collider.w = NULL;
    collider.h = NULL;
    xpos = NULL;
    ypos = NULL;
}

int Food::getWidth()
{
    return mFoodItem.getWidth();
}

int Food::getHeight()
{
    return mFoodItem.getHeight();
}

int Food::getX()
{
    return xpos;
}

int Food::getY()
{
    return ypos;
}

SDL_Rect Food::getCollider()
{
    return collider;
}

bool Food::collides(SDL_Rect obj)
{
    if (collider.x + (collider.w - 4) >= obj.x && collider.x <= obj.x + obj.w)
    {
        if (collider.y + (collider.h - 4) >= obj.y && collider.y <= obj.y + obj.h)
        {
            return true;
        }
    }

    return false;
}

void Food::move(SDL_Rect hand)
{
    // we need center of item to be in center of hand
    xpos = (hand.x + (hand.w * 0.3)) - (mFoodItem.getWidth() / 2);
    collider.x = xpos;

    ypos = (hand.y + (hand.h * 0.10)) - (mFoodItem.getHeight() / 2);
    collider.y = ypos;

    /*
    // move left or right
    xpos += xvel;
    collider.x = xpos;

    // if it goes off screen
    if ((xpos < 0) || (xpos + this->getWidth() > SCREEN_WIDTH))
    {
        // move back
        xpos -= xvel;
        collider.x = xpos;
    }

    // move up or down
    ypos += yvel;
    collider.y = ypos;

    if ((ypos < 0) || (ypos + this->getHeight() > SCREEN_HEIGHT))
    {
        // move back
        ypos -= yvel;
        collider.y = ypos;
    }
    */
}