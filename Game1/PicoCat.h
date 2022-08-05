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
	//�̹���
	ObImage*	stand = new ObImage(L"0_stand1.png");
	ObImage*	walk = new ObImage(L"0_walkSprite.png");
	ObImage*	push = new ObImage(L"0_pushSprite.png");
	ObImage*	jump = new ObImage(L"0_jump1.png");
	
	Vector2		direction;
	float		gravity;

	float		gravityPlus;

	//��
	float		blockOn;
	bool		isOn;

	//��
	float		wallOn;
	bool		isWall;

	//�������� :: �ٴڿ� ������ �ʱ�ȭ :: isOn = true �϶�
	bool		isJump;
	float		jumpTime;

public:

	//���� ���� ����
	bool		isHave{ false };

	//�ⱸ�� �������� ����
	bool		isEnd{ false };

	//�̵� �ӵ� ���������� �ӽ÷� public�� �ű�
	float		scalar;

	//�������
	CATSTAT		stat;

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

	void onWall(float obPosX, float obScaleX);
	void offWall();

	//�������� ������ �� ������
	void Endgame();
};

