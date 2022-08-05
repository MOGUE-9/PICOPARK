#pragma once
enum class CATSTAT
{
	STAND,
	RIGHTPRESS,
	RIGHTUP,
	LEFTPRESS,
	LEFTUP,
	JUMPDOWN,
	JUMPUP,

	WALK,
	PUSH,
	JUMP

};


class PicoCat
{
private:
	//이미지
	ObImage*	stand = new ObImage(L"0_stand1.png");
	ObImage*	walk = new ObImage(L"0_walkSprite.png");
	ObImage*	push = new ObImage(L"0_pushSprite.png");
	ObImage*	jump = new ObImage(L"0_jump1.png");
	
	Vector2		direction;
	float		gravity;

	float		gravityPlus;

	//블럭
	float		blockOn;
	bool		isOn;

	//벽
	float		wallOn;
	bool		isWall;

	//점프여부 :: 바닥에 닿으면 초기화 :: isOn = true 일때
	bool		isJump;
	float		jumpTime;

public:

	float		scalar;

	//현재상태
	CATSTAT		stat;

public:


	//충돌블럭
	ObRect* col = new ObRect();
	ObRect* headCol = new ObRect();


public:
	PicoCat();
	~PicoCat();

	void Update();
	void Render();

	void onBlock(float obPosY);
	void offBlock();

	void onWall(float obPosX, float obScaleX);
	void offWall();
};

