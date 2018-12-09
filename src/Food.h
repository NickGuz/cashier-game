#ifndef FOOD_H
#define FOOD_H

#include "Texture.h"
#include "Person.h"
//#include "Window.h"

class Food : public Person
{  
    public:
        Food();
        ~Food();
        void init(SDL_Renderer* renderer);
        void free();
        void render(int x, int y, int w, int h);
        int getWidth();
        int getHeight();

        // makes texture out of random food item
        void load();

        static std::vector<std::string> usedFoods;

    private:
        SDL_Renderer* mRenderer;
        Texture mFoodItem;
        int xpos;
        int ypos;
};

#endif