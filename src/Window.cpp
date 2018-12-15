#include "Window.h"

//const int SCREEN_WIDTH = 1280;
//const int SCREEN_HEIGHT = 720;

Window::Window()
{
    mWindow = NULL;
    mRenderer = NULL;
    gFont = NULL;
    state = NULL;
    //state->setRenderer(mRenderer);

    // start SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
         // hide cursor
        //SDL_ShowCursor(SDL_DISABLE);

        // load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            // main loop
            update();
        }
    }

    close();
}

Window::~Window()
{
    close();
}

bool Window::init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL failed to intialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!\n");
        }

        // create window
        mWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (mWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // create renderer for window
            mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (mRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // initialize renderer color
                SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0xFF);

                // initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_Image could not initialize! SDL_Image Error: %s\n", IMG_GetError());
                    success = false;
                }

                // initialize SDL_ttf
                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool Window::loadMedia()
{
    bool success = true;

    // load hand texture
    if (!mCursor.loadHands(mRenderer))
    {
        printf("Failed to load hand cursors!\n");
        success = false;
    }

    // open the font
    gFont = TTF_OpenFont("fonts/comic.ttf", 30);
    if (gFont == NULL)
    {
        printf("Failed to load comic sans font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }

    return success;
}

void Window::close()
{
    // free loaded images
    mCursor.free();
    mTextTexture.free();

    // free states (make global or members)

    // free global font
    //TTF_CloseFont(gFont);
    //gFont = NULL;

    // destroy window
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;
    mRenderer = NULL;
    state = NULL;

    // quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

// the main loop
void Window::update()
{
    bool quit = false;

    // do something here like statemachine.switchToState()
    // also make pointers to other states in statemachine or something
    //state = &StateMachine();
    //state->interview = Interview();
    //Interview* istate = state->getInterview();
    //Interview* istate = state->setState("interview");

    //state->setRenderer(mRenderer);
    //state->interview = new Interview();

    //Interview * istate = state->interview;

    Input input = Input();

    // fps stuff
    Timer fpsTimer = Timer();
    std::stringstream fpsText;
    SDL_Color textColor = {0, 255, 0, 255};

    // start counting fps
    int countedFrames = 0;
    fpsTimer.start();

    Store store = Store(mRenderer);
    TitleScreen title = TitleScreen(mRenderer);
    bool switchScreen = false;
    bool quitGame = false;
    
    // event handler
    SDL_Event e;

    while (!quit)
    {
        // handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            // user requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            // user presses a key
            // make input class for this prob
            /*
            else if (e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_SPACE:
                        //store.next();
                        break;
                }
            }
            */

            input.onEvent(&e);

            SDL_GetMouseState(&mouse_x, &mouse_y);

            // handle open and close animation on hand
            mCursor.handleEvent(&e);
            store.handleEvent(&e);

            // quit when user clicks "quit"
            quitGame = title.handleQuit(&e, &mouse_x, &mouse_y);
            if (quitGame)
            {
                quit = true;
            }

            // if user clicks start on title screen start the game
            if (!switchScreen)
            {
                switchScreen = title.handleStart(&e, &mouse_x, &mouse_y);
            }
        }

        // calulate fps
        float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.0f);
        if (avgFPS > 2000000)
        {
            avgFPS = 0;
        }

        // set text to be rendered for fps
        fpsText.str("");
        fpsText << "FPS: " << avgFPS;


        // load fps font
        if (!gFPSTextTexture.loadFromRenderedText(fpsText.str().c_str(), textColor, gFont, mRenderer))
        {
            printf("Unable to render FPS texture!\n");
        }

        // clear screen
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(mRenderer);

        if (!switchScreen)
        {
            title.render();
        }
        else
        {
            store.update(input, mCursor);
            store.render();
            mCursor.render(mouse_x - 50, mouse_y - 50, mRenderer);
        }

        /*
        // test
        SDL_Rect rect;
        rect.x = 100;
        rect.y = 100;
        rect.w = 100;
        rect.h = 100;

        if (mCursor.collides(rect))
        {
            std::cout << "Collides" << std::endl;
        }
        */

        // render fps
        gFPSTextTexture.render(0, 0, gFPSTextTexture.getWidth() / 2, gFPSTextTexture.getHeight() / 2, mRenderer);

        // update the screen
        SDL_RenderPresent(mRenderer);
        input.keysPressed.clear();
        input.keysPressed.resize(MAX_KEYS, false);
        countedFrames++;
    }
}