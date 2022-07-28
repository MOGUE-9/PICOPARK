#include "stdafx.h"

Map1::Map1()
{
	//âũ�� �ڽ�
	mapBox->SetWorldPos(Vector2(0.0f, 0.0f));
	mapBox->scale = Vector2(app.GetWidth(), app.GetHeight());
	mapBox->isFilled = false;
	mapBox->colOnOff = false;

	for (int i = 0; i < 2; i++)
	{
		//�� �⺻Ʋ
		wall[i] = new ObImage(L"wall.png");
		wall[i]->SetParentRT(*mapBox);
		wall[i]->pivot = OFFSET_B;
		wall[i]->collider = COLLIDER::RECT;
				//âũ���� ������ ���߱� :: X��ǥ = -app.GetHalfWidth().x (480) + scale.x * 0.5f; 
		wall[i]->SetLocalPos(Vector2(-465.0f, -270.0f)); 
		wall[i]->scale = Vector2(30.0f, app.GetHeight());
	}

	for (int i = 0; i < 3; i++)
	{
		//�ٴ� �⺻Ʋ
		floor[i] = new ObImage(L"floor.png");
		floor[i]->SetParentRT(*mapBox);
		floor[i]->pivot = OFFSET_T;
		floor[i]->collider = COLLIDER::RECT;
		floor[i]->scale.y = 30.0f;
		floor[i]->SetLocalPosY(-app.GetHalfHeight() + 30.0f);
		

		//��� �⺻Ʋ
		stair[i] = new ObImage(L"wall.png");
	}

	//�ٴ� ��ü���� X��ǥ ��ġ, ũ�� �缳�� ������� :: Y�� ���ÿ��ص�OK ������ �� �ǾƷ� �پ��־
	floor[0]->scale.x = app.GetWidth();

	floor[1]->SetLocalPosX(1000.0f);
	floor[1]->scale.x = 500.0f;

}

Map1::~Map1()
{
	SafeDelete(mapBox);

}

void Map1::Update()
{
	mapBox->Update();
	for (int i = 0; i < 2; i++)
	{
		wall[i]->Update();
	}

	for (int i = 0; i < 3; i++)
	{
		floor[i]->Update();
		stair[i]->Update();
	}
}

void Map1::Render()
{
	mapBox->Render();
	for (int i = 0; i < 2; i++)
	{
		wall[i]->Render();
	}
	for (int i = 0; i < 3; i++)
	{
		floor[i]->Render();
		stair[i]->Render();
	}
}
