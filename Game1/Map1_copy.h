#pragma once

//#define BMAX 8

class Map1_copy
{
	//âũ�� �ڽ�
	ObRect* mapBox = new ObRect();
	Vector2		liftDir{ DOWN };

	ObRect* keyBox = new ObRect();

	bool		isButton{ false }; //��ư �Ҹ� ����
	bool		isPress{ false }; //��ư ���ȴ�
	bool		isOnce{ true }; //�ѹ��� �ҰŴϱ� ��ȸ�� üĿ
	bool		isOpen{ false }; //main���� ���Ǹ����� �� �̹��� ����


public:

	ObImage*	blocks[8];



	//ObImage*	wall[2];
	//ObImage*	floor[3];
	//ObImage*	stair[3];
	
	//Ʈ���� ���߸� ������ �ٴ� :: MovPos���ְ� Ư����ġ���� ���ߵ��� �������
	ObImage* floorLF;

	//�ο������� ���Ʒ��� �����̴� �ٴ�
	ObImage* lift;
	ObImage* key = new ObImage(L"key.PNG");


	ObImage* door;
	ObImage* doorOP;

public:

	ObRect* button;

	Map1_copy();
	~Map1_copy();

	void Update();
	void Render();

	void Pressed();

	void openDoor();

	void stageOpen();
	void stageClose();

};

