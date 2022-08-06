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
		player[i]->col->SetWorldPosX(100.0f - 200.0f * i);
	}
	
	SOUND->AddSound("01Spring.mp3", "title", true);
	SOUND->SetVolume("title", 0.1f);

	//ȿ����
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

	///�÷��̾� �̵�
#if 1
	///1P
	//������
	if (INPUT->KeyPress(VK_RIGHT)/* || INPUT->KeyPress('D')*/)
	{
		player[0]->stat = CATSTAT::RIGHTPRESS;
		//player->stat = CATSTAT::RIGHTPRESS;
	}
	//��������
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
	//������ Ű ���� �� :: ������
	if (INPUT->KeyUp(VK_RIGHT))
	{
		player[0]->stat = CATSTAT::RIGHTUP;
	}
	//����
	else if (INPUT->KeyUp(VK_LEFT))
	{
		player[0]->stat = CATSTAT::LEFTUP;
	}
	//�� �� �ƴҶ��� ����
	if (INPUT->KeyDown(VK_UP))
	{
		player[0]->stat = CATSTAT::JUMPDOWN;
	}
	//Ű ���� ���� 1ȸ ����
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
	//������ Ű ���� �� :: ������
	if (INPUT->KeyUp('D'))
	{
		player[1]->stat = CATSTAT::RIGHTUP;
	}
	//����
	else if (INPUT->KeyUp('A'))
	{
		player[1]->stat = CATSTAT::LEFTUP;
	}
	//�� �� �ƴҶ��� ���� << �ٵ� �̰� �̷��� �ϴ��� �׳� ... �� ���� Ű�� ���� �ִ°� ������
	if (INPUT->KeyDown('W'))
	{
		player[1]->stat = CATSTAT::JUMPDOWN;
	}
	//Ű ���� ���� 1ȸ ����
	if (INPUT->KeyUp('W'))
	{
		player[1]->stat = CATSTAT::JUMPUP;
	}
#endif

	//solo
#if 0
	///�÷��̾� �̵�
	//������
	if (INPUT->KeyPress(VK_RIGHT) || INPUT->KeyPress('D'))
	{
		player->stat = CATSTAT::RIGHTPRESS;
	}

	//��������
	else if (INPUT->KeyPress(VK_LEFT) || INPUT->KeyPress('S'))
	{
		player->stat = CATSTAT::LEFTPRESS;
	}
	else
	{
		player->stat = CATSTAT::STAND;
	}


	//������ Ű ���� �� :: ������
	if (INPUT->KeyUp(VK_RIGHT) || INPUT->KeyUp('D'))
	{
		player->stat = CATSTAT::RIGHTUP;
	}
	//����
	else if (INPUT->KeyUp(VK_LEFT) || INPUT->KeyUp('S'))
	{
		player->stat = CATSTAT::LEFTUP;
	}

	//�� �� �ƴҶ��� ���� << �ٵ� �̰� �̷��� �ϴ��� �׳� ... �� ���� Ű�� ���� �ִ°� ������
	if (INPUT->KeyDown(VK_UP) || INPUT->KeyDown('W'))
	{
		player->stat = CATSTAT::JUMPDOWN;
	}

	//Ű ���� ���� 1ȸ ����
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

		SOUND->Stop("Stage1");
		//SOUND->Play("title");

	///������-----------------------------------------------
		// P1 �� ������ door�� intersect üũ
		if (player[0]->col->Intersect(titleMap->door))
		{
			//�� �տ��� down Ű ������ ��
			if (INPUT->KeyDown(VK_DOWN))
			{
				//�Ҹ����� ������
				SOUND->Stop("doorSound");
				SOUND->Play("doorSound");

				titleMap->openDoor();
			}
		}
		else if (player[0]->col->Intersect(titleMap->doorOP)) //������ doorOP�� intersect üũ
		{
			//������ �տ��� down Ű ������ ��
			if (INPUT->KeyDown(VK_DOWN))
			{
				player[0]->isEnd = true;
			}
		}

		// P2 �� ������ door�� intersect üũ
		if (player[1]->col->Intersect(titleMap->door))
		{
			if (INPUT->KeyDown('S'))
			{
				//������ �Ҹ����� ������
				SOUND->Stop("doorSound");
				SOUND->Play("doorSound");

				titleMap->openDoor();
			}
		}
		else if (player[1]->col->Intersect(titleMap->doorOP)) //������ doorOP�� intersect üũ
		{
			//������ �տ��� down Ű ������ ��
			if (INPUT->KeyDown('S'))
			{
				player[1]->isEnd = true;
			}
		}

		//�÷��̾� ��ġ �ʱ� ��ġ�� �ű��
		if (player[0]->isEnd && player[1]->isEnd)
		{
			for (int j = 0; j < pNum; j++)
			{
				player[j]->isEnd = false;
				player[j]->col->SetWorldPosX(100.0f - 200.0f * j);
			}

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
		//SOUND->Play("Stage1");

		
		
	//��Ƽ


		if (isFull)
		{
			if (firstMap->lift->GetWorldPos().y >= 260.0f) //�ⱸ �ٴ� ����
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

	///������-----------------------------------------------
		// P1 �� ������ door�� intersect üũ
		if (player[0]->col->Intersect(firstMap->door))
		{
			//�� �տ��� down Ű ������ ��
			if (INPUT->KeyDown(VK_DOWN))
			{
				//���� ���� üũ
				if (player[0]->isHave)
				{
					//������ �Ҹ����� ������
					SOUND->Stop("doorSound");
					SOUND->Play("doorSound");
					firstMap->key->visible = false;
					firstMap->openDoor();
				}
			}
		}
		else if (player[0]->col->Intersect(firstMap->doorOP)) //������ doorOP�� intersect üũ
		{
			//������ �տ��� down Ű ������ ��
			if (INPUT->KeyDown(VK_DOWN))
			{
				player[0]->isEnd = true;
			}
		}

		// P2 �� ������ door�� intersect üũ
		if (player[1]->col->Intersect(firstMap->door))
		{
			if (INPUT->KeyDown('S'))
			{
				//���� ���� üũ
				if (player[1]->isHave)
				{
					//������ �Ҹ����� ������
					SOUND->Stop("doorSound");
					SOUND->Play("doorSound");
					firstMap->key->visible = false;
					firstMap->openDoor();
				}
			}
		}
		else if (player[1]->col->Intersect(firstMap->doorOP)) //������ doorOP�� intersect üũ
		{
			//������ �տ��� down Ű ������ ��
			if (INPUT->KeyDown('S'))
			{
				player[1]->isEnd = true;
			}
		}

		//�÷��̾� ��ġ �ʱ� ��ġ�� �ű��
		if (player[0]->isEnd && player[1]->isEnd)
		{
			for (int j = 0; j < pNum; j++)
			{
				player[j]->isHave = false;
				player[j]->isEnd = false;
				player[j]->col->SetWorldPosX(100.0f - 200.0f * j);
			}

			firstMap->stageClose();
			isKey = false;

			titleMap->stageOpen();

			stage = STAGE::TITLE;
		}

		//���� ì��������
		if (isKey)
		{
			for (int j = 0; j < pNum; j++)
			{
				//���� ���� �ִ� ������Ը�
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


	}

	//cout << "��" << endl;
	//cout << firstMap->wall[0]->GetWorldPos().y << endl;
	//cout << player->col->GetWorldPos().x << endl;
	//cout << "��" << endl;
	//cout << firstMap->wall[0]->GetWorldPivot().y << endl;
	//cout << player->col->GetWorldPivot().x << endl; 

	for (int i = 0; i < pNum; i++)
	{
		player[i]->Update();
	}

	titleMap->Update();
	firstMap->Update();
}

void Main::LateUpdate()
{
	//�÷��̾� ���� �浹

	//for (int j = 0; j < pNum; j++)
	//{
	//	int i = 1 - j;
	//	if (player[j]->headCol->Intersect(player[i]->headCol))
	//	{
	//		//����� ����				// ���ڸ� �ʹ� �� ���ߴϱ� �浹ó�������� �� ���Ƽ� ���� �߰�
	//		if (player[j]->col->Intersect(player[i]->headCol))
	//		{
	//			player[j]->onBlock(player[i]->headCol->GetWorldPos().y);
	//		}
	//		//���� ������ ����
	//		else if (player[j]->headCol->Intersect(player[i]->headCol))
	//		{
	//			//���� �� ����
	//			if (player[j]->col->GetWorldPos().x < player[i]->headCol->GetWorldPos().x)
	//			{
	//				// �� scale *0.5 ..�ε�! �� 24�ĸ� �ִϸ��̼� ������ ����
	//				int wallOn = player[i]->headCol->GetWorldPos().x - player[i]->headCol->scale.x * 0.5f - 22.0f;
	//
	//				player[j]->col->SetWorldPosX(wallOn);
	//				//player->col->SetWorldPosX(2390.0f);
	//			}
	//			//���� �� ����
	//			else if (player[j]->col->GetWorldPos().x > player[i]->headCol->GetWorldPos().x)
	//			{
	//				int wallOn = player[i]->headCol->GetWorldPos().x + player[i]->headCol->scale.x * 0.5f + 22.0f;
	//
	//				player[j]->col->SetWorldPosX(wallOn);
	//			}
	//		}
	//		else
	//		{
	//			player[j]->offBlock();
	//			player[j]->offWall();
	//		}
	//	}
	//	player[j]->Update();
	//}



	///Ÿ��Ʋ
	if (stage == STAGE::TITLE)
	{

		CAM->position.y = 240.0f;
		CAM->position.x = 0.0f;
		//�����÷���
#if 1


				//���� �� ���� ������� �� ������ ���� update					// 960*0.5  = -480 + 30 + ��scale*0.5
		for (int i = 0; i < pNum; i++)
		{
			player[i]->col->SetWorldPosX(Utility::Saturate(player[i]->col->GetWorldPos().x, -455.0f, 455.0f));
		}

		for (int i = 0; i < pNum; i++)
		{
			//�ٴڰ� �浹���� ���� ��� ���� �ֱ�
			if (player[i]->col->Intersect(titleMap->floor))
			{
				player[i]->onBlock(titleMap->floor->GetWorldPos().y);
			}
			else player[i]->offBlock();

			player[i]->Update();
		}

#endif
		//�ַ��÷���
#if 0

		//�ٴڰ� �浹���� ���� ��� ���� �ֱ�
		if (player->col->Intersect(titleMap->floor))
		{
			player->onBlock(titleMap->floor->GetWorldPos().y);
		}
		else player->offBlock();

		//������
		if (player->col->Intersect(titleMap->door))
		{
			if (INPUT->KeyDown(VK_DOWN))
			{
				SOUND->Stop("doorSound");
				SOUND->Play("doorSound");
				titleMap->openDoor();
			}
		}
		//�������� �̵�
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

///��������1
	else if (stage == STAGE::ST_1)
	{
		CAM->position.y = 240.0f;
		CAM->position.x = Utility::Saturate(CAM->position.x, 0.0f, 2320.0f);
		//CAM->position.x = Utility::Saturate(CAM->position.x, 0.0f, 2000.0f);

		//���� �ڵ�
#if 1
		//���� �� ���� ������� �� ������ ���� update					// 960*0.5  = -480 + 30 + ��scale*0.5
		for (int i = 0; i < pNum; i++)
		{
			player[i]->col->SetWorldPosX(Utility::Saturate(player[i]->col->GetWorldPos().x, -480.0f, 2775.0f));
		}


		//����
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
		//	//�������� �̵�
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
			//��ư���
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

		// <<�� �̵��ϴ� �ٴ�
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

		///����Ʈ ���
		for (int j = 0; j < pNum; j++)
		{
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
					//���� �� ����
					if (player[j]->col->GetWorldPos().x < firstMap->lift->GetWorldPos().x)
					{
						// �� scale *0.5 ..�ε�! �� 24�ĸ� �ִϸ��̼� ������ ����
						int wallOn = firstMap->lift->GetWorldPos().x - firstMap->lift->scale.x * 0.5f - 22.0f;

						player[j]->col->SetWorldPosX(wallOn);
					}
				}
				else
				{
					float liftOn = player[j]->headCol->GetWorldPos().y + player[j]->headCol->scale.y;
					//�� �Ӹ����� ����������
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
		
		//�� �浹
		for (int j = 0; j < pNum; j++)
		{
			for (int i = 0; i < 2; i++)
			{
				//����� ����				// ���ڸ� �ʹ� �� ���ߴϱ� �浹ó�������� �� ���Ƽ� ���� �߰�
				if (player[j]->col->Intersect(firstMap->wall[i]))
				{
					player[j]->onBlock(firstMap->wall[i]->GetWorldPos().y);
				}
				//���� ������ ����
				else if (player[j]->headCol->Intersect(firstMap->wall[i]))
				{
					//���� �� ����
					if (player[j]->col->GetWorldPos().x < firstMap->wall[i]->GetWorldPos().x)
					{
						// �� scale *0.5 ..�ε�! �� 24�ĸ� �ִϸ��̼� ������ ����
						int wallOn = firstMap->wall[i]->GetWorldPos().x - firstMap->wall[i]->scale.x * 0.5f - 22.0f;

						player[j]->col->SetWorldPosX(wallOn);
						//player->col->SetWorldPosX(2390.0f);
					}
					//���� �� ����
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

		//�ٴ��浹
		for (int i = 0; i < 3; i++)
		{
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
					//���� ����
					if (player[j]->col->GetWorldPos().x < firstMap->floor[i]->GetWorldPos().x)
					{
						int wallOn = firstMap->floor[i]->GetWorldPos().x - firstMap->floor[i]->scale.x * 0.5f - 22.0f;

						player[j]->col->SetWorldPosX(wallOn);
						//break;
					}
					//���� ����
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
			//����浹
			for (int i = 0; i < 3; i++)
			{
				if (player[j]->col->Intersect(firstMap->stair[i]))
				{
					//if (firstMap->stair[i]->GetWorldPos().y - 10.0f < player->col->GetWorldPos().y)//(dir.y < 0.0f)
					//{
						//�� OFFSET_T�� �ٲ�
					player[j]->onBlock(firstMap->stair[i]->GetWorldPos().y);
					//}

				}
				else if (player[j]->headCol->Intersect(firstMap->stair[i]))
				{
					//���� ����
					if (player[j]->col->GetWorldPos().x < firstMap->stair[i]->GetWorldPos().x)
					{
						int wallOn = firstMap->stair[i]->GetWorldPos().x - firstMap->stair[i]->scale.x * 0.5f - 22.0f;

						player[j]->col->SetWorldPosX(wallOn);
						break;
					}
					//���� ����
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

		//1�÷��̾� �ڵ�    
#if 0 

		//���� ����ٴ�
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

		//������
		if (player->col->Intersect(firstMap->door))
		{
			if (INPUT->KeyDown(VK_DOWN))
			{
				SOUND->Stop("doorSound");
				SOUND->Play("doorSound");
				firstMap->openDoor();
			}
		}
		//�������� �̵�
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

		//��ư���
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

		//����Ʈ ���
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
				//���� �� ����
				if (player->col->GetWorldPos().x < firstMap->lift->GetWorldPos().x)
				{
					// �� scale *0.5 ..�ε�! �� 24�ĸ� �ִϸ��̼� ������ ����
					int wallOn = firstMap->lift->GetWorldPos().x - firstMap->lift->scale.x * 0.5f - 22.0f;

					player->col->SetWorldPosX(wallOn);
					//player->col->SetWorldPosX(2390.0f);
				}
			}
			else
			{
				float liftOn = player->headCol->GetWorldPos().y + player->headCol->scale.y;
				//�� �Ӹ����� ����������
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

		//�� �浹
		for (int i = 0; i < 2; i++)
		{
			//����� ����				// ���ڸ� �ʹ� �� ���ߴϱ� �浹ó�������� �� ���Ƽ� ���� �߰�
			if (player->col->Intersect(firstMap->wall[i]))
			{
				player->onBlock(firstMap->wall[i]->GetWorldPos().y);
				break;
			}
			//���� ������ ����
			else if (player->headCol->Intersect(firstMap->wall[i]))
			{
				//���� �� ����
				if (player->col->GetWorldPos().x < firstMap->wall[i]->GetWorldPos().x)
				{
					int wallOn = firstMap->wall[i]->GetWorldPos().x - firstMap->wall[i]->scale.x * 0.5f - 22.0f;

					player->col->SetWorldPosX(wallOn);
					break;
					//player->col->SetWorldPosX(2390.0f);
				}
				//���� �� ����
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

		//����浹
		for (int i = 0; i < 3; i++)
		{
			if (player->col->Intersect(firstMap->stair[i]))
			{
				if (firstMap->stair[i]->GetWorldPos().y - 10.0f < player->col->GetWorldPos().y)//(dir.y < 0.0f)
				{
					//�� OFFSET_T�� �ٲ�
					player->onBlock(firstMap->stair[i]->GetWorldPos().y);
					break;
				}
			}
			else if (player->headCol->Intersect(firstMap->stair[i]))
			{
				//���� ����
				if (player->col->GetWorldPos().x < firstMap->stair[i]->GetWorldPos().x)
				{
					int wallOn = firstMap->stair[i]->GetWorldPos().x - firstMap->stair[i]->scale.x * 0.5f - 22.0f;

					player->col->SetWorldPosX(wallOn);
					break;
					//player->col->SetWorldPosX(2390.0f);
				}
				//���� ����
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

		//�ٴ��浹
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
				//���� ����
				if (player->col->GetWorldPos().x < firstMap->floor[i]->GetWorldPos().x)
				{
					int wallOn = firstMap->floor[i]->GetWorldPos().x - firstMap->floor[i]->scale.x * 0.5f - 22.0f;

					player->col->SetWorldPosX(wallOn);
					break;
					//player->col->SetWorldPosX(2390.0f);
				}
				//���� ����
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
}

void Main::ResizeScreen()
{

}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Game1");
    app.SetInstance(instance);
	app.InitWidthHeight(960.0f,540.0f); // �������Ӻ��� (1280.0f,720.0f)
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}