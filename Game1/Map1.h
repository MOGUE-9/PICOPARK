#pragma once
class Map1
{
	//âũ�� �ڽ�
	ObRect* mapBox = new ObRect();

	ObImage* wall[2];
	ObImage* floor[3];
	ObImage* stair[3];

	//Ʈ���� ���߸� ������ �ٴ� :: MovPos���ְ� Ư����ġ���� ���ߵ��� �������
	ObImage* floorLF;

	//�ο������� ���Ʒ��� �����̴� �ٴ�
	ObImage* floorUpdown;

public:

	Map1();
	~Map1();

	void Update();
	void Render();

};

