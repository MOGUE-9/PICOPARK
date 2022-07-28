#pragma once
enum class CATSTAT
{
	STAND,
	WALK,
	PUSH,
	JUMP

};


class PicoCat
{
private:
	//�̹���
	ObImage*	stand = new ObImage(L"0_stand1.png");
	ObImage*	walk = new ObImage(L"0_walkSprite.png");
	ObImage*	push = new ObImage(L"0_pushSprite.png");
	ObImage*	jump = new ObImage(L"0_jump1.png");

	//�������
	CATSTAT		stat;
	
	float		scalar;
	float		gravity;

	//��
	float		blockOn;
	bool		isOn;

public:

	//�浹��
	ObRect* col = new ObRect();
	ObRect* headCol = new ObRect();


public:
	PicoCat();
	~PicoCat();

	void Update();
	void Render();

	void onBlock(float obPosY);
	void offBlock();

};

