#include "StateMachine.h"
//#include "states/Interview.h"

StateMachine::StateMachine()
{
    mRenderer = NULL;
    interview = NULL;
}

StateMachine::~StateMachine()
{
    free();
}

void StateMachine::setRenderer(SDL_Renderer* renderer)
{
    mRenderer = renderer;
}

Interview* StateMachine::getInterview()
{
    //return &Interview();
}

// returns statemachine pointer so that doesnt make sense
StateMachine* StateMachine::setState(StateMachine* state)
{
    

    return NULL;
}

void StateMachine::free()
{

}