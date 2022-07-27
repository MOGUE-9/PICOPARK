#include "framework.h"

Sound::Sound()
{
    //사운드 시스템 생성
    System_Create(&system);
    //사운드 채널 동적할당
    system->init(32, FMOD_INIT_NORMAL, nullptr);
}

Sound::~Sound()
{
    //사운드를 다 삭제하는 부분
    for (auto iter = SoundList.begin(); iter != SoundList.end(); iter++)
    {
        iter->second->channel->stop();
        iter->second->sound->release();
        delete iter->second;
    }
    system->release();
    system->close();
    SoundList.clear();
}

bool Sound::AddSound(string File, string Key, bool loop)
{
    string path = "../Contents/Sound/" + File;

    //key 중복 허용x
    auto iter = SoundList.find(Key);

    //중복된게 있다.
    if (iter != SoundList.end())
    {
        return false;
    }

    //중복된게 없다.
    SoundNode * temp = new SoundNode();
    system->createSound
    (
        path.c_str(),
        FMOD_DEFAULT,
        nullptr,
        &temp->sound
    );

    if (loop)
    {
        temp->sound->setMode(FMOD_LOOP_NORMAL);
    }
    else
    {
        temp->sound->setMode(FMOD_LOOP_OFF);
    }

    //맵에 할당한 배열 원소넣기
    SoundList[Key] = temp;

    return true;
}

bool Sound::DeleteSound(string Key)
{
    auto iter = SoundList.find(Key);

    //중복된게 없다.
    if (iter == SoundList.end())
    {
        return false;
    }
    //first가 키, second 밸류
    iter->second->channel->stop();
    iter->second->sound->release();
    delete iter->second;

    //맵에서도 삭제
    SoundList.erase(iter);

    return true;
}

void Sound::Play(string Key)
{
    auto iter = SoundList.find(Key);

    //중복된게 있을때
    if (iter != SoundList.end())
    {
        bool isplay;
        iter->second->channel->isPlaying(&isplay);
        if (!isplay)
        {
            system->playSound(
                iter->second->sound, nullptr,
                false,
                &iter->second->channel);
        }
    }
}

void Sound::Stop(string Key)
{
    auto iter = SoundList.find(Key);

    //중복된게 있을때
    if (iter != SoundList.end())
    {
        iter->second->channel->stop();
    }
}

void Sound::Pause(string Key)
{
    auto iter = SoundList.find(Key);

    //중복된게 있을때
    if (iter != SoundList.end())
    {
        iter->second->channel->setPaused(true);
    }
}

void Sound::Resume(string Key)
{
    auto iter = SoundList.find(Key);

    //중복된게 있을때
    if (iter != SoundList.end())
    {
        iter->second->channel->setPaused(false);
    }
}

void Sound::SetVolume(string Key, float scale)
{
    auto iter = SoundList.find(Key);

    //중복된게 있을때
    if (iter != SoundList.end())
    {
        iter->second->channel->setVolume(scale * app.soundScale);
    }
}

void Sound::SetMasterVolume()
{
    for (auto iter = SoundList.begin(); iter != SoundList.end(); iter++)
    {
        iter->second->channel->setVolume(app.soundScale);
    }
}

void Sound::Update()
{
    system->update();
}
