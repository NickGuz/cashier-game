#ifndef FOOD_H
#define FOOD_H

#include "Texture.h"
#include "Person.h"
#include "Hand.h"
//#include "Window.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Food : public Person
{  
    public:
        Food();
        ~Food();
        void init(SDL_Renderer* renderer);
        void free();
        void render();
        int getWidth();
        int getHeight();
        int getX();
        int getY();
        SDL_Rect getCollider();

        // makes texture out of random food item
        void load(int old_x, int prevWidth);

        void move(SDL_Rect hand);

        static std::vector<std::string> usedFoods;
        
        // maximum axis velocity 
        static const int FOOD_VEL = 10;
        static int next_xpos;

    private:
        SDL_Renderer* mRenderer;
        Texture mFoodItem;

        // x and y offsets
        int xpos, ypos;

        // velocity of this food
        int xvel, yvel;

        // the collision box
        SDL_Rect collider;
};

#endif