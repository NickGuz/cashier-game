#include "StateMachine.h"
//#include "states/Interview.h"
#include "states/Interview.h"
#include "states/Store.h"
#include "states/TitleScreen.h"
#include "states/Results.h"

// define static members
int StateMachine::mouse_x = 0;
int StateMachine::mouse_y = 0;
Hand StateMachine::mHand = Hand();

StateMachine::StateMachine()
{
    //mRenderer = NULL;  
}


StateMachine::~StateMachine()
{
    
}


void StateMachine::init(SDL_Renderer* renderer)
{
    mRenderer = renderer;
}

void StateMachine::setNextState(int newState)
{
    // if the user doesn't want to exit
    if (nextState != STATE_QUIT)
    {
        // set next state
        nextState = newState;
    }
}

void StateMachine::changeState()
{
    // if the state needs to be changed
    if (nextState != STATE_NULL)
    {
        // delete current state
        if (nextState != STATE_QUIT)
        {
            //currentState->free();
            delete currentState;
        }

        // change the state
        switch (nextState)
        {
            case STATE_TITLE:
                currentState = new TitleScreen();
                break;

            case STATE_INTERVIEW:
                currentState = new Interview();
                break;

            case STATE_STORE:
                currentState = new Store();
                break;

            case STATE_RESULTS:
                currentState = new Results();
                break;
        }

        // change the current state id
        stateID = nextState;

        // null the next state id
        nextState = STATE_NULL;
    }
}

void StateMachine::handleMouse(SDL_Event* e)
{
    mHand.handleEvent(e);
}

void StateMachine::render()
{
    currentState->render();
    //mHand.render(mouse_x - 50, mouse_y - 50, mRenderer);
}

void StateMachine::renderHand()
{
    mHand.render(mouse_x - 50, mouse_y - 50, mRenderer);
}