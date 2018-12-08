#include "Person.h"

// SOLUTION
// make texture class just a template class with basic load function in it and free
// then loop through and call free() on all textures which will destroy the texture and null the ptr

#define AMOUNT_OF_ELEMENTS 8

// use boost if this doesn't work properly on all systems?
namespace fs = std::filesystem;

Person::Person()
{
    mWidth = 0;
    mHeight = 0;
}

Person::~Person()
{
    free();
}

void Person::create(SDL_Renderer* renderer)
{
    mSkin.loadFromFile(getRandFile("img/people/skin"), renderer);
    mShirt.loadFromFile(getRandFile("img/people/clothes/shirts"), renderer);
    mHair.loadFromFile(getRandFile("img/people/hair"), renderer);
    mEyebrows.loadFromFile(getRandFile("img/people/face/eyebrows"), renderer);
    mEyes.loadFromFile(getRandFile("img/people/face/eyes"), renderer);
    mMouth.loadFromFile(getRandFile("img/people/face/mouths"), renderer);
    mNose.loadFromFile(getRandFile("img/people/face/noses"), renderer);
    mBase.loadFromFile("img/people/base.png", renderer);

    //textures = {mSkin, mShirt, mHair, mEyebrows, mEyes, mMouth, mNose, mBase};
}

std::string Person::getRandFile(std::string path)
{
    unsigned int fileCount = 0;
    std::vector<std::string> files; 

    for (auto &file : fs::directory_iterator(path))
    {
        files.push_back(file.path().string().c_str());
        fileCount++;
    }

    // initialize (seed) engine
    std::random_device rd;

    // random number engine used (mersenne-twister)
    std::mt19937 rng(rd());

    // get random int from 0 to fileCount
    std::uniform_int_distribution<int> uni(0, fileCount - 1);

    int randInt = uni(rng);

    return files[randInt];
}

// properly inherit this later
SDL_Texture* Person::loadFromFile(std::string path, SDL_Renderer* renderer)
{
    // get rid of preexisting texture
    //free();

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

// deallocate memory please
void Person::free()
{
    // would be better to loop through array and free all these but it wasnt working
    mSkin.free();
    mShirt.free();
    mHair.free();
    mEyebrows.free();
    mEyes.free();
    mMouth.free();
    mNose.free();
    mBase.free();

    mWidth = 0;
    mHeight = 0;
}

void Person::render(int x, int y, int w, int h, SDL_Renderer* renderer)
{
    // same with these
    mSkin.render(x, y, w, h, renderer);
    mShirt.render(x, y, w, h, renderer);
    mHair.render(x, y, w, h, renderer);
    mEyebrows.render(x, y, w, h, renderer);
    mEyes.render(x, y, w, h, renderer);
    mMouth.render(x, y, w, h, renderer);
    mNose.render(x, y, w, h, renderer);
    mBase.render(x, y, w, h, renderer);
}