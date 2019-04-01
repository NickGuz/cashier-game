#include "Interview.h"

Interview::Interview()
{
    mBackground.loadFromFile("img/interview/interview_bg.png", mRenderer);
    mBoss.loadFromFile("img/interview/boss.png", mRenderer);
    mTable.loadFromFile("img/interview/table.png", mRenderer);
    mDbox.setRenderer(mRenderer);
    mDbox.addText("Hey bud");
    mDbox.addText("Im your boss now");
    mDbox.addText("Jk get out");
    mDbox.addText("Jk I guess you're hired");
    mDbox.init();
}

void Interview::next()
{
    mDbox.next();
}

void Interview::render()
{
    mBackground.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, mRenderer);
    mBoss.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, mRenderer);
    mTable.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, mRenderer);
    mDbox.render();
}

void Interview::update(Input* input)
{
    if (input->isKeyPressed(SDL_SCANCODE_SPACE))
    {
        if (!mDbox.next())
        {
            mDbox.free();

            // change to store state
            StateMachine::setNextState(STATE_STORE);
        }
    }
}

void Interview::free()
{
    mBackground.free();
    mBoss.free();
    mTable.free();
    mRenderer = NULL;
}