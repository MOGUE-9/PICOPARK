#pragma once
class Enemy
{
public:
	ObRect* col;
	float hp;
	float damagingTime;

	Enemy();
	~Enemy();

	void Update();
	void Render();
	void TakeDamage(int damage);
};

