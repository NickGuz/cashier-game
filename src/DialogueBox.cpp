#include "DialogueBox.h"

DialogueBox::DialogueBox()
{
    mFont = NULL;
    mRenderer = NULL;
    textColor = {0xFF, 0xFF, 0xFF};
}

DialogueBox::~DialogueBox()
{
    free();
}

void DialogueBox::addText(std::string text)
{
    // need to figure out way to iterate linked list on spacebar or whatever
    dialogue.addNode(text);
}

bool DialogueBox::next()
{
    if (dialogue.next())
    {
        mTextTexture.loadFromRenderedText(dialogue.getCurrent(), textColor, mFont, mRenderer);
        return true;
    }

    return false;
}

void DialogueBox::init()
{
    mBox.loadFromFile("img/d_box.png", mRenderer);
    mBox.setBlendMode(SDL_BLENDMODE_BLEND);
    mBox.setAlpha(230);

    mFont = TTF_OpenFont("fonts/comic.ttf", 30);
    if (mFont == NULL)
    {
        printf("Failed to load comic sans font! TTF Error: %s\n", TTF_GetError());
    }
    else
    {
        // render text
        if (!mTextTexture.loadFromRenderedText(dialogue.getCurrent(), textColor, mFont, mRenderer))
        {
            printf("Failed to render text texture!\n");
        }
    }
}

void DialogueBox::render()
{
    mBox.render(-30, 0, SCREEN_WIDTH, SCREEN_HEIGHT, mRenderer);
    mTextTexture.render((SCREEN_WIDTH - mTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - mTextTexture.getHeight()) * 0.9, NULL, NULL, mRenderer);
}

void DialogueBox::free()
{
    mBox.free();
    mRenderer = NULL;
    TTF_CloseFont(mFont);
    mFont = NULL;
}

void DialogueBox::setRenderer(SDL_Renderer* renderer)
{
    mRenderer = renderer;
}