#pragma once

//#define BMAX 8

class Map1_copy
{
	//창크기 박스
	ObRect* mapBox = new ObRect();
	Vector2		liftDir{ DOWN };

	ObRect* keyBox = new ObRect();

	bool		isButton{ false }; //버튼 소리 났니
	bool		isPress{ false }; //버튼 눌렸니
	bool		isOnce{ true }; //한번만 할거니까 일회용 체커
	bool		isOpen{ false }; //main에서 조건맞으면 문 이미지 변경


public:

	ObImage*	blocks[8];



	//ObImage*	wall[2];
	//ObImage*	floor[3];
	//ObImage*	stair[3];
	
	//트리거 맞추면 나오는 바닥 :: MovPos해주고 특정위치가면 멈추도록 해줘야함
	ObImage* floorLF;

	//인원수따라 위아래로 움직이는 바닥
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

