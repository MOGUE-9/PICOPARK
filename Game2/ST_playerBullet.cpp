#include "stdafx.h"

ST_playerBullet::ST_playerBullet()
{
	col->scale.x = 100.0f;
	col->scale.y = 50.0f;

	for (int i = 0; i < 4; i++)
	{
		greenB[i] = new ObImage(L"PlayeBullet.png");
		greenB[i]->SetParentRT(*col);
		greenB[i]->maxFrame.x = 4;
		greenB[i]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	}
	greenB[1]->visible = false;
	greenB[2]->visible = false;
	greenB[3]->visible = false;

	greenB[0]->scale = Vector2(50, 100.0f);
	greenB[1]->scale = Vector2(50, 100.0f);
	greenB[2]->scale = Vector2(50, 100.0f);
	greenB[3]->scale = Vector2(50, 100.0f);

	level = 0;
}

ST_playerBullet::~ST_playerBullet()
{
	SafeDelete(greenB[0]);
}

void ST_playerBullet::Update()
{
	ST_Bullet::Update();
	if (!isfire) return;

	for (int i = 0; i < 4; i++)
	{
		greenB[i]->Update();
	}
}

void ST_playerBullet::Render()
{
	ST_Bullet::Render();

	col->visible = isfire;

	if (!isfire) return;

	for (int i = 0; i < 4; i++)
	{
		greenB[i]->Render();
	}
	
}

void ST_playerBullet::ChangeLevel(int level)
{
	if (level == 0)
	{
		col->scale.x = 50.0f;
		damage = 5;

		greenB[0]->SetLocalPos(Vector2(0.0f, 0.0f));

		greenB[0]->visible = true;
		greenB[1]->visible = false;
		greenB[2]->visible = false;
		greenB[3]->visible = false;

	}
	else if (level == 1)
	{
		col->scale.x = 100.0f;
		damage = 10;

		greenB[0]->SetLocalPos(Vector2(-25.0f, 0.0f));
		greenB[1]->SetLocalPos(Vector2(25.0f, 0.0f));

		greenB[0]->visible = true;
		greenB[1]->visible = true;
		greenB[2]->visible = false;
		greenB[3]->visible = false;
	}
	else if (level == 2)
	{
		col->scale.x = 150.0f;
		damage = 15;

		greenB[0]->SetLocalPos(Vector2(0.0f, 0.0f));
		greenB[1]->SetLocalPos(Vector2(-50.0f, 0.0f));
		greenB[2]->SetLocalPos(Vector2(50.0f, 0.0f));

		greenB[0]->visible = true;
		greenB[1]->visible = true;
		greenB[2]->visible = true;
		greenB[3]->visible = false;
	}
	else if (level == 3)
	{
		col->scale.x = 200.0f;
		damage = 20;

		greenB[0]->SetLocalPos(Vector2(-25.0f, 0.0f));
		greenB[1]->SetLocalPos(Vector2(-75.0f, 0.0f));
		greenB[2]->SetLocalPos(Vector2(25.0f, 0.0f));
		greenB[3]->SetLocalPos(Vector2(75.0f, 0.0f));

		greenB[0]->visible = true;
		greenB[1]->visible = true;
		greenB[2]->visible = true;
		greenB[3]->visible = true;
	}
}
