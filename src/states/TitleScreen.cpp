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

        // set values for start button hitbox
        startCollider.w = mStartButton.getWidth();
        startCollider.h = mStartButton.getHeight(); 
        startCollider.x = (SCREEN_WIDTH - mStartButton.getWidth()) / 2; 
        startCollider.y = (SCREEN_HEIGHT - mStartButton.getHeight()) * 0.5;
        
        if (!mQuitButton.loadFromRenderedText("Quit", textColor, mFont, mRenderer))
        {
            printf("Failed to load quit button!\n");
        }

        // set values for quit button hitbox
        quitCollider.w = mQuitButton.getWidth();
        quitCollider.h = mQuitButton.getHeight();
        quitCollider.x = (SCREEN_WIDTH - mQuitButton.getWidth()) / 2;
        quitCollider.y = (SCREEN_HEIGHT - mQuitButton.getHeight()) * 0.8;
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
    if (input->isKeyPressed(SDLK_RETURN))
    {
        StateMachine::setNextState(STATE_INTERVIEW);
    }

    // handle start button click
    if (mHand.collides(startCollider) && input->isMousePressed())
    {
        StateMachine::setNextState(STATE_INTERVIEW);
    }

    // handle quit button click
    if (mHand.collides(quitCollider) && input->isMousePressed())
    {
        StateMachine::setNextState(STATE_QUIT);
    }
}

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