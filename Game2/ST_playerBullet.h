#pragma once
class ST_playerBullet : public ST_Bullet
{
private:
	int		 level;
public:

	ObImage* greenB[4];
	int damage;

	ST_playerBullet();
	~ST_playerBullet();

	void Update() override;
	void Render() override;

	int GetLevel() { return level; }
	void ChangeLevel(int level);
};

