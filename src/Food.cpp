#include "Food.h"

Food::Food(SDL_Renderer* renderer)
{
    mRenderer = renderer;
    load();
}

Food::~Food()
{

}

// makes texture out of random food item
void Food::load()
{
    std::string foodFile = getRandFile("img/food");

    for (int i = 0; i < usedFoods.size(); i++)
    {
        if (usedFoods[i] == foodFile)
        {
            // infinite recursion very possible
            load();
        }
    }

    mFoodItem.loadFromFile(getRandFile(foodFile), mRenderer);
}

void Food::free()
{

}