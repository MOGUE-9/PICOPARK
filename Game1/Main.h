#pragma once
#define PMAX 2

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
	STAGE		stage{ STAGE::TITLE };

	float		camScalar;

	int			pNum;
	PicoCat*	player;
	//PicoCat*	player[2];


	Map1*		firstMap;
	bool		isFull; //리프트 인원 체크
	Vector2		liftDir{ DOWN };
	bool		isKey{ false };
	Vector2		keyPos{ -50.0f, 50.0f };


public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
