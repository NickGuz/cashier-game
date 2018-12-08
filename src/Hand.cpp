#include "Hand.h"

Hand::Hand()
{
    mClosedHand = NULL;
    mOpenHand = NULL;
    mIsClosed = false;
    mWidth = 0;
    mHeight = 0;
}

Hand::~Hand()
{
    free();
}

SDL_Texture* Hand::loadFromFile(std::string path, SDL_Renderer* renderer)
{
    // get rid of preexisting texture
    free();

    // the final texture
    SDL_Texture* newTexture = NULL;

    // load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_Image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        // create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            // get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        // get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    // return success
    return newTexture;
}

bool Hand::loadHands(SDL_Renderer* renderer)
{
    mClosedHand = loadFromFile("img/arm_closed_hand.png", renderer);
    mOpenHand = loadFromFile("img/arm_open_hand.png", renderer);

    if (mClosedHand == NULL || mOpenHand == NULL)
    {
        printf("hi\n");
        return false;
    }

    return true;
}

void Hand::handleEvent(SDL_Event* e)
{
    if (e->type == SDL_MOUSEBUTTONDOWN)
    {
        mIsClosed = true;
    }
    else if (e->type == SDL_MOUSEBUTTONUP)
    {
        mIsClosed = false;
    }
}

/*
void Hand::free()
{
    if (mOpenHand != NULL)
    {
        SDL_DestroyTexture(mOpenHand);
        mOpenHand = NULL;
    }

    if (mClosedHand != NULL)
    {
        SDL_DestroyTexture(mClosedHand);
        mClosedHand = NULL;
    }
    
    mWidth = 0;
    mHeight = 0;
}
*/


void Hand::render(int x, int y, SDL_Renderer* renderer)
{
    SDL_Rect renderQuad = {x, y, mWidth * 0.8, mHeight * 0.8};

    if (mIsClosed)
    {
        SDL_RenderCopy(renderer, mClosedHand, NULL, &renderQuad);
    }
    else
    {
        SDL_RenderCopy(renderer, mOpenHand, NULL, &renderQuad);
    }
}