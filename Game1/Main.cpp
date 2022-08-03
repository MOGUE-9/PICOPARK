#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	titleMap = new Title();
	firstMap = new Map1();

	player = new PicoCat();


	SOUND->AddSound("01Spring.mp3", "title", true);
	SOUND->SetVolume("title", 0.1f);

	SOUND->AddSound("jumSFX.mp3", "jump", false);


	SOUND->AddSound("03Doremi.mp3", "Stage1", true);

}

void Main::Release()
{
	SafeDelete(titleMap);
	SafeDelete(firstMap);
	SafeDelete(player);
}

void Main::Update()
{
	//ImGuiColorEditFlags
	//ImGui::ColorEdit4("d", (float*)&block->color, ImGuiColorEditFlags_PickerHueWheel);

	if (INPUT->KeyPress('L'))
	{
		CAM->position.x += 200.0f * DELTA;
	}

	//if (INPUT->KeyDown(VK_UP) || INPUT->KeyDown('W'))
	//{
	//	SOUND->Stop("jump");
	//	SOUND->Play("jump");
	//}

	//if (stage == STAGE::TITLE)
	//{
	//	SOUND->Stop("Stage1");
	//	SOUND->Play("title");
	//}

	if (stage == STAGE::ST_1)
	{
		//SOUND->Stop("title");
		//SOUND->Play("Stage1");


		//우측 맵 끝에 닿았을때 더 못가게 막는 update					// 960*0.5  = -480 + 30 + 내scale*0.5
		//player->col->SetWorldPosX(Utility::Saturate(player->col->GetWorldPos().x, -426.0f , 2775.0f)); //2800-25(플레이어 크기)
	
		if (isFull)
		{
			cout << firstMap->lift->GetWorldPos().y << endl;
	
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

	}

	//cout << "포" << endl;
	//cout << firstMap->wall[0]->GetWorldPos().y << endl;
	//cout << player->col->GetWorldPos().x << endl;
	//cout << "피" << endl;
	//cout << firstMap->wall[0]->GetWorldPivot().y << endl;
	//cout << player->col->GetWorldPivot().x << endl; 

	player->Update();

	titleMap->Update();
	firstMap->Update();
}

void Main::LateUpdate()
{
	Vector2 velocity = player->col->GetWorldPos() - CAM->position;
	CAM->position += velocity * 5.0f * DELTA;

	///메인
	if (stage==STAGE::TITLE)
	{
		CAM->position.y = 240.0f;
		CAM->position.x = 0.0f;
		//플레이어가 바닥의 UP방향에 있을 때만 충돌 :: 
		// 양옆으로 부딪히면 좌우 위치에 고정되게하기 -> Title cpp에서?
		if (true)
		{

		}
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

	}
	///스테이지1
	else if (stage == STAGE::ST_1)
	{
		CAM->position.y = 240.0f;
		CAM->position.x = Utility::Saturate(CAM->position.x, 0.0f, 2320.0f);
		//CAM->position.x = Utility::Saturate(CAM->position.x, 0.0f, 2000.0f);

		//문열기
		if (player->col->Intersect(firstMap->door))
		{
			if (INPUT->KeyDown(VK_DOWN))
			{
				firstMap->openDoor();
			}
		}
		//스테이지 이동
		else if (player->col->Intersect(firstMap->doorOP))
		{
			if (INPUT->KeyDown(VK_DOWN))
			{
				firstMap->stageClose();

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
		player->Update();
		firstMap->Update();

		//리프트 밟기
		if (player->col->Intersect(firstMap->lift))
		{
			if (firstMap->lift->GetWorldPos().y - 10.0f < player->col->GetWorldPos().y)//(dir.y < 0.0f)
			{
				player->onBlock(firstMap->lift->GetWorldPos().y);
				isFull = true;
			}
			else 
			{
				player->onWall(firstMap->lift->GetWorldPivot().x, firstMap->lift->scale.x);
			}

			
		}
		else
		{
			isFull = false;
			player->offBlock();
		}
		player->Update();

		//벽 충돌
		for (int i = 0; i < 2; i++)
		{
			if (player->col->Intersect(firstMap->wall[i]))
			{

				//Vector2 dir = firstMap->wall[i]->GetWorldPos() - player->col->GetWorldPos();

				//cout << "포" << endl;
				//cout << firstMap->wall[i]->GetWorldPos().x << endl;
				//cout << player->col->GetWorldPos().x << endl;
				//cout << "피" << endl;
				//cout << firstMap->wall[i]->GetWorldPivot().x << endl;
				//cout << player->col->GetWorldPivot().x << endl; 

				//벽밟고 서기				// 숫자를 너무 딱 맞추니까 충돌처리날때는 더 낮아서 오차 추가
				if (firstMap->wall[i]->GetWorldPos().y - 10.0f < player->col->GetWorldPos().y)//(dir.y < 0.0f)
				{
					벽 OFFSET_T로 바꿈
					player->onBlock(firstMap->wall[i]->GetWorldPos().y);
					break;
				}

				else //(dir.y > 0.0f)
				{
					//내가 벽 좌측
					if (player->col->GetWorldPos().x < firstMap->wall[i]->GetWorldPos().x)
					{
						// 내 scale *0.5 ..인데! 왜 24냐면 애니메이션 때문에 줄임
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

				
			}
			
			else
			{
				player->offBlock();
				player->offWall();
			}
		}
		player->Update();


		for (int i = 0; i < 3; i++)
		{
			//계단충돌
			if (player->col->Intersect(firstMap->stair[i]))
			{
				if (firstMap->stair[i]->GetWorldPos().y - 10.0f < player->col->GetWorldPos().y)//(dir.y < 0.0f)
				{
					//벽 OFFSET_T로 바꿈
					player->onBlock(firstMap->stair[i]->GetWorldPos().y);
					break;
				}
				else 
				{
					//내가 좌측
					if (player->col->GetWorldPos().x < firstMap->stair[i]->GetWorldPos().x)
					{
						// 내 scale *0.5 ..인데! 왜 24냐면 애니메이션 때문에 줄임
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
					//player->onWall(firstMap->stair[i]->GetWorldPivot().x, firstMap->stair[i]->scale.x);
					//break;
				}
				
			}
			else
			{
				//player->offWall();
				player->offBlock();
			}

			//바닥충돌
			if (player->col->Intersect(firstMap->floor[i]))
			{
				if (firstMap->floor[i]->GetWorldPos().y - 10.0f < player->col->GetWorldPos().y)//(dir.y < 0.0f)
				{
					player->onBlock(firstMap->floor[i]->GetWorldPos().y);
					break;
				}
				else
				{
					//좌측
					if (player->col->GetWorldPivot().x < firstMap->floor[i]->GetWorldPivot().x)
					{
						// 내 scale *0.5 ..인데! 왜 24냐면 애니메이션 때문에 줄임
						float wallOn = firstMap->floor[i]->GetWorldPivot().x - firstMap->floor[i]->scale.x * 0.5f - 25.0f;
						player->col->SetWorldPosX(wallOn);
					}
					//우측
					else if (player->col->GetWorldPivot().x > firstMap->floor[i]->GetWorldPivot().x)
					{
						float wallOn = firstMap->floor[i]->GetWorldPivot().x + firstMap->floor[i]->scale.x * 0.5f + 25.0f;
						player->col->SetWorldPosX(wallOn);

					}

					//player->onWall(firstMap->floor[i]->GetWorldPivot().x, firstMap->floor[i]->scale.x);
					break;
				}

			}
			else
			{
				player->offBlock();
			}
		}
		player->Update();

		firstMap->Update();

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
	//block->Render();
	player->Render();
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