#include "Results.h"

Results::Results()
{
    font = NULL;
    textColor = {0xFF, 0xFF, 0xFF};

    font = TTF_OpenFont("fonts/comic.ttf", 52);
    if (font == NULL)
    {
        printf("Failed to load comic sans font! TTF Error: %s\n", TTF_GetError());
    }
    else
    {
        if (!dayOverText.loadFromRenderedText("Day End", textColor, font, mRenderer))
        {
            printf("Failed to load day end text!\n");
        }
    }
}

/*
Results::~Results()
{

}
*/

void Results::render()
{
    dayOverText.render(SCREEN_WIDTH / 2 - (dayOverText.getWidth() / 2), SCREEN_HEIGHT * 0.2, dayOverText.getWidth(), dayOverText.getHeight(), mRenderer);
}

void Results::update(Input* input)
{

}

void Results::free()
{

}