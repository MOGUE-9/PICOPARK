#pragma once
#define MAX 30
class ST_Player
{
private:
	ObImage*		LR;
	ObImage*		boost;
	ObRect*			col;
	Vector2			dir;

	bool			isBoosting;
	float			LRkey;

	int				level;

public:
	ST_playerBullet bullet[MAX];

public:
	ST_Player();
	~ST_Player();

	void Update();
	void Render();

};

