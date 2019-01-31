#include "../StateMachine.h"

class Results : public StateMachine
{
    public:
        Results();
        //~Results();
        void render();
        void update(Input* input);
        void free();

    private:
        Texture dayOverText;
        TTF_Font* font;
        SDL_Color textColor;
};