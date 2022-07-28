#pragma once
class Title
{
private:

	ObRect*		mapBox = new ObRect();
	
	ObImage*	name;

	bool		isOpen{ false }; //main에서 조건맞으면 문 이미지 변경

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

