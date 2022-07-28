#pragma once
class Title
{
private:

	ObRect*		mapBox = new ObRect();
	
	ObImage*	name;

	bool		isOpen{ false }; //main���� ���Ǹ����� �� �̹��� ����

public:

	ObImage*	floor;
	ObImage*	door;
	ObImage*	doorOP;


public:

	Title();
	~Title();

	void Update();
	void Render();

	void openDoor();

	void stageOpen();
	void stageClose();

};

