#ifndef DIALOGUEBOX_H
#define DIALOGUEBOX_H

#include "Texture.h"
#include "LinkedList.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class DialogueBox
{
    struct node
    {
        std::string text;
        node* next;
    };

    public:
        DialogueBox();
        ~DialogueBox();
        void addText(std::string text);
        bool next();
        void render();
        void init();
        void free();
        void setRenderer(SDL_Renderer* renderer);

    private:
        Texture mBox;
        Texture mTextTexture;
        SDL_Renderer* mRenderer; 
        TTF_Font* mFont;

        // for font
        std::string mText;
        SDL_Color textColor;

        // linked list stuff
        LinkedList dialogue;

        bool isEmpty;
};

#endif