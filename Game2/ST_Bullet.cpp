#include "stdafx.h"

ST_Bullet::ST_Bullet()
{
	col = new ObRect();
	col->collider = COLLIDER::RECT;
	col->isFilled = false;
	isfire = false;
}

ST_Bullet::~ST_Bullet()
{
}

bool ST_Bullet::Shoot(Vector2 fireDir, float scalar, Vector2 firePos)
{
	if (!isfire)
	{
		isfire = true;

		col->SetWorldPos(firePos);
		this->fireDir = fireDir;
		this->scalar = scalar;

		return true;
	}

	return false;
}

void ST_Bullet::Update()
{
	if (!isfire) return;

	Vector2 velocity = fireDir * scalar;
	col->MoveWorldPos(velocity * DELTA);
	col->rotation = Utility::DirToRadian(velocity) - DIV2PI;

	col->Update();
}

void ST_Bullet::Render()
{
	col->Render();
}
