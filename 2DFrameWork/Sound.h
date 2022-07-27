#pragma once
class Sound : public Singleton<Sound>
{
	struct SoundNode
	{
		FMOD::Sound * sound;        //출력할 사운드 데이터
		FMOD::Channel * channel;    //출력해줄 채널
	};
	map<string, SoundNode*> SoundList;
	FMOD::System * system;

public:
    Sound();
    ~Sound();
    //전역에서 사운드 추가 
    bool AddSound(string File, string Key, bool loop = false);
    //전역에서 사운드 삭제
    bool DeleteSound(string Key);

    //그리고 key를 매개변수로 두고 모두 제어
    void Play(string Key);
    void Stop(string Key);
    //일시정지
    void Pause(string Key);
    //일시정지 해제
    void Resume(string Key);

    void SetVolume(string Key, float scale);
    void SetMasterVolume();
    void Update();
};

