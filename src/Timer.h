#include <SDL2/SDL.h>
#include <string>
#include <sstream>

class Timer
{
    public:
        Timer();

        // the various clock actions
        void start();
        void stop();
        void pause();
        void unpause();

        // gets the timers time
        Uint32 getTicks();

        // checks status of timer
        bool isStarted();
        bool isPaused();

    private:
        // the clock time when the timer started
        Uint32 mStartTicks;

        // the ticks stored when the timer was paused
        Uint32 mPausedTicks;

        // timer status
        bool mPaused;
        bool mStarted;
};