#include "Timer.h"
#include "SDL.h"

void Timer::Start()
{
    Stopped = false;
    StartTime = 0;
    DeltaTime = 0;
}

int Timer::Read()
{
    if (!Stopped) {
        UpdateDeltaTime();
    }
    return DeltaTime;
}

int Timer::Stop()
{
    UpdateDeltaTime();
    Stopped = true;
    return Read();
}

void Timer::UpdateDeltaTime()
{
    DeltaTime = GetCurrentTime() - StartTime;
}

int Timer::GetCurrentTime()
{
    return SDL_GetTicks();
}
