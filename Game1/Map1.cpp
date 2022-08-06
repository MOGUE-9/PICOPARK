#include "stdafx.h"

Map1::Map1()
{
	//창크기 박스
	mapBox->SetWorldPos(Vector2(0.0f, 240.0f));
	mapBox->scale = Vector2(app.GetWidth(), app.GetHeight());
	mapBox->isFilled = false;
	mapBox->colOnOff = false;

	keyBox->scale = Vector2(40.0f, 75.0f) * 0.5f;
	keyBox->SetWorldPos(Vector2(2100.0f, 240.0f));
	keyBox->isFilled = false;
	keyBox->color = Color(1.0f, 0.0f, 0.0f, 1.0f);

	key->scale = Vector2(36.0f, 72.0f) * 0.5f;
	key->SetParentRT(*keyBox);
	//key->SetWorldPos(Vector2(2100.0f, 240.0f));
	key->collider = COLLIDER::RECT;

	///블럭셋팅 순서
	// 0 , 1 , 2 --> floor // 3 , 4 , 5 --> stair // 6 , 7 --> wall

	// 0 , 1 , 2 --> floor
	///바닥 기본틀
	for (int i = 0; i < 3; i++)
	{
		blocks[i] = new ObImage(L"floor.png");
		blocks[i]->SetParentRT(*mapBox);
		blocks[i]->colOnOff = true;
		blocks[i]->pivot = OFFSET_T;
		blocks[i]->collider = COLLIDER::RECT;
		blocks[i]->scale.y = 30.0f;
		blocks[i]->SetLocalPosY(-app.GetHalfHeight() + 30.0f);
	}
	//바닥 객체별로 X좌표 위치, 크기 재설정 해줘야함 :: Y는 동시에해도OK 어차피 다 맨아래 붙어있어서
	blocks[0]->scale.x = app.GetWidth();

	blocks[1]->SetLocalPosX(1000.0f);
	blocks[1]->scale.x = 500.0f;

	//floor[2]->SetLocalPosX(2600.0f);
	blocks[2]->SetLocalPosX(2550.0f); //디버그하는데 1캐릭으로 땅에 안닿아서 옮김
	blocks[2]->scale.x = 1500.0f;

	///계단 기본틀
	for (int i = 3; i < 6; i++)
	{
		blocks[i] = new ObImage(L"wall.png");
		blocks[i]->SetParentRT(*mapBox);
		blocks[i]->pivot = OFFSET_T;
		blocks[i]->collider = COLLIDER::RECT;
		blocks[i]->scale.x = 50.0f;
		blocks[i]->SetLocalPosX(1250.0f);
		//stair[i]->SetLocalPosY(-app.GetHalfHeight() + 30.0f);
	}
	//계단 :: floor1 끝나는 지점부터 생성돼야함
	blocks[3]->SetLocalPosY(-app.GetHalfHeight() + 80.0f);
	blocks[3]->scale.y = 180.0f;

	blocks[4]->SetLocalPosX(1300.0f); //시작X에서 0의 x크기만큼 더함
	blocks[4]->SetLocalPosY(-app.GetHalfHeight() + 130.0f);
	blocks[4]->scale.y = 180.0f;

	blocks[5]->SetLocalPosX(1350.0f);
	blocks[5]->SetLocalPosY(-app.GetHalfHeight() + 180.0f);
	blocks[5]->colOnOff = false;
	blocks[5]->visible = false;

	///벽 기본틀
	for (int i = 6; i < 8; i++)
	{
		blocks[i] = new ObImage(L"wall.png");
		blocks[i]->SetParentRT(*mapBox);
		blocks[i]->pivot = OFFSET_T;
		blocks[i]->collider = COLLIDER::RECT;
		//창크기의 좌측에 맞추기 :: X좌표 = -app.GetHalfWidth().x (480) + scale.x * 0.5f; 
		blocks[i]->SetLocalPos(Vector2(-465.0f, app.GetHalfHeight()));
		blocks[i]->scale = Vector2(30.0f, app.GetHeight());
	}

	blocks[7]->SetLocalPosX(2600.0f);
	blocks[7]->SetLocalPosY(30.0f);
	blocks[7]->scale = Vector2(400.0f, app.GetHalfHeight());
//-------------------------------------------------------------------------------
	floorLF = new ObImage(L"floor.png");
	floorLF->SetParentRT(*blocks[2]);
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

	liftBox->SetParentRT(*mapBox);
	liftBox->pivot = OFFSET_B;
	liftBox->SetLocalPos(Vector2(2300.0f, -240.0f));
	liftBox->scale = Vector2(200.0f, 270.0f);
	liftBox->isFilled = false;
	liftBox->color = Color(1.0f, 0.0f, 0.0f, 1.0f);
	liftBox->visible = false;

	lift = new ObImage(L"floor.png");
	lift->SetParentRT(*mapBox);
	lift->collider = COLLIDER::RECT;
	lift->pivot = OFFSET_T;
	lift->SetLocalPos(Vector2(2300.0f, 0.0f));
	lift->color = Color(0.0f, 1.0f, 0.0f, 1.0f);
	lift->scale = Vector2(200.0f, 10.0f);

	//문
	door = new ObImage(L"door.png");
	door->collider = COLLIDER::RECT;
	door->pivot = OFFSET_B;
	door->SetParentRT(*blocks[7]);
	door->scale = Vector2(95.0f, 93.0f) * 0.7f;
	//door->SetLocalPosY(app.GetHeight() * 0.5f);

	//열린문(검정색)
	doorOP = new ObImage(L"doorOpen.png");
	doorOP->collider = COLLIDER::RECT;
	doorOP->pivot = OFFSET_B;
	doorOP->SetParentRT(*blocks[7]);
	doorOP->scale = Vector2(95.0f, 93.0f) * 0.7f;
	//doorOP->SetLocalPosY(app.GetHeight() * 0.5f);
	doorOP->visible = false;
	doorOP->colOnOff = false;

	SOUND->AddSound("button.mp3", "button", false);
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
		
		if (floorLF->Intersect(blocks[4]))
		{
			float bPos = blocks[4]->GetWorldPos().x + blocks[4]->scale.x * 0.5f;
			floorLF->SetWorldPosX(bPos);
			//floorLF->SetWorldPosX(1375.0f);

			isOnce = false;
		}
	}

//-------------------------
	mapBox->Update();

	for (int i = 0; i < BMAX; i++)
	{
		blocks[i]->Update();
	}

	floorLF->Update();
	button->Update();

	door->Update();
	doorOP->Update();

	lift->Update();
	liftBox->Update();

	key->Update();
	keyBox->Update();
}

void Map1::Render()
{
	mapBox->Render();

	for (int i = 0; i < BMAX; i++)
	{
		blocks[i]->Render();
	}
	 
	floorLF->Render();
	button->Render();

	lift->Render();
	liftBox->Render();

	key->Render();
	keyBox->Render();

	door->Render();
	doorOP->Render();

}

void Map1::Pressed()
{
	isPress = true;
	if (!isButton)
	{
		SOUND->Play("button");
		isButton = true;
	}
}

void Map1::openDoor()
{
	door->colOnOff = false;
	isOpen = true;
}

void Map1::stageOpen()
{
	mapBox->colOnOff = false;

	for (int i = 0; i < BMAX; i++)
	{
		blocks[i]->colOnOff = true;
	}
	blocks[5]->colOnOff = false;


	floorLF->colOnOff = true;
	button->colOnOff = true;

	door->colOnOff = true;
	doorOP->colOnOff = false;

	lift->colOnOff = true;
	liftBox->colOnOff = true;
}

void Map1::stageClose()
{
	mapBox->colOnOff = false;

	for (int i = 0; i < BMAX; i++)
	{
		blocks[i]->colOnOff = false;
	}

	floorLF->colOnOff = false;
	button->colOnOff = false;

	door->colOnOff = false;
	doorOP->colOnOff = false;

	lift->colOnOff = false;
	liftBox->colOnOff = false;

	door->visible = true;
	doorOP->visible = false;
	isOpen = false;

	key->SetParentRT(*keyBox);
	key->visible = true;

	floorLF->SetLocalPosX(-750.0f);

	button->scale.y = 10.0f;
	isPress = false;
	isOnce = true;
}