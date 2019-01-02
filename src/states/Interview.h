#ifndef INTERVIEW_H
#define INTERVIEW_H

#include "../StateMachine.h"
#include "../DialogueBox.h"
#include "../Input.h"

class Interview : public StateMachine
{
    public:
        Interview();
        //~Interview();
        void render();
        void update(Input* input);
        void free();
        void next();

    private:
        //SDL_Renderer* mRenderer;
        Texture mBackground;
        Texture mTable;
        DialogueBox mDbox;

        // make this a person
        Texture mBoss;
};

#endif