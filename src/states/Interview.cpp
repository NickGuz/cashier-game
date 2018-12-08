#include "Interview.h"

Interview::Interview(SDL_Renderer* renderer)
{
    mRenderer = renderer;
    //SDL_ShowCursor(SDL_DISABLE);

    mBackground.loadFromFile("img/interview/interview_bg.png", mRenderer);
    mBoss.loadFromFile("img/interview/boss.png", mRenderer);
    mTable.loadFromFile("img/interview/table.png", mRenderer);
    mDbox.setRenderer(mRenderer);
    mDbox.addText("Hey bud");
    mDbox.addText("Im your boss now");
    mDbox.addText("Jk get out");
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

void Interview::free()
{
    mBackground.free();
    mBoss.free();
    mTable.free();
    mRenderer = NULL;
}