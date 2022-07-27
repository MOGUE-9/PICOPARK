#pragma once
class Timer : public Singleton<Timer>
{
private:
    chrono::steady_clock::time_point    currentTime;
    chrono::steady_clock::time_point    lastTime;
    UINT                                framePerSecond;
    UINT                                framePerSecondCount;
    float                               framePerSecondTimeElapsed;
    float                               deltaTime;
    float                               deltaScaleTime;
    float                               worldTime;
   
public:
    Timer();
    bool    GetTick(float& time, float interval);
    void    Chronometry(UINT lock = 60);
    float   GetDelta()          { return deltaTime; } //∏≈≈©∑Œ X
    float   GetDeltaTime()      { return deltaScaleTime; }
    UINT    GetFramePerSecond() { return framePerSecond; }
    float   GetWorldTime()      { return worldTime; }
};
