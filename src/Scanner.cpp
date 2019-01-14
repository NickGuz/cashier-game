#include "Scanner.h"

Scanner::Scanner()
{
    scanHeight = 0;
    scanWidth = 0;
    scanned = false;
    scannedFrames = 0;
}

Scanner::~Scanner()
{

}

void Scanner::free()
{
    mRenderer = NULL;
    scanDefault.free();
    scanScanned.free();
}

void Scanner::load(SDL_Renderer* renderer)
{
    mRenderer = renderer;
    scanDefault.loadFromFile("img/store/scanner/try4/default.png", mRenderer);
    scanScanned.loadFromFile("img/store/scanner/try4/scan5.png", mRenderer);

    // set dimension variables here so we don't need to call functions every frame in render
    scanWidth = scanDefault.getWidth();
    scanHeight = scanDefault.getHeight();

    // setup collision box
    collider.w = scanWidth * 0.7;
    collider.h = scanHeight * 0.7;
    collider.x = (SCREEN_WIDTH / 2) * 0.40;
    collider.y = SCREEN_HEIGHT * 0.63;
}

void Scanner::update()
{

}

void Scanner::render()
{
    //std::cout << frames << ", " << scannedFrames << std::endl;
    if (!scanned)
        scanDefault.render((SCREEN_WIDTH / 2) * 0.39, SCREEN_HEIGHT * 0.63, scanWidth * 0.7, scanHeight * 0.7, mRenderer);
    else
    {
        scanScanned.render((SCREEN_WIDTH / 2) * 0.39, SCREEN_HEIGHT * 0.63, scanWidth * 0.7, scanHeight * 0.7, mRenderer);
    }
}

SDL_Rect Scanner::getCollider()
{
    return collider;
}