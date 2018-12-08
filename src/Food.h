#ifndef FOOD_H
#define FOOD_H

#include "Texture.h"
#include "Person.h"
//#include "Window.h"

class Food : public Person
{  
    public:
        Food(SDL_Renderer* renderer);
        ~Food();
        void free();

        // makes texture out of random food item
        void load();

    private:
        SDL_Renderer* mRenderer;
        Texture mFoodItem;
        int xpos;
        int ypos;
        static std::vector<std::string> usedFoods;

};

#endif