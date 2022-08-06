#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	titleMap = new Title();
	firstMap = new Map1();

	pNum = 2;

	camScalar = 0.0f;

	//player = new PicoCat();
	
	for (int i = 0; i < pNum; i++)
	{
		player[i] = new PicoCat();
		//player[i]->col->SetWorldPosX(100.0f - 200.0f * i);
	}
	player[0]->col->SetWorldPosX(100.0f);

	player[1]->col->SetWorldPosX(-100.0f);
	player[1]->ColorChange(0.5f, 0.5f, 0.8f);

	//player[1]->ColorChange();
	
	SOUND->AddSound("01Spring.mp3", "title", true);
	SOUND->SetVolume("title", 0.1f);

	//효과음
	SOUND->AddSound("jumSFX.mp3", "jump", false);
	SOUND->AddSound("lockDoor.mp3", "doorSound", false);
	SOUND->AddSound("keyGet.mp3", "key", false);

	SOUND->AddSound("03Doremi.mp3", "Stage1", true);

}

void Main::Release()
{
	SafeDelete(titleMap);
	SafeDelete(firstMap);
	//SafeDelete(player);
}

void Main::Update()
{

	//ImGuiColorEditFlags
	//ImGui::ColorEdit4("d", (float*)&block->color, ImGuiColorEditFlags_PickerHueWheel);

	float velo = (player[0]->col->GetWorldPos().x + player[pNum - 1]->col->GetWorldPos().x) * 0.5f - CAM->position.x;
	Vector2 velocity;
	velocity.x = velo;

	CAM->position += velocity * camScalar * DELTA;

	if (INPUT->KeyPress('L'))
	{
		CAM->position.x += 200.0f * DELTA;
	}

	///플레이어 이동
#if 1
	///1P
	//오른쪽
	if (INPUT->KeyPress(VK_RIGHT)/* || INPUT->KeyPress('D')*/)
	{
		player[0]->stat = CATSTAT::RIGHTPRESS;
		//player->stat = CATSTAT::RIGHTPRESS;
	}
	//왼쪽으로
	else if (INPUT->KeyPress(VK_LEFT)/* || INPUT->KeyPress('S')*/)
	{
		player[0]->stat = CATSTAT::LEFTPRESS;
		//player->stat = CATSTAT::LEFTPRESS;
	}
	else
	{
		player[0]->stat = CATSTAT::STAND;
		//player->stat = CATSTAT::STAND;
	}
	//움직임 키 뗐을 때 :: 오른쪽
	if (INPUT->KeyUp(VK_RIGHT))
	{
		player[0]->stat = CATSTAT::RIGHTUP;
	}
	//점프
	else if (INPUT->KeyUp(VK_LEFT))
	{
		player[0]->stat = CATSTAT::LEFTUP;
	}
	//문 앞 아닐때만 점프
	if (INPUT->KeyDown(VK_UP))
	{
		player[0]->stat = CATSTAT::JUMPDOWN;
	}
	//키 떼면 점프 1회 판정
	if (INPUT->KeyUp(VK_UP))
	{
		player[0]->stat = CATSTAT::JUMPUP;
	}

	///2P
	if (INPUT->KeyPress('D'))
	{
		player[1]->stat = CATSTAT::RIGHTPRESS;
	}
	else if (INPUT->KeyPress('A'))
	{
		player[1]->stat = CATSTAT::LEFTPRESS;
	}
	else
	{
		player[1]->stat = CATSTAT::STAND;
	}
	//움직임 키 뗐을 때 :: 오른쪽
	if (INPUT->KeyUp('D'))
	{
		player[1]->stat = CATSTAT::RIGHTUP;
	}
	//점프
	else if (INPUT->KeyUp('A'))
	{
		player[1]->stat = CATSTAT::LEFTUP;
	}
	//문 앞 아닐때만 점프 << 근데 이거 이렇게 하느니 그냥 ... 문 여는 키를 따로 주는게 나을듯
	if (INPUT->KeyDown('W'))
	{
		player[1]->stat = CATSTAT::JUMPDOWN;
	}
	//키 떼면 점프 1회 판정
	if (INPUT->KeyUp('W'))
	{
		player[1]->stat = CATSTAT::JUMPUP;
	}
#endif

	if (stage == STAGE::TITLE)
	{
		camScalar = 0.0f;

		for (int i = 0; i < pNum; i++)
		{
			player[i]->scalar = 150.0f;
		}

		SOUND->Stop("Stage1");
		SOUND->Play("title");

	///문열기-----------------------------------------------
		// P1 랑 닫힌문 door과 intersect 체크
		if (player[0]->col->Intersect(titleMap->door))
		{
			//문 앞에서 down 키 눌렀을 때
			if (INPUT->KeyDown(VK_DOWN))
			{
				//소리나고 문열림
				SOUND->Stop("doorSound");
				SOUND->Play("doorSound");

				titleMap->openDoor();
			}
		}
		else if (player[0]->col->Intersect(titleMap->doorOP)) //열린문 doorOP랑 intersect 체크
		{
			//열린문 앞에서 down 키 눌렀을 때
			if (INPUT->KeyDown(VK_DOWN))
			{
				player[0]->isEnd = true;
			}
		}

		// P2 랑 닫힌문 door과 intersect 체크
		if (player[1]->col->Intersect(titleMap->door))
		{
			if (INPUT->KeyDown('S'))
			{
				//있으면 소리나고 문열림
				SOUND->Stop("doorSound");
				SOUND->Play("doorSound");

				titleMap->openDoor();
			}
		}
		else if (player[1]->col->Intersect(titleMap->doorOP)) //열린문 doorOP랑 intersect 체크
		{
			//열린문 앞에서 down 키 눌렀을 때
			if (INPUT->KeyDown('S'))
			{
				player[1]->isEnd = true;
			}
		}

		//플레이어 위치 초기 위치로 옮기기
		if (player[0]->isEnd && player[1]->isEnd)
		{
			for (int j = 0; j < pNum; j++)
			{
				player[j]->isEnd = false;
				player[j]->StartGame();
				//player[j]->col->SetWorldPosX(100.0f - 200.0f * j);
			}
			player[0]->col->SetWorldPos(Vector2(100.0f, 0.0f));
			player[1]->col->SetWorldPos(Vector2(-100.0f, 0.0f));

			titleMap->stageClose();
			firstMap->stageOpen();

			stage = STAGE::ST_1;
		}
	}

	if (stage == STAGE::ST_1)
	{                                                                                           
		camScalar = 100.0f;

		for (int i = 0; i < pNum; i++)
		{
			player[i]->scalar = 100.0f;
		}

		SOUND->Stop("title");
		SOUND->Play("Stage1");

	///리프트------------------------------------------------------------------
		if (player[0]->isLift && player[1]->isLift)
		{
			isFull = true;
		}
		else isFull = false;
	
		if (isFull)
		{
			if (firstMap->lift->GetWorldPos().y >= 260.0f) //출구 바닥 높이
			{
				firstMap->lift->SetWorldPosY(260.0f);
			}
			else
			{
				liftDir = UP;
				firstMap->lift->MoveWorldPos(liftDir * 100.0f * DELTA);
			}
		}
		else
		{
			liftDir = DOWN;
			firstMap->lift->MoveWorldPos(liftDir * 100.0f * DELTA);

			if (firstMap->lift->GetWorldPos().y <= 20.0f)
			{
				firstMap->lift->SetWorldPosY(20.0f);
			}
		}

	///문열기-----------------------------------------------
		// P1 랑 닫힌문 door과 intersect 체크
		if (player[0]->col->Intersect(firstMap->door))
		{
			//문 앞에서 down 키 눌렀을 때
			if (INPUT->KeyDown(VK_DOWN))
			{
				//열쇠 유무 체크
				if (player[0]->isHave)
				{
					//있으면 소리나고 문열림
					SOUND->Stop("doorSound");
					SOUND->Play("doorSound");
					firstMap->key->visible = false;
					firstMap->openDoor();
				}
			}
		}
		else if (player[0]->col->Intersect(firstMap->doorOP)) //열린문 doorOP랑 intersect 체크
		{
			//열린문 앞에서 down 키 눌렀을 때
			if (INPUT->KeyDown(VK_DOWN))
			{
				player[0]->isEnd = true;
			}
		}

		// P2 랑 닫힌문 door과 intersect 체크
		if (player[1]->col->Intersect(firstMap->door))
		{
			if (INPUT->KeyDown('S'))
			{
				//열쇠 유무 체크
				if (player[1]->isHave)
				{
					//있으면 소리나고 문열림
					SOUND->Stop("doorSound");
					SOUND->Play("doorSound");
					firstMap->key->visible = false;
					firstMap->openDoor();
				}
			}
		}
		else if (player[1]->col->Intersect(firstMap->doorOP)) //열린문 doorOP랑 intersect 체크
		{
			//열린문 앞에서 down 키 눌렀을 때
			if (INPUT->KeyDown('S'))
			{
				player[1]->isEnd = true;
			}
		}

		//플레이어 위치 초기 위치로 옮기기
		if (player[0]->isEnd && player[1]->isEnd)
		{
			for (int j = 0; j < pNum; j++)
			{
				player[j]->isHave = false;
				player[j]->isEnd = false;
				player[j]->StartGame();
				//player[j]->col->SetWorldPosX(100.0f - 200.0f * j);
			}
			player[0]->col->SetWorldPos(Vector2(100.0f, 0.0f));
			player[1]->col->SetWorldPos(Vector2(-100.0f, 0.0f));

			firstMap->stageClose();
			isKey = false;

			titleMap->stageOpen();

			stage = STAGE::TITLE;
		}

	///열쇠 챙겨졌을때
		if (isKey)
		{
			for (int j = 0; j < pNum; j++)
			{
				//열쇠 갖고 있는 사람에게만
				if (player[j]->isHave)
				{
					Vector2 dir = player[j]->headCol->GetWorldPos() + keyPos - firstMap->key->GetWorldPos();
					firstMap->key->MoveWorldPos(dir * 10.0f * DELTA);

					if (j == 0 && INPUT->KeyPress(VK_RIGHT))
					{
						keyPos.x = -50.0f;
					}
					else if (j == 0 && INPUT->KeyPress(VK_LEFT))
					{
						keyPos.x = 50.0f;
					}

					if (j == 1 && INPUT->KeyPress('D'))
					{
						keyPos.x = -50.0f;
					}
					else if (j == 1 && INPUT->KeyPress('A'))
					{
						keyPos.x = 50.0f;
					}
				}
			}
		}

		/// <<로 이동하는 바닥
		for (int j = 0; j < pNum; j++)
		{
			if (player[j]->col->Intersect(firstMap->floorLF))
			{
				player[j]->onBlock(firstMap->floorLF->GetWorldPos().y);
			}
			else
			{
				player[j]->offBlock();
			}
		}
	}

	for (int i = 0; i < pNum; i++)
	{
		player[i]->Update();
	}

	titleMap->Update();
	firstMap->Update();
}

void Main::LateUpdate()
{
	//플레이어 끼리 충돌
			///플레이어 충돌
#if 1
	///플레이어[0] 
	if (player[0]->col->Intersect(player[1]->headCol))
	{
		//몸통주인이 머리주인 밟고 서기
		//정수리 위치
		float headP = player[1]->headCol->GetWorldPos().y + player[1]->headCol->scale.y;
		player[0]->onBlock(headP);
	}
	//머리-머리 충돌
	else if (player[0]->headCol->Intersect(player[1]->headCol))
	{
		// [0]을 조작하고 있으니까, 이 키입력이 있을때만 여기 들어오게 ...
		if (INPUT->KeyPress(VK_LEFT) || INPUT->KeyPress(VK_RIGHT))
		{
			//내가 좌측
			if (player[0]->col->GetWorldPos().x < player[1]->headCol->GetWorldPos().x)
			{
				//player[0]->stat = CATSTAT::RIGHTPUSH;
				// 내 scale *0.5 ..인데! 왜 24냐면 애니메이션 때문에 줄임
				int wallOn = player[1]->headCol->GetWorldPos().x - player[1]->headCol->scale.x * 0.5f - 23.0f;

				//충돌대상자 위치
				float Ipos = player[1]->col->GetWorldPos().x;

				//player[i]->col->SetWorldPosX(Ipos);
				player[0]->col->SetWorldPosX(wallOn);
				//break;
			}
			//내가 벽 우측
			else if (player[0]->col->GetWorldPos().x > player[1]->headCol->GetWorldPos().x)
			{
				//player[0]->stat = CATSTAT::LEFTPUSH;

				int wallOn = player[1]->headCol->GetWorldPos().x + player[1]->headCol->scale.x * 0.5f + 23.0f;
				//충돌대상자 위치
				float Ipos = player[1]->col->GetWorldPos().x;

				//player[i]->col->SetWorldPosX(Ipos);
				player[0]->col->SetWorldPosX(wallOn);
				//break;
			}
		}
	}
	///플레이어[1] 
	if (player[1]->col->Intersect(player[0]->headCol))
	{
		//몸통주인이 머리주인 밟고 서기
		//정수리 위치
		float headP = player[0]->headCol->GetWorldPos().y + player[0]->headCol->scale.y;
		player[1]->onBlock(headP);
	}
	//머리-머리 충돌
	else if (player[1]->headCol->Intersect(player[0]->headCol))
	{
		// [0]을 조작하고 있으니까, 이 키입력이 있을때만 여기 들어오게 ...
		if (INPUT->KeyPress('A') || INPUT->KeyPress('D'))
		{
			//내가 좌측
			if (player[1]->col->GetWorldPos().x < player[0]->headCol->GetWorldPos().x)
			{
				// 내 scale *0.5 ..인데! 왜 24냐면 애니메이션 때문에 줄임
				int wallOn = player[0]->headCol->GetWorldPos().x - player[0]->headCol->scale.x * 0.5f - 23.0f;

				//충돌대상자 위치
				float Ipos = player[0]->col->GetWorldPos().x;

				//player[i]->col->SetWorldPosX(Ipos);
				player[1]->col->SetWorldPosX(wallOn);
				//break;
			}
			//내가 벽 우측
			else if (player[1]->col->GetWorldPos().x > player[0]->headCol->GetWorldPos().x)
			{
				int wallOn = player[0]->headCol->GetWorldPos().x + player[0]->headCol->scale.x * 0.5f + 23.0f;
				//충돌대상자 위치
				float Ipos = player[0]->col->GetWorldPos().x;

				//player[i]->col->SetWorldPosX(Ipos);
				player[1]->col->SetWorldPosX(wallOn);
				//break;
			}
		}
	}
	for (int i = 0; i < pNum; i++)
	{
		player[i]->Update();
	}
#endif
		
	///타이틀
	if (stage == STAGE::TITLE)
	{
		CAM->position.y = 240.0f;
		CAM->position.x = 0.0f;
		//다인플레이

		//우측 맵 끝에 닿았을때 더 못가게 막는 update					// 960*0.5  = -480 + 30 + 내scale*0.5
		for (int i = 0; i < pNum; i++)
		{
			player[i]->col->SetWorldPosX(Utility::Saturate(player[i]->col->GetWorldPos().x, -455.0f, 455.0f));
		}

		for (int i = 0; i < pNum; i++)
		{
			//바닥과 충돌중일 때는 계속 위에 있기
			if (player[i]->col->Intersect(titleMap->floor))
			{
				player[i]->onBlock(titleMap->floor->GetWorldPos().y);
			}
			else player[i]->offBlock();

			player[i]->Update();
		}
	}

///스테이지1
	else if (stage == STAGE::ST_1)
	{
		CAM->position.y = 240.0f;
		CAM->position.x = Utility::Saturate(CAM->position.x, 0.0f, 2320.0f);
		//CAM->position.x = Utility::Saturate(CAM->position.x, 0.0f, 2000.0f);

		//우측 맵 끝에 닿았을때 더 못가게 막는 update					// 960*0.5  = -480 + 30 + 내scale*0.5
		for (int i = 0; i < pNum; i++)
		{
			player[i]->col->SetWorldPosX(Utility::Saturate(player[i]->col->GetWorldPos().x, -480.0f, 2775.0f));
		}

		///열쇠
		for (int j = 0; j < pNum; j++)
		{
			if (player[j]->col->Intersect(firstMap->key))
			{
				if (!isKey)
				{
					player[j]->isHave = true;
					SOUND->Play("key");
					firstMap->key->SetParentT(*player[j]->col);
					firstMap->key->SetLocalPos(Vector2(0.0f, 0.0f));
					//firstMap->key->SetLocalPos(Vector2(-50.0f, 50.0f));
					isKey = true;
				}
			}
		}
		firstMap->key->Update();

		///버튼밟기
		for (int j = 0; j < pNum; j++)
		{
			
			if (player[j]->col->Intersect(firstMap->button))
			{
				firstMap->Pressed();

				player[j]->onBlock(firstMap->button->GetWorldPos().y + firstMap->button->scale.y);
				player[j]->Update();
			}
			else
			{
				player[j]->offBlock();
				player[j]->Update();
			}
			firstMap->button->Update();
		}

		///리프트 밟기
		for (int j = 0; j < pNum; j++)
		{
			//리프트 충돌박스
			if (player[j]->col->Intersect(firstMap->liftBox))
			{
				//리프트의 x좌표 사이즈 안에 있을때 && 그리고 그 위에 있을때!!! 
				if (firstMap->lift->GetWorldPos().y + 5.0f > player[j]->col->GetWorldPos().y
					&& firstMap->lift->GetWorldPos().y - firstMap->lift->scale.y < player[j]->col->GetWorldPos().y)
				{
					player[j]->onBlock(firstMap->lift->GetWorldPos().y);
					player[j]->isLift = true;

					if (INPUT->KeyPress(VK_UP) || INPUT->KeyPress('W'))
					{
						if (INPUT->KeyPress(VK_UP))
						{
							player[0]->offBlock();
							player[0]->isLift = false;
						}
						if (INPUT->KeyPress('W'))
						{
							player[1]->offBlock();
							player[1]->isLift = false;
						}
					}
					player[j]->underLift = false;
				}
				else
				{
					player[j]->underLift = false;
					player[j]->isLift = false;
					//player[j]->offBlock();
					//player[j]->Update();
				}
			}
			else
			{
				player[j]->underLift = false;
				player[j]->isLift = false;
				//player[j]->offBlock();
				//player[j]->Update();
			}
			//리프트 좌측에서 비비는건 충돌박스 밖이니까
			if (player[j]->headCol->Intersect(firstMap->lift))
			{
				float liftOn = player[j]->headCol->GetWorldPos().y + player[j]->headCol->scale.y;

				//플레이어 몸통의 월드X좌표가 << 작은거임 << 리프트의 월드X좌표(OFFsET_T) - 리프트 X사이즈 = 리프트 좌측X좌표
				if (player[j]->col->GetWorldPos().x < firstMap->lift->GetWorldPos().x - firstMap->lift->scale.x * 0.5f)
				{
					//내가 벽 좌측
					if (INPUT->KeyPress(VK_RIGHT) || INPUT->KeyPress('D'))
					{
						int wallOn = firstMap->lift->GetWorldPos().x - firstMap->lift->scale.x * 0.5f - 22.0f;

						player[j]->col->SetWorldPosX(wallOn);
						player[j]->isLift = false; //왼쪽에 있으니까 당연히 타고있는판정 X
					}
				}
				//플레이어 머리통 정수리 Y좌표 << 작을때 << 리프트의 바닥 Y좌표 ( -5.0f 인건 .. 사이즈가 10.f 인데 오차생길까봐)
				else if (player[j]->col->Intersect(firstMap->liftBox) &&
					liftOn < firstMap->lift->GetWorldPos().y - 5.0f)
				{
					//리프트 Y좌표 고정할 Y값 계산식
					float liftOn2 = liftOn + 10.0f;

					firstMap->lift->SetWorldPosY(liftOn2);
					player[j]->isLift = false;
					player[j]->underLift = true;

					if (INPUT->KeyPress(VK_UP) || INPUT->KeyPress('W'))
					{
						player[j]->stat = CATSTAT::STAND;
					}
				}
			}
			player[j]->Update();

			firstMap->lift->Update();
		}
		///모든 바닥 벽 계단
		for (int j = 0; j < pNum; j++)
		{
			for (int i = 0; i < BMAX; i++)
			{
				//몸통이랑 충돌 -> 밟고서기
				if (player[j]->col->Intersect(firstMap->blocks[i]))
				{
					player[j]->onBlock(firstMap->blocks[i]->GetWorldPos().y);
				}
				//머리랑 충돌 -> 옆으로 비비기
				else if (player[j]->headCol->Intersect(firstMap->blocks[i]))
				{
					//내가 왼쪽에 있음 (오른쪽이 블럭)
					if (player[j]->col->GetWorldPos().x < firstMap->blocks[i]->GetWorldPos().x)
					{
						int wallOn = firstMap->blocks[i]->GetWorldPos().x - firstMap->blocks[i]->scale.x * 0.5f - 22.0f;

						player[j]->col->SetWorldPosX(wallOn);
					}
					//내가 오른쪽에 있음 (왼쪽이 블럭)
					else if (player[j]->col->GetWorldPos().x > firstMap->blocks[i]->GetWorldPos().x)
					{
						int wallOn = firstMap->blocks[i]->GetWorldPos().x + firstMap->blocks[i]->scale.x * 0.5f + 22.0f;

						player[j]->col->SetWorldPosX(wallOn);
					}
				}
			}
			player[j]->Update();
		}
	}

}

void Main::Render()
{
	if (stage == STAGE::TITLE)
	{
		titleMap->Render();
	}
	else if(stage == STAGE::ST_1)
	{
		firstMap->Render();
	}

	for (int i = 0; i < pNum; i++)
	{
		player[i]->Render();
	}
}

void Main::ResizeScreen()
{

}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Game1");
    app.SetInstance(instance);
	app.InitWidthHeight(960.0f,540.0f); // 원본게임비율 (1280.0f,720.0f)
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}