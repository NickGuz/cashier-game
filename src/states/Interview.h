#ifndef INTERVIEW_H
#define INTERVIEW_H

#include "../StateMachine.h"
#include "../DialogueBox.h"

class Interview : public StateMachine
{
    public:
        Interview(SDL_Renderer* renderer);

        void render();
        void free();
        void next();

    private:
        SDL_Renderer* mRenderer;
        Texture mBackground;
        Texture mTable;
        DialogueBox mDbox;

        // make this a person
        Texture mBoss;
};

#endif