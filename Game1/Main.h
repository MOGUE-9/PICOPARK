#pragma once
#define FMAX 8
#define RMAX 3

enum class STAGE
{
	NONE,
	TITLE,
	ST_1,
	ST_2
};

class Main : public Scene
{
private:
	
	Title*		titleMap;
	Map1*		firstMap;

	PicoCat*	player;
	bool		isFull; //리프트 인원 체크
	Vector2		liftDir{ DOWN };

	STAGE		stage{ STAGE::TITLE };


public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
