#ifndef PERSON_H
#define PERSON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <random>
#include "Texture.h"


class Person : public Texture
{
    public:
        Person();
        ~Person();
        SDL_Texture* loadFromFile(std::string path, SDL_Renderer* renderer);
        std::string getRandFile(std::string path);
        void render(int x, int y, int w, int h, SDL_Renderer* renderer);
        void free();
        void create(SDL_Renderer* renderer);
        std::string getOpener();

    private:
        Texture mSkin;
        Texture mShirt;
        Texture mHair;
        Texture mEyebrows;
        Texture mEyes;
        Texture mMouth;
        Texture mNose;
        Texture mBase;
        int mWidth;
        int mHeight;

    protected:
        inline static std::vector<std::string> openers = {
            "Hey",
            "Hello",
            "Hi",
            "How's it goin'?",
            "Hey man",
            "Ring this shit up",
            "Hurry up"
        };
};

#endif