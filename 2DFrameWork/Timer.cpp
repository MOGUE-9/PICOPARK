#include "framework.h"

Timer::Timer()
{
    //현재 시간 측정
    lastTime = chrono::steady_clock::now();
    //타이머 생성시엔 경과시간을 알수없다.
    deltaTime = 0.0f;
    //처음 실행시간은 0
    worldTime = 0.0f;
    framePerSecond = 0;
    framePerSecondCount = 0;
    framePerSecondTimeElapsed = 0.0f;
}

bool Timer::GetTick(float& time, float interval)
{
    time += DELTA;
    if (time > interval)
    {
        time -= interval;
        return true;
    }
    return false;
}

void Timer::Chronometry(UINT lock)
{
    currentTime = chrono::steady_clock::now();
    //지난시간 - 현재시간값을 나노 초단위로 받기
    chrono::duration<double> Delta = currentTime - lastTime;
    //        초단위로 변경하여 값받기
    deltaTime = (float)Delta.count();

    //델타가 1/60보다 작다면
    while (deltaTime < (1.0f / lock))
    {
        //현재시간을 다시측정
        currentTime = chrono::steady_clock::now();
        //델타를 다시계산
        Delta = currentTime - lastTime;
        deltaTime = (float)Delta.count();
    }

    //마지막 시간을 기록
    lastTime = currentTime;
    //전체 시간 경과량을 연산
    worldTime += deltaTime;

    //1초를 잡아주는 변수
    framePerSecondTimeElapsed += deltaTime;

    framePerSecondCount++;
    //FPSTimeElapsed 이 1초가 넘었을때
    if (framePerSecondTimeElapsed > 1.0f)
    {
        framePerSecond = framePerSecondCount;
        framePerSecondCount = 0;
        framePerSecondTimeElapsed = 0.0f;
    }
    deltaScaleTime = deltaTime * app.deltaScale;
}
