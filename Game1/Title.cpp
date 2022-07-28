#include "stdafx.h"

Title::Title()
{

	mapBox->SetWorldPos(Vector2(0.0f,0.0f));
	mapBox->scale = Vector2(app.GetWidth(), app.GetHeight());
	mapBox->isFilled = false;

	name = new ObImage(L"title.png");
	name->SetParentRT(*mapBox);
	name->scale = Vector2(990.0f, 222.0f) * 0.6f;
	name->SetLocalPosY(50.0f);

	floor = new ObImage(L"floor.png");
	floor->pivot = OFFSET_T;
	floor->collider = COLLIDER::RECT;
	floor->SetParentRT(*mapBox);
	floor->scale = Vector2(app.GetWidth(),30.0f);
	floor->SetLocalPosY(-app.GetHalfHeight() + 30.0f);

	door = new ObImage(L"door.png");
	door->collider = COLLIDER::RECT;
	door->pivot = OFFSET_B;
	door->SetParentRT(*mapBox);
	door->scale = Vector2(95.0f, 93.0f) * 0.7f;
	door->SetLocalPosY(-app.GetHalfHeight() + 30.0f);

	doorOP = new ObImage(L"doorOpen.png");

}

Title::~Title()
{
	SafeDelete(mapBox);
	SafeDelete(name);
	SafeDelete(floor);
}

void Title::Update()
{
	mapBox->Update();
	name->Update();
	floor->Update();
	door->Update();
}

void Title::Render()
{
	mapBox->Render();
	name->Render();
	floor->Render();
	door->Render();

}
