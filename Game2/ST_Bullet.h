#pragma once
class ST_Bullet
{
public:
	ObRect* col;
	Vector2	fireDir;
	float	scalar;

	bool	isfire;

	ST_Bullet();
	~ST_Bullet();

	bool Shoot(Vector2 fireDir, float scalar, Vector2 firePos);
	virtual void Update();
	virtual void Render();

};

