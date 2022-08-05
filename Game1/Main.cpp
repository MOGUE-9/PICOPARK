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
	}

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

	//Vector2 velocity = player->col->GetWorldPos() - CAM->position;

	CAM->position += velocity * camScalar * DELTA;


	if (INPUT->KeyPress('L'))
	{
		CAM->position.x += 200.0f * DELTA;
	}

	if (INPUT->KeyDown(VK_UP) || INPUT->KeyDown('W'))
	{
		SOUND->Stop("jump");
		SOUND->Play("jump");
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

	//solo
#if 0
	///플레이어 이동
	//오른쪽
	if (INPUT->KeyPress(VK_RIGHT) || INPUT->KeyPress('D'))
	{
		player->stat = CATSTAT::RIGHTPRESS;
	}

	//왼쪽으로
	else if (INPUT->KeyPress(VK_LEFT) || INPUT->KeyPress('S'))
	{
		player->stat = CATSTAT::LEFTPRESS;
	}
	else
	{
		player->stat = CATSTAT::STAND;
	}


	//움직임 키 뗐을 때 :: 오른쪽
	if (INPUT->KeyUp(VK_RIGHT) || INPUT->KeyUp('D'))
	{
		player->stat = CATSTAT::RIGHTUP;
	}
	//점프
	else if (INPUT->KeyUp(VK_LEFT) || INPUT->KeyUp('S'))
	{
		player->stat = CATSTAT::LEFTUP;
	}

	//문 앞 아닐때만 점프 << 근데 이거 이렇게 하느니 그냥 ... 문 여는 키를 따로 주는게 나을듯
	if (INPUT->KeyDown(VK_UP) || INPUT->KeyDown('W'))
	{
		player->stat = CATSTAT::JUMPDOWN;
	}

	//키 떼면 점프 1회 판정
	if (INPUT->KeyUp(VK_UP) || INPUT->KeyUp('W'))
	{
		player->stat = CATSTAT::JUMPUP;
	}

#endif

	if (stage == STAGE::TITLE)
	{
		camScalar = 0.0f;

		for (int i = 0; i < pNum; i++)
		{
			player[i]->scalar = 100.0f;
		}

		//player->scalar = 100.0f;

		SOUND->Stop("Stage1");
		//SOUND->Play("title");
	}

	if (stage == STAGE::ST_1)
	{                                                                                           
		camScalar = 100.0f;

		for (int i = 0; i < pNum; i++)
		{
			player[i]->scalar = 100.0f;
		}

		//player->scalar = 80.0f;

		SOUND->Stop("title");
		//SOUND->Play("Stage1");

		//우측 맵 끝에 닿았을때 더 못가게 막는 update					// 960*0.5  = -480 + 30 + 내scale*0.5
	//멀티
#if 1
		for (int i = 0; i < pNum; i++)
		{
			player[i]->col->SetWorldPosX(Utility::Saturate(player[i]->col->GetWorldPos().x, -480.0f, 2775.0f));
		}
#endif

		//솔로
		//player->col->SetWorldPosX(Utility::Saturate(player->col->GetWorldPos().x, -480.0f , 2775.0f)); //2800-25(플레이어 크기)
	
		if (isFull)
		{
												//출구 바닥 높이
			if (firstMap->lift->GetWorldPos().y >= 260.0f)
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
		//firstMap->lift->SetWorldPosY(Utility::Saturate(firstMap->lift->GetWorldPos().y, -200.0f, 70.0f));

		//문열기
		for (int j = 0; j < pNum; j++)
		{
			//닫힌문 door과 intersect 체크
			if (player[j]->col->Intersect(firstMap->door))
			{
				//문 앞에서 down 키 눌렀을 때
				if (INPUT->KeyDown(VK_DOWN))
				{
					//열쇠 유무 체크
					//if (player[j]->isHave)
					//{
						//있으면 소리나고 문열림
					SOUND->Stop("doorSound");
					SOUND->Play("doorSound");
					firstMap->openDoor();
					//}
				}
			}
			//열린문 doorOP랑 intersect 체크
			if (player[j]->col->Intersect(firstMap->doorOP))
			{
				//열린문 앞에서 down 키 눌렀을 때
				if (INPUT->KeyDown(VK_DOWN))
				{
					player[j]->isEnd = true;
				}
			}
		}

		//플레이어 위치 초기 위치로 옮기기
		if (player[0]->isEnd && player[1]->isEnd)
		{
			for (int j = 0; j < pNum; j++)
			{
				player[j]->isEnd = false;
				player[j]->col->SetWorldPos(Vector2(0.0f, 0.0f));
			}

			firstMap->stageClose();
			isKey = false;

			titleMap->stageOpen();

			stage = STAGE::TITLE;
		}



	}

	//cout << "포" << endl;
	//cout << firstMap->wall[0]->GetWorldPos().y << endl;
	//cout << player->col->GetWorldPos().x << endl;
	//cout << "피" << endl;
	//cout << firstMap->wall[0]->GetWorldPivot().y << endl;
	//cout << player->col->GetWorldPivot().x << endl; 

	for (int i = 0; i < pNum; i++)
	{
		player[i]->Update();
	}

	//player->Update();

	titleMap->Update();

	firstMap->Update();
}

void Main::LateUpdate()
{


	///타이틀
	if (stage == STAGE::TITLE)
	{
		CAM->position.y = 240.0f;
		CAM->position.x = 0.0f;


		//다인플레이
#if 1
		for (int i = 0; i < pNum; i++)
		{
			//바닥과 충돌중일 때는 계속 위에 있기
			if (player[i]->col->Intersect(titleMap->floor))
			{
				player[i]->onBlock(titleMap->floor->GetWorldPos().y);
			}
			else player[i]->offBlock();
		}

		for (int i = 0; i < pNum; i++)
		{	//문열기
			if (titleMap->door->colOnOff)
			{
				if (player[i]->col->Intersect(titleMap->door))
				{
					if (INPUT->KeyDown(VK_DOWN))
					{
						SOUND->Stop("doorSound");
						SOUND->Play("doorSound");
						titleMap->openDoor();
						break;
					}
				}
			}
			//스테이지 이동
			else if (player[i]->col->Intersect(titleMap->doorOP))
			{
				if (INPUT->KeyDown(VK_DOWN))
				{

					titleMap->stageClose();
					//여기 위까진 ㄱㅊ .. 이 아래가 문제
					firstMap->stageOpen();

					player[i]->col->SetWorldPos(Vector2(0.0f, 0.0f));
					stage = STAGE::ST_1;

					break;
				}
			}

			player[i]->Update();
			titleMap->Update();
		}
#endif
		
		//솔로플레이
#if 0

		//바닥과 충돌중일 때는 계속 위에 있기
		if (player->col->Intersect(titleMap->floor))
		{
			player->onBlock(titleMap->floor->GetWorldPos().y);
		}
		else player->offBlock();

		//문열기
		if (player->col->Intersect(titleMap->door))
		{
			if (INPUT->KeyDown(VK_DOWN))
			{
				SOUND->Stop("doorSound");
				SOUND->Play("doorSound");
				titleMap->openDoor();
			}
		}
		//스테이지 이동
		else if (player->col->Intersect(titleMap->doorOP))
		{
			if (INPUT->KeyDown(VK_DOWN))
			{
				titleMap->stageClose();

				firstMap->stageOpen();

				player->col->SetWorldPos(Vector2(0.0f, 0.0f));
				stage = STAGE::ST_1;
			}
		}
 
		player->Update();
		titleMap->Update();
#endif

	}

///스테이지1
	else if (stage == STAGE::ST_1)
	{
		CAM->position.y = 240.0f;
		CAM->position.x = Utility::Saturate(CAM->position.x, 0.0f, 2320.0f);
		//CAM->position.x = Utility::Saturate(CAM->position.x, 0.0f, 2000.0f);

		//다인 코드
#if 1
		////열쇠
		//for (int j = 0; j < pNum; j++)
		//{
		//	if (player[j]->col->Intersect(firstMap->key))
		//	{
		//		if (!isKey)
		//		{
		//			SOUND->Play("key");
		//			firstMap->key->SetParentT(*player[j]->col);
		//			firstMap->key->SetLocalPos(Vector2(0.0f, 0.0f));
		//			//firstMap->key->SetLocalPos(Vector2(-50.0f, 50.0f));
		//			isKey = true;
		//		}
		//	}
		//	if (isKey)
		//	{
		//		Vector2 dir = player[j]->headCol->GetWorldPos() + keyPos - firstMap->key->GetWorldPos();
		//		firstMap->key->MoveWorldPos(dir * 10.0f * DELTA);

		//		if (INPUT->KeyPress(VK_RIGHT))
		//		{
		//			keyPos.x = -50.0f;
		//		}
		//		else if (INPUT->KeyPress(VK_LEFT))
		//		{
		//			keyPos.x = 50.0f;
		//		}
		//	}
		//	firstMap->key->Update();
		//}

		

		//for (int j = 0; j < pNum; j++)
		//{
		//	if (player[j]->col->Intersect(firstMap->door))
		//	{
		//		if (INPUT->KeyDown(VK_DOWN))
		//		{
		//			SOUND->Stop("doorSound");
		//			SOUND->Play("doorSound");
		//			firstMap->openDoor();
		//		}
		//	}
		//	//스테이지 이동
		//	else if (player[j]->col->Intersect(firstMap->doorOP))
		//	{
		//		if (INPUT->KeyDown(VK_DOWN))
		//		{
		//			firstMap->stageClose();
		//			isKey = false;

		//			titleMap->stageOpen();

		//			player[j]->col->SetWorldPos(Vector2(0.0f, 0.0f));
		//			stage = STAGE::TITLE;
		//		}
		//	}
		//}


		for (int j = 0; j < pNum; j++)
		{
			//버튼밟기
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

		// <<로 이동하는 바닥
		for (int j = 0; j < pNum; j++)
		{
			if (player[j]->col->Intersect(firstMap->floorLF))
			{
				player[j]->onBlock(firstMap->floorLF->GetWorldPos().y);
				player[j]->Update();
			}
			else
			{
				player[j]->offBlock();
				player[j]->Update();
			}
		}

		for (int j = 0; j < pNum; j++)
		{
			//리프트 밟기
			if (player[j]->col->Intersect(firstMap->lift))
			{
				if (firstMap->lift->GetWorldPos().y - 5.0f < player[j]->col->GetWorldPos().y)//(dir.y < 0.0f)
				{
					player[j]->onBlock(firstMap->lift->GetWorldPos().y);
					isFull = true;
				}

			}
			else if (player[j]->headCol->Intersect(firstMap->lift))
			{
				if (INPUT->KeyPress(VK_RIGHT))
				{
					//내가 벽 좌측
					if (player[j]->col->GetWorldPos().x < firstMap->lift->GetWorldPos().x)
					{
						// 내 scale *0.5 ..인데! 왜 24냐면 애니메이션 때문에 줄임
						int wallOn = firstMap->lift->GetWorldPos().x - firstMap->lift->scale.x * 0.5f - 22.0f;

						player[j]->col->SetWorldPosX(wallOn);
					}
				}
				else
				{
					float liftOn = player[j]->headCol->GetWorldPos().y + player[j]->headCol->scale.y;
					//내 머리위에 발판있을때
					if (liftOn < firstMap->lift->GetWorldPos().y)
					{
						liftOn += 10.0f;
						firstMap->lift->SetWorldPosY(liftOn);
					}
				}
			}
			else
			{
				isFull = false;
				player[j]->offBlock();
			}
			firstMap->lift->Update();
			player[j]->Update();
		}

		for (int j = 0; j < pNum; j++)
		{
			//벽 충돌
			for (int i = 0; i < 2; i++)
			{
				//벽밟고 서기				// 숫자를 너무 딱 맞추니까 충돌처리날때는 더 낮아서 오차 추가
				if (player[j]->col->Intersect(firstMap->wall[i]))
				{
					player[j]->onBlock(firstMap->wall[i]->GetWorldPos().y);
				}
				//벽의 옆구리 비비기
				else if (player[j]->headCol->Intersect(firstMap->wall[i]))
				{
					//내가 벽 좌측
					if (player[j]->col->GetWorldPos().x < firstMap->wall[i]->GetWorldPos().x)
					{
						// 내 scale *0.5 ..인데! 왜 24냐면 애니메이션 때문에 줄임
						int wallOn = firstMap->wall[i]->GetWorldPos().x - firstMap->wall[i]->scale.x * 0.5f - 22.0f;

						player[j]->col->SetWorldPosX(wallOn);
						//player->col->SetWorldPosX(2390.0f);
					}
					//내가 벽 우측
					else if (player[j]->col->GetWorldPos().x > firstMap->wall[i]->GetWorldPos().x)
					{
						int wallOn = firstMap->wall[i]->GetWorldPos().x + firstMap->wall[i]->scale.x * 0.5f + 22.0f;

						player[j]->col->SetWorldPosX(wallOn);
					}
				}
				else
				{
					player[j]->offBlock();
					player[j]->offWall();
				}
			}
			player[j]->Update();
		}

		for (int i = 0; i < 3; i++)
		{
			//바닥충돌
			for (int j = 0; j < pNum; j++)
			{
				if (firstMap->floor[i]->Intersect(player[j]->col))
				//if (player[i]->col->Intersect(firstMap->floor[i]))
				{
					player[j]->onBlock(firstMap->floor[i]->GetWorldPos().y);
					//break;
				}
				else if (firstMap->floor[i]->Intersect(player[j]->headCol))
				//else if (player[i]->headCol->Intersect(firstMap->floor[i]))
				{
					//내가 좌측
					if (player[j]->col->GetWorldPos().x < firstMap->floor[i]->GetWorldPos().x)
					{
						int wallOn = firstMap->floor[i]->GetWorldPos().x - firstMap->floor[i]->scale.x * 0.5f - 22.0f;

						player[j]->col->SetWorldPosX(wallOn);
						//break;
					}
					//내가 우측
					else if (player[j]->col->GetWorldPos().x > firstMap->floor[i]->GetWorldPos().x)
					{
						int wallOn = firstMap->floor[i]->GetWorldPos().x + firstMap->floor[i]->scale.x * 0.5f + 22.0f;

						player[j]->col->SetWorldPosX(wallOn);
						//break;
					}
				}
				else
				{
					player[j]->offWall();
					player[j]->offBlock();
					//break;
				}
				player[j]->Update();
			}
			firstMap->floor[i]->Update();
		}

		for (int j = 0; j < pNum; j++)
		{
			//계단충돌
			for (int i = 0; i < 3; i++)
			{
				if (player[j]->col->Intersect(firstMap->stair[i]))
				{
					//if (firstMap->stair[i]->GetWorldPos().y - 10.0f < player->col->GetWorldPos().y)//(dir.y < 0.0f)
					//{
						//벽 OFFSET_T로 바꿈
					player[j]->onBlock(firstMap->stair[i]->GetWorldPos().y);
					//}

				}
				else if (player[j]->headCol->Intersect(firstMap->stair[i]))
				{
					//내가 좌측
					if (player[j]->col->GetWorldPos().x < firstMap->stair[i]->GetWorldPos().x)
					{
						int wallOn = firstMap->stair[i]->GetWorldPos().x - firstMap->stair[i]->scale.x * 0.5f - 22.0f;

						player[j]->col->SetWorldPosX(wallOn);
						break;
					}
					//내가 우측
					else if (player[j]->col->GetWorldPos().x > firstMap->stair[i]->GetWorldPos().x)
					{
						int wallOn = firstMap->stair[i]->GetWorldPos().x + firstMap->stair[i]->scale.x * 0.5f + 22.0f;

						player[j]->col->SetWorldPosX(wallOn);
						break;
					}

				}
				else
				{
					player[j]->offWall();
					player[j]->offBlock();
				}
			}
			player[j]->Update();
		}

#endif

		//1플레이어 코드    
#if 0 

		//열쇠 따라다님
		if (player->col->Intersect(firstMap->key))
		{
			if (!isKey)
			{
				SOUND->Play("key");
				firstMap->key->SetParentT(*player->col);
				firstMap->key->SetLocalPos(Vector2(0.0f, 0.0f));
				//firstMap->key->SetLocalPos(Vector2(-50.0f, 50.0f));
				isKey = true;
			}
		}
		if (isKey)
		{
			Vector2 dir = player->headCol->GetWorldPos() + keyPos - firstMap->key->GetWorldPos();
			firstMap->key->MoveWorldPos(dir * 10.0f * DELTA);

			if (INPUT->KeyPress(VK_RIGHT))
			{
				keyPos.x = -50.0f;
			}
			else if (INPUT->KeyPress(VK_LEFT))
			{
				keyPos.x = 50.0f;
			}
		}
		firstMap->key->Update();

		//문열기
		if (player->col->Intersect(firstMap->door))
		{
			if (INPUT->KeyDown(VK_DOWN))
			{
				SOUND->Stop("doorSound");
				SOUND->Play("doorSound");
				firstMap->openDoor();
			}
		}
		//스테이지 이동
		else if (player->col->Intersect(firstMap->doorOP))
		{
			if (INPUT->KeyDown(VK_DOWN))
			{
				firstMap->stageClose();
				isKey = false;

				titleMap->stageOpen();

				player->col->SetWorldPos(Vector2(0.0f, 0.0f));
				stage = STAGE::TITLE;
			}
		}

		//버튼밟기
		if (player->col->Intersect(firstMap->button))
		{
			firstMap->Pressed();
			player->onBlock(firstMap->button->GetWorldPos().y + firstMap->button->scale.y);
		}
		//player->Update();
		//firstMap->Update();

		if (player->col->Intersect(firstMap->floorLF))
		{
			player->onBlock(firstMap->floorLF->GetWorldPos().y);
		}
		player->Update();

		//리프트 밟기
		if (player->col->Intersect(firstMap->lift))
		{
			if (firstMap->lift->GetWorldPos().y - 5.0f < player->col->GetWorldPos().y)//(dir.y < 0.0f)
			{
				player->onBlock(firstMap->lift->GetWorldPos().y);
				isFull = true;
			}
		}
		else if (player->headCol->Intersect(firstMap->lift))
		{
			if (INPUT->KeyPress(VK_RIGHT))
			{
				//내가 벽 좌측
				if (player->col->GetWorldPos().x < firstMap->lift->GetWorldPos().x)
				{
					// 내 scale *0.5 ..인데! 왜 24냐면 애니메이션 때문에 줄임
					int wallOn = firstMap->lift->GetWorldPos().x - firstMap->lift->scale.x * 0.5f - 22.0f;

					player->col->SetWorldPosX(wallOn);
					//player->col->SetWorldPosX(2390.0f);
				}
			}
			else
			{
				float liftOn = player->headCol->GetWorldPos().y + player->headCol->scale.y;
				//내 머리위에 발판있을때
				if (liftOn < firstMap->lift->GetWorldPos().y)
				{
					liftOn += 10.0f;
					firstMap->lift->SetWorldPosY(liftOn);
				}
			}
		}
		else
		{
			isFull = false;
			player->offBlock();
		}
		//firstMap->lift->Update();
		player->Update();

		//벽 충돌
		for (int i = 0; i < 2; i++)
		{
			//벽밟고 서기				// 숫자를 너무 딱 맞추니까 충돌처리날때는 더 낮아서 오차 추가
			if (player->col->Intersect(firstMap->wall[i]))
			{
				player->onBlock(firstMap->wall[i]->GetWorldPos().y);
				break;
			}
			//벽의 옆구리 비비기
			else if (player->headCol->Intersect(firstMap->wall[i]))
			{
				//내가 벽 좌측
				if (player->col->GetWorldPos().x < firstMap->wall[i]->GetWorldPos().x)
				{
					int wallOn = firstMap->wall[i]->GetWorldPos().x - firstMap->wall[i]->scale.x * 0.5f - 22.0f;

					player->col->SetWorldPosX(wallOn);
					break;
					//player->col->SetWorldPosX(2390.0f);
				}
				//내가 벽 우측
				else if (player->col->GetWorldPos().x > firstMap->wall[i]->GetWorldPos().x)
				{
					int wallOn = firstMap->wall[i]->GetWorldPos().x + firstMap->wall[i]->scale.x * 0.5f + 22.0f;

					player->col->SetWorldPosX(wallOn);
					break;
				}
			}
			else
			{
				player->offBlock();
				player->offWall();
			}
		}
		player->Update();

		//계단충돌
		for (int i = 0; i < 3; i++)
		{
			if (player->col->Intersect(firstMap->stair[i]))
			{
				if (firstMap->stair[i]->GetWorldPos().y - 10.0f < player->col->GetWorldPos().y)//(dir.y < 0.0f)
				{
					//벽 OFFSET_T로 바꿈
					player->onBlock(firstMap->stair[i]->GetWorldPos().y);
					break;
				}
			}
			else if (player->headCol->Intersect(firstMap->stair[i]))
			{
				//내가 좌측
				if (player->col->GetWorldPos().x < firstMap->stair[i]->GetWorldPos().x)
				{
					int wallOn = firstMap->stair[i]->GetWorldPos().x - firstMap->stair[i]->scale.x * 0.5f - 22.0f;

					player->col->SetWorldPosX(wallOn);
					break;
					//player->col->SetWorldPosX(2390.0f);
				}
				//내가 우측
				else if (player->col->GetWorldPos().x > firstMap->stair[i]->GetWorldPos().x)
				{
					int wallOn = firstMap->stair[i]->GetWorldPos().x + firstMap->stair[i]->scale.x * 0.5f + 22.0f;

					player->col->SetWorldPosX(wallOn);
					break;
				}

			}
			else
			{
				player->offWall();   
				player->offBlock();
			}
		}
		player->Update();

		//바닥충돌
		for (int i = 0; i < 3; i++)
		{
			if (player->col->Intersect(firstMap->floor[i]))
			{
				player->onBlock(firstMap->floor[i]->GetWorldPos().y);
				break;
			}
			else
			{
				//player->offWall();
				player->offBlock();
			}
			if (player->headCol->Intersect(firstMap->floor[i]))
			{
				//내가 좌측
				if (player->col->GetWorldPos().x < firstMap->floor[i]->GetWorldPos().x)
				{
					int wallOn = firstMap->floor[i]->GetWorldPos().x - firstMap->floor[i]->scale.x * 0.5f - 22.0f;

					player->col->SetWorldPosX(wallOn);
					break;
					//player->col->SetWorldPosX(2390.0f);
				}
				//내가 우측
				else if (player->col->GetWorldPos().x > firstMap->floor[i]->GetWorldPos().x)
				{
					int wallOn = firstMap->floor[i]->GetWorldPos().x + firstMap->floor[i]->scale.x * 0.5f + 22.0f;

					player->col->SetWorldPosX(wallOn);
					break;
				}
			}
			else
			{
				player->offWall();
				//player->offBlock();
			}
		}
		//player->Update();
		firstMap->Update();
#endif

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
	//player->Render();
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