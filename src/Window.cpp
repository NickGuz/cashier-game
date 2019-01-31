#include "Window.h"

//const int SCREEN_WIDTH = 1280;
//const int SCREEN_HEIGHT = 720;

Window::Window()
{
    mWindow = NULL;
    mRenderer = NULL;
    gFont = NULL;

    // start SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // hide default os cursor
        SDL_ShowCursor(SDL_DISABLE);

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
    if (!StateMachine::mHand.loadHands(mRenderer))
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
    mTextTexture.free();

    //StateMachine::free();

    // destroy window
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;
    mRenderer = NULL;
    //state = NULL;

    // quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

// the main loop
void Window::update()
{
    bool quit = false;

    Input input = Input();

    // fps stuff
    Timer fpsTimer = Timer();
    std::stringstream fpsText;
    SDL_Color textColor = {0, 255, 0, 255};

    // start counting fps
    unsigned int countedFrames = 0;
    fpsTimer.start();

    // state stuff
    StateMachine::init(mRenderer);
    StateMachine::stateID = STATE_TITLE;
    StateMachine::currentState = new TitleScreen();
    //StateMachine::nextState = NULL;
    //StateMachine::mouse_x = 0;
    //StateMachine::mouse_y = 0;
  
    bool switchScreen = false;
    bool quitGame = false;
    
    // event handler
    SDL_Event e;

    while (!quit)
    {
        input.keysPressed.clear();
        input.keysPressed.resize(MAX_KEYS, false);

        // handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
    

            // user requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            input.onEvent(&e);

            SDL_GetMouseState(&StateMachine::mouse_x, &StateMachine::mouse_y);


            // handle open and close animation on hand
            StateMachine::handleMouse(&e);
        }

        StateMachine::currentState->update(&input);
        
        StateMachine::changeState();

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

        //std::cout << fpsTimer.getTicks() / 1000 << std::endl;

        // clear screen
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(mRenderer);

        StateMachine::currentState->render();
        StateMachine::renderHand();

        // render fps
        gFPSTextTexture.render(0, 0, gFPSTextTexture.getWidth() / 2, gFPSTextTexture.getHeight() / 2, mRenderer);

        // update the screen
        SDL_RenderPresent(mRenderer);
        
        countedFrames++;
    }
}