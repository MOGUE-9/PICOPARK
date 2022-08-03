#include "stdafx.h"

Map1::Map1()
{
	//창크기 박스
	mapBox->SetWorldPos(Vector2(0.0f, 240.0f));
	mapBox->scale = Vector2(app.GetWidth(), app.GetHeight());
	mapBox->isFilled = false;
	mapBox->colOnOff = false;

	key->scale = Vector2(36.0f, 72.0f) * 0.5f;

	for (int i = 0; i < 2; i++)
	{
		//벽 기본틀
		wall[i] = new ObImage(L"wall.png");
		wall[i]->SetParentRT(*mapBox);
		wall[i]->pivot = OFFSET_T;
		wall[i]->collider = COLLIDER::RECT;
				//창크기의 좌측에 맞추기 :: X좌표 = -app.GetHalfWidth().x (480) + scale.x * 0.5f; 
		wall[i]->SetLocalPos(Vector2(-465.0f, app.GetHalfHeight()));
		wall[i]->scale = Vector2(30.0f, app.GetHeight());
	}

	for (int i = 0; i < 3; i++)
	{
		//바닥 기본틀
		floor[i] = new ObImage(L"floor.png");
		floor[i]->SetParentRT(*mapBox);
		floor[i]->pivot = OFFSET_T;
		floor[i]->collider = COLLIDER::RECT;
		floor[i]->scale.y = 30.0f;
		floor[i]->SetLocalPosY(-app.GetHalfHeight() + 30.0f);
		

		//계단 기본틀
		stair[i] = new ObImage(L"wall.png");
		stair[i]->SetParentRT(*mapBox);
		stair[i]->pivot = OFFSET_T;
		stair[i]->collider = COLLIDER::RECT;
		stair[i]->scale.x = 50.0f;
		stair[i]->SetLocalPosX(1250.0f);
		//stair[i]->SetLocalPosY(-app.GetHalfHeight() + 30.0f);
	}

	wall[1]->SetLocalPosX(2600.0f);
	wall[1]->SetLocalPosY(30.0f);
	wall[1]->scale = Vector2(400.0f, app.GetHalfHeight());

	//바닥 객체별로 X좌표 위치, 크기 재설정 해줘야함 :: Y는 동시에해도OK 어차피 다 맨아래 붙어있어서
	floor[0]->scale.x = app.GetWidth();

	floor[1]->SetLocalPosX(1000.0f);
	floor[1]->scale.x = 500.0f;

	//floor[2]->SetLocalPosX(2600.0f);
	floor[2]->SetLocalPosX(2550.0f); //디버그하는데 1캐릭으로 땅에 안닿아서 옮김
	floor[2]->scale.x = 1500.0f;

	//계단 :: floor1 끝나는 지점부터 생성돼야함
	stair[0]->SetLocalPosY(-app.GetHalfHeight() + 80.0f);
	stair[0]->scale.y = 180.0f;

	stair[1]->SetLocalPosX(1300.0f); //시작X에서 0의 x크기만큼 더함
	stair[1]->SetLocalPosY(-app.GetHalfHeight() + 130.0f);
	stair[1]->scale.y = 180.0f;

	stair[2]->SetLocalPosX(1350.0f);
	stair[2]->SetLocalPosY(-app.GetHalfHeight() + 180.0f);
	stair[2]->scale.y = 180.0f;

	floorLF = new ObImage(L"floor.png");
	floorLF->SetParentRT(*floor[2]);
	floorLF->pivot = OFFSET_LT;
	//floorLF->SetLocalPosY(-app.GetHalfHeight() + 30.0f);
	floorLF->SetLocalPosX(-750.0f);
	floorLF->scale.y = 15.0f; //두께
	floorLF->scale.x = 500.0f; //길이
	//floorLF->color.B(1.0f); //색잘보이게하려고
	floorLF->collider = COLLIDER::RECT;

	button = new ObRect();
	button->SetParentRT(*mapBox);
	button->scale = Vector2(15.0f, 10.0f);
	button->pivot = OFFSET_B;
	button->SetWorldPos(Vector2(1900.0f, -app.GetHalfHeight() + 30.0f));
	button->color = Color(1.0f, 0.0f, 0.0f, 1.0f);

	lift = new ObImage(L"floor.png");
	lift->SetParentRT(*mapBox);
	lift->collider = COLLIDER::RECT;
	lift->pivot = OFFSET_T;
	lift->SetLocalPos(Vector2(2300.0f, 20.0f));
	lift->color = Color(0.0f, 1.0f, 0.0f, 1.0f);
	lift->scale = Vector2(200.0f, 10.0f);

	//문
	door = new ObImage(L"door.png");
	door->collider = COLLIDER::RECT;
	door->pivot = OFFSET_B;
	door->SetParentRT(*wall[1]);
	door->scale = Vector2(95.0f, 93.0f) * 0.7f;
	//door->SetLocalPosY(app.GetHeight() * 0.5f);

	//열린문(검정색)
	doorOP = new ObImage(L"doorOpen.png");
	doorOP->collider = COLLIDER::RECT;
	doorOP->pivot = OFFSET_B;
	doorOP->SetParentRT(*wall[1]);
	doorOP->scale = Vector2(95.0f, 93.0f) * 0.7f;
	//doorOP->SetLocalPosY(app.GetHeight() * 0.5f);
	doorOP->visible = false;
	doorOP->colOnOff = false;
}

Map1::~Map1()
{
	SafeDelete(mapBox);
}

void Map1::Update()
{
	//cout << wall[1]->GetWorldPos().y << endl;


	//main에서 아래키 눌러서, 문 1회 열었을때, 열린 문 보여주고 colOn (열릴준비)
	if (isOpen)
	{
		door->visible = false;
		doorOP->visible = true;
		doorOP->colOnOff = true;
	}
		
	if (isPress && isOnce)
	{
		button->scale.y = 4.0f;

		floorLF->MoveWorldPos(LEFT * 100.0f * DELTA);
		
		if (floorLF->Intersect(stair[2]))
		{
			floorLF->SetWorldPosX(1375.0f);
			isOnce = false;
		}
	}

//-------------------------
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

	floorLF->Update();
	button->Update();
	door->Update();
	doorOP->Update();
	lift->Update();
	key->Update();
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

	//floor[0]->Render();
	//floor[1]->Render();


	floorLF->Render();
	button->Render();
	lift->Render();
	door->Render();
	doorOP->Render();
	key->Render();

}

void Map1::Pressed()
{
	isPress = true;

}

void Map1::openDoor()
{
	door->colOnOff = false;
	isOpen = true;
}

void Map1::stageOpen()
{
	mapBox->colOnOff = false;

	for (int i = 0; i < 2; i++)
	{
		wall[i]->colOnOff = true;
	}

	for (int i = 0; i < 3; i++)
	{
		floor[i]->colOnOff = true;
		stair[i]->colOnOff = true;
	}

	floorLF->colOnOff = true;
	button->colOnOff = true;
	door->colOnOff = true;
	doorOP->colOnOff = false;
	lift->colOnOff = true;
}

void Map1::stageClose()
{
	mapBox->colOnOff = false;

	for (int i = 0; i < 2; i++)
	{
		wall[i]->colOnOff = false;
	}

	for (int i = 0; i < 3; i++)
	{
		floor[i]->colOnOff = false;
		stair[i]->colOnOff = false;
	}

	floorLF->colOnOff = false;
	button->colOnOff = false;
	door->colOnOff = false;
	doorOP->colOnOff = false;
	lift->colOnOff = false;

	door->visible = true;
	doorOP->visible = false;
	isOpen = false;

	floorLF->SetLocalPosX(-750.0f);
	button->scale.y = 10.0f;
	isPress = false;
	isOnce = true;
}