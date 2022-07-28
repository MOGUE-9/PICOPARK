#pragma once
class Title
{
	ObRect* mapBox = new ObRect();

	ObImage* name;

public:

	ObImage* floor;
	ObImage* door;
	ObImage* doorOP;


public:

	Title();
	~Title();

	void Update();
	void Render();
};

