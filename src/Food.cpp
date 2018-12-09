#include "Food.h"

//std::vector<std::string> usedFoods();

Food::Food()
{
    //mRenderer = renderer;
    //std::vector<std::string> usedFoods();
    //load();
}

Food::~Food()
{

}

void Food::init(SDL_Renderer* renderer)
{
    mRenderer = renderer;
}

// makes texture out of random food item
void Food::load()
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
                load();
                return;
            }
        }
    }

    usedFoods.push_back(foodFile);
    mFoodItem.loadFromFile(foodFile, mRenderer);
}

void Food::render(int x, int y, int w, int h)
{
    mFoodItem.render(x, y, NULL, NULL, mRenderer);
}

void Food::free()
{

}

int Food::getWidth()
{
    return mFoodItem.getWidth();
}

int Food::getHeight()
{
    return mFoodItem.getHeight();
}
