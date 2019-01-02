#include "TitleScreen.h"

TitleScreen::TitleScreen()
{
    //mRenderer = renderer;
    mFont = NULL;
    textColor = {0xFF, 0xFF, 0xFF};
    SDL_ShowCursor(SDL_ENABLE);

    mFont = TTF_OpenFont("fonts/comic.ttf", 42);
    if (mFont == NULL)
    {
        printf("Failed to load comic sans font! TTF Error: %s\n", TTF_GetError());
    }
    else
    {
        
        if (!mStartButton.loadFromRenderedText("Start", textColor, mFont, mRenderer))
        {
            printf("Failed to load start button!\n");
        }

        
        if (!mQuitButton.loadFromRenderedText("Quit", textColor, mFont, mRenderer))
        {
            printf("Failed to load quit button!\n");
        }
    }
}

/*
TitleScreen::~TitleScreen()
{
    free();
}
*/

void TitleScreen::update(Input* input)
{
    //StateMachine::setNextState(STATE_INTERVIEW);
    //std::cout << input.keysPressed.size() << std::endl;

    if (input->isKeyPressed(SDLK_RETURN))
    {
        StateMachine::setNextState(STATE_INTERVIEW);
    }
}

/*
bool TitleScreen::handleStart(SDL_Event* e, int *mouse_x, int *mouse_y)
{
    if (*mouse_x >= (SCREEN_WIDTH - mStartButton.getWidth()) / 2 && 
        *mouse_x <= (SCREEN_WIDTH + mStartButton.getWidth()) / 2 &&
        *mouse_y >= (SCREEN_HEIGHT - mStartButton.getHeight()) / 2 &&
        *mouse_y <= (SCREEN_HEIGHT + mStartButton.getHeight()) / 2 &&
        e->type == SDL_MOUSEBUTTONDOWN)
    {
        return true;
    }

    return false;
}

bool TitleScreen::handleQuit(SDL_Event* e, int *mouse_x, int *mouse_y)
{
    if (*mouse_x >= (SCREEN_WIDTH - mQuitButton.getWidth()) / 2 &&
        *mouse_x <= (SCREEN_WIDTH + mQuitButton.getWidth()) / 2 &&
        *mouse_y >= (SCREEN_HEIGHT - mQuitButton.getHeight()) * 0.8 &&
        *mouse_y <= (SCREEN_HEIGHT + mQuitButton.getHeight()) * 0.8 &&
        e->type == SDL_MOUSEBUTTONDOWN)
    {
        return true;
    }

    return false;
}
*/

void TitleScreen::render()
{
    mStartButton.render((SCREEN_WIDTH - mStartButton.getWidth()) / 2, (SCREEN_HEIGHT - mStartButton.getHeight()) * 0.5,
                         mStartButton.getWidth(), mStartButton.getHeight(), mRenderer);

    mQuitButton.render((SCREEN_WIDTH - mQuitButton.getWidth()) / 2, (SCREEN_HEIGHT - mQuitButton.getHeight()) * 0.8,
                         mQuitButton.getWidth(), mQuitButton.getHeight(), mRenderer);
}

void TitleScreen::free()
{
    mRenderer = NULL;
    TTF_CloseFont(mFont);
    mFont = NULL;
    mStartButton.free();
    mQuitButton.free();
}