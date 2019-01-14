#include "Bag.h"

Bag::Bag()
{
    bagWidth = 0;
    bagHeight = 0;
    isOverBag = false;
    mRenderer = NULL;
}

Bag::~Bag()
{
    
}

void Bag::free()
{
    mRenderer = NULL;
    closedBag.free();
    openBag.free();
}

void Bag::load(SDL_Renderer* renderer)
{
    mRenderer = renderer;
    closedBag.loadFromFile("img/store/bag/frame1.png", mRenderer);
    openBag.loadFromFile("img/store/bag/frame2.png", mRenderer);

    // set dimension variables
    bagWidth = closedBag.getWidth();
    bagHeight = closedBag.getHeight();

    // setup hitbox
    collider.w = (bagWidth * 0.7) / 2;
    collider.h = bagHeight * 0.7;
    collider.x = 0;         // (SCREEN_WIDTH / 2) * 0.10;
    collider.y = SCREEN_HEIGHT * 0.50;
}

void Bag::update()
{

}

void Bag::render()
{
    if (!isOverBag)
        closedBag.render(collider.x, collider.y, bagWidth * 0.7, collider.h, mRenderer);
    else
        openBag.render(collider.x, collider.y, bagWidth * 0.7, collider.h, mRenderer);
}

SDL_Rect Bag::getCollider()
{
    return collider;
}