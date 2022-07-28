#pragma once
class Map1
{
	//창크기 박스
	ObRect* mapBox = new ObRect();

	ObImage* wall[2];
	ObImage* floor[3];
	ObImage* stair[3];

	//트리거 맞추면 나오는 바닥 :: MovPos해주고 특정위치가면 멈추도록 해줘야함
	ObImage* floorLF;

	//인원수따라 위아래로 움직이는 바닥
	ObImage* floorUpdown;

public:

	Map1();
	~Map1();

	void Update();
	void Render();

};

