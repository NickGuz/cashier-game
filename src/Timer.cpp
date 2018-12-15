#include "Timer.h"

Timer::Timer()
{
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

void Timer::start()
{
    // start the timer
    mStarted = true;

    // unpause the timer
    mPaused = false;

    // get the current clock time
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void Timer::stop()
{
    // stop timer
    mStarted = false;

    // unpause the timer
    mPaused = false;

    // clear tick variables
    mStartTicks = 0;
    mPausedTicks = 0;
}

void Timer::pause()
{
    // if the timer is running and isnt already paused
    if (mStarted && !mPaused)
    {
        // pause timer
        mPaused = true;

        // calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

void Timer::unpause()
{
    // if the timer is running and paused
    if (mStarted && mPaused)
    {
        // unpause the timer
        mPaused = false;

        // reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;

        // reset the paused ticks
        mPausedTicks = 0;
    }
}

Uint32 Timer::getTicks()
{
    // the actual timer time
    Uint32 time = 0;

    // if the timer is running
    if (mStarted)
    {
        // if the timer is paused
        if (mPaused)
        {
            // return the number of ticks when the timer was paused
            time = mPausedTicks;
        }
        else
        {
            // return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }

    return time;
}

bool Timer::isStarted()
{
    return mStarted;
}

bool Timer::isPaused()
{
    return mPaused && mStarted;
}

