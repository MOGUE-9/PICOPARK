#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	titleMap = new Title();
	firstMap = new Map1();

	pNum = 2;

	//player = new PicoCat();
	for (int i = 0; i < pNum; i++)
	{
		player[i] = new PicoCat();
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

	if (INPUT->KeyPress('L'))
	{
		CAM->position.x += 200.0f * DELTA;
	}

	if (INPUT->KeyDown(VK_UP) || INPUT->KeyDown('W'))
	{
		SOUND->Stop("jump");
		SOUND->Play("jump");
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
		for (int i = 0; i < pNum; i++)
		{
			player[i]->stat = CATSTAT::RIGHTPRESS;
		}
		//player->stat = CATSTAT::RIGHTPRESS;
	}

	//��������
	else if (INPUT->KeyPress(VK_LEFT) || INPUT->KeyPress('S'))
	{
		for (int i = 0; i < pNum; i++)
		{
			player[i]->stat = CATSTAT::LEFTPRESS;
		}

		//player->stat = CATSTAT::LEFTPRESS;
	}
	else
	{
		for (int i = 0; i < pNum; i++)
		{
			player[i]->stat = CATSTAT::STAND;
		}
		//player->stat = CATSTAT::STAND;
	}


	//������ Ű ���� �� :: ������
	if (INPUT->KeyUp(VK_RIGHT) || INPUT->KeyUp('D'))
	{
		for (int i = 0; i < pNum; i++)
		{
			player[i]->stat = CATSTAT::RIGHTUP;
		}
		//player->stat = CATSTAT::RIGHTUP;
	}
	//����
	else if (INPUT->KeyUp(VK_LEFT) || INPUT->KeyUp('S'))
	{
		for (int i = 0; i < pNum; i++)
		{
			player[i]->stat = CATSTAT::LEFTUP;
		}
		//player->stat = CATSTAT::LEFTUP;
	}

	//�� �� �ƴҶ��� ���� << �ٵ� �̰� �̷��� �ϴ��� �׳� ... �� ���� Ű�� ���� �ִ°� ������
	if (INPUT->KeyDown(VK_UP) || INPUT->KeyDown('W'))
	{
		for (int i = 0; i < pNum; i++)
		{
			player[i]->stat = CATSTAT::JUMPDOWN;
		}
		//player->stat = CATSTAT::JUMPDOWN;
	}

	//Ű ���� ���� 1ȸ ����
	if (INPUT->KeyUp(VK_UP) || INPUT->KeyUp('W'))
	{
		for (int i = 0; i < pNum; i++)
		{
			player[i]->stat = CATSTAT::JUMPUP;
		}
		//player->stat = CATSTAT::JUMPUP;
	}

#endif

	if (stage == STAGE::TITLE)
	{
		SOUND->Stop("Stage1");
		SOUND->Play("title");
	}

	if (stage == STAGE::ST_1)
	{
		SOUND->Stop("title");
		SOUND->Play("Stage1");

		//���� �� ���� ������� �� ������ ���� update					// 960*0.5  = -480 + 30 + ��scale*0.5
		for (int i = 0; i < pNum; i++)
		{
			player[i]->col->SetWorldPosX(Utility::Saturate(player[i]->col->GetWorldPos().x, -480.0f, 2775.0f));
		}
		//player->col->SetWorldPosX(Utility::Saturate(player->col->GetWorldPos().x, -480.0f , 2775.0f)); //2800-25(�÷��̾� ũ��)
	
		if (isFull)
		{
												//�ⱸ �ٴ� ����
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
	//player->Update();

	titleMap->Update();
	firstMap->Update();
}

void Main::LateUpdate()
{

	float velo = (player[0]->col->GetWorldPos().x + player[pNum - 1]->col->GetWorldPos().x) * 0.5f - CAM->position.x;
	Vector2 velocity;
	velocity.x = velo;

	//Vector2 velocity = player->col->GetWorldPos() - CAM->position;

	CAM->position += velocity * 5.0f * DELTA;

	///Ÿ��Ʋ
	if (stage == STAGE::TITLE)
	{
		CAM->position.y = 240.0f;
		CAM->position.x = 0.0f;
		//�÷��̾ �ٴ��� UP���⿡ ���� ���� �浹 :: 
		// �翷���� �ε����� �¿� ��ġ�� �����ǰ��ϱ� -> Title cpp����?
		if (true)
		{

		}

		//�����÷���
#if 1
		for (int i = 0; i < pNum; i++)
		{
			//�ٴڰ� �浹���� ���� ��� ���� �ֱ�
			if (player[i]->col->Intersect(titleMap->floor))
			{
				player[i]->onBlock(titleMap->floor->GetWorldPos().y);
			}
			else player[i]->offBlock();
		}

		for (int i = 0; i < pNum; i++)
		{	//������
			if (titleMap->door->colOnOff)
			{
				if (player[i]->col->Intersect(titleMap->door))
				{
					if (INPUT->KeyDown(VK_DOWN))
					{
						SOUND->Stop("doorSound");
						SOUND->Play("doorSound");
						titleMap->openDoor();
					}
				}
			}
			//�������� �̵�
			else if (player[i]->col->Intersect(titleMap->doorOP))
			{
				if (INPUT->KeyDown(VK_DOWN))
				{
					titleMap->stageClose();

					firstMap->stageOpen();

					player[i]->col->SetWorldPos(Vector2(0.0f, 0.0f));
					stage = STAGE::ST_1;
				}
			}

			player[i]->Update();
			titleMap->Update();
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
		for (int i = 0; i < pNum; i++)
		{
			//���� ����ٴ�
			if (player[i]->col->Intersect(firstMap->key))
			{
				if (!isKey)
				{
					SOUND->Play("key");
					firstMap->key->SetParentT(*player[i]->col);
					firstMap->key->SetLocalPos(Vector2(0.0f, 0.0f));
					//firstMap->key->SetLocalPos(Vector2(-50.0f, 50.0f));
					isKey = true;
				}
			}
			if (isKey)
			{
				Vector2 dir = player[i]->headCol->GetWorldPos() + keyPos - firstMap->key->GetWorldPos();
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
			if (player[i]->col->Intersect(firstMap->door))
			{
				if (INPUT->KeyDown(VK_DOWN))
				{
					SOUND->Stop("doorSound");
					SOUND->Play("doorSound");
					firstMap->openDoor();
				}
			}
			//�������� �̵�
			else if (player[i]->col->Intersect(firstMap->doorOP))
			{
				if (INPUT->KeyDown(VK_DOWN))
				{
					firstMap->stageClose();
					isKey = false;

					titleMap->stageOpen();

					player[i]->col->SetWorldPos(Vector2(0.0f, 0.0f));
					stage = STAGE::TITLE;
				}
			}

			//��ư���
			if (player[i]->col->Intersect(firstMap->button))
			{
				firstMap->Pressed();
				//SOUND->Stop("button");
				//SOUND->Play("button");
				player[i]->onBlock(firstMap->button->GetWorldPos().y + firstMap->button->scale.y);
			}
			player[i]->Update();
			firstMap->Update();

			if (player[i]->col->Intersect(firstMap->floorLF))
			{
				player[i]->onBlock(firstMap->floorLF->GetWorldPos().y);
			}
			player[i]->Update();


			//����Ʈ ���
			if (player[i]->col->Intersect(firstMap->lift))
			{
				if (firstMap->lift->GetWorldPos().y - 5.0f < player[i]->col->GetWorldPos().y)//(dir.y < 0.0f)
				{
					player[i]->onBlock(firstMap->lift->GetWorldPos().y);
					isFull = true;
				}

			}
			else if (player[i]->headCol->Intersect(firstMap->lift))
			{
				if (INPUT->KeyPress(VK_RIGHT))
				{
					//���� �� ����
					if (player[i]->col->GetWorldPos().x < firstMap->lift->GetWorldPos().x)
					{
						// �� scale *0.5 ..�ε�! �� 24�ĸ� �ִϸ��̼� ������ ����
						int wallOn = firstMap->lift->GetWorldPos().x - firstMap->lift->scale.x * 0.5f - 22.0f;

						player[i]->col->SetWorldPosX(wallOn);
						//player->col->SetWorldPosX(2390.0f);
					}
				}
				else
				{
					float liftOn = player[i]->headCol->GetWorldPos().y + player[i]->headCol->scale.y;
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
				player[i]->offBlock();
			}
			firstMap->lift->Update();
			player[i]->Update();

			//�� �浹
			for (int i = 0; i < 2; i++)
			{
				//����� ����				// ���ڸ� �ʹ� �� ���ߴϱ� �浹ó�������� �� ���Ƽ� ���� �߰�
				if (player[i]->col->Intersect(firstMap->wall[i]))
				{
					player[i]->onBlock(firstMap->wall[i]->GetWorldPos().y);
					break;
				}
				//���� ������ ����
				else if (player[i]->headCol->Intersect(firstMap->wall[i]))
				{
					//���� �� ����
					if (player[i]->col->GetWorldPos().x < firstMap->wall[i]->GetWorldPos().x)
					{
						// �� scale *0.5 ..�ε�! �� 24�ĸ� �ִϸ��̼� ������ ����
						int wallOn = firstMap->wall[i]->GetWorldPos().x - firstMap->wall[i]->scale.x * 0.5f - 22.0f;

						player[i]->col->SetWorldPosX(wallOn);
						break;
						//player->col->SetWorldPosX(2390.0f);
					}
					//���� �� ����
					else if (player[i]->col->GetWorldPos().x > firstMap->wall[i]->GetWorldPos().x)
					{
						int wallOn = firstMap->wall[i]->GetWorldPos().x + firstMap->wall[i]->scale.x * 0.5f + 22.0f;

						player[i]->col->SetWorldPosX(wallOn);
						break;
					}
				}
				else
				{
					player[i]->offBlock();
					player[i]->offWall();
				}
			}
			player[i]->Update();

			//����浹
			for (int i = 0; i < 3; i++)
			{
				if (player[i]->col->Intersect(firstMap->stair[i]))
				{
					//if (firstMap->stair[i]->GetWorldPos().y - 10.0f < player->col->GetWorldPos().y)//(dir.y < 0.0f)
					//{
						//�� OFFSET_T�� �ٲ�
					player[i]->onBlock(firstMap->stair[i]->GetWorldPos().y);
					//}

				}
				else if (player[i]->headCol->Intersect(firstMap->stair[i]))
				{
					//���� ����
					if (player[i]->col->GetWorldPos().x < firstMap->stair[i]->GetWorldPos().x)
					{
						// �� scale *0.5 ..�ε�! �� 24�ĸ� �ִϸ��̼� ������ ����
						int wallOn = firstMap->stair[i]->GetWorldPos().x - firstMap->stair[i]->scale.x * 0.5f - 22.0f;

						player[i]->col->SetWorldPosX(wallOn);
						break;
						//player->col->SetWorldPosX(2390.0f);
					}
					//���� ����
					else if (player[i]->col->GetWorldPos().x > firstMap->stair[i]->GetWorldPos().x)
					{
						int wallOn = firstMap->stair[i]->GetWorldPos().x + firstMap->stair[i]->scale.x * 0.5f + 22.0f;

						player[i]->col->SetWorldPosX(wallOn);
						break;
					}

				}
				else
				{
					player[i]->offWall();
					player[i]->offBlock();
				}
			}
			player[i]->Update();

			//�ٴ��浹
			for (int i = 0; i < 3; i++)
			{
				if (player[i]->col->Intersect(firstMap->floor[i]))
				{
					player[i]->onBlock(firstMap->floor[i]->GetWorldPos().y);
					break;
				}
				else if (player[i]->headCol->Intersect(firstMap->floor[i]))
				{
					//���� ����
					if (player[i]->col->GetWorldPos().x < firstMap->floor[i]->GetWorldPos().x)
					{
						// �� scale *0.5 ..�ε�! �� 24�ĸ� �ִϸ��̼� ������ ����
						int wallOn = firstMap->floor[i]->GetWorldPos().x - firstMap->floor[i]->scale.x * 0.5f - 22.0f;

						player[i]->col->SetWorldPosX(wallOn);
						break;
						//player->col->SetWorldPosX(2390.0f);
					}
					//���� ����
					else if (player[i]->col->GetWorldPos().x > firstMap->floor[i]->GetWorldPos().x)
					{
						int wallOn = firstMap->floor[i]->GetWorldPos().x + firstMap->floor[i]->scale.x * 0.5f + 22.0f;

						player[i]->col->SetWorldPosX(wallOn);
						break;
					}
				}
				else
				{
					player[i]->offWall();
					player[i]->offBlock();
				}
			}
			player[i]->Update();
			firstMap->Update();

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
			//SOUND->Stop("button");
			//SOUND->Play("button");
			player->onBlock(firstMap->button->GetWorldPos().y + firstMap->button->scale.y);
		}
		player->Update();
		firstMap->Update();

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
		firstMap->lift->Update();
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
					// �� scale *0.5 ..�ε�! �� 24�ĸ� �ִϸ��̼� ������ ����
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
				//if (firstMap->stair[i]->GetWorldPos().y - 10.0f < player->col->GetWorldPos().y)//(dir.y < 0.0f)
				//{
					//�� OFFSET_T�� �ٲ�
				player->onBlock(firstMap->stair[i]->GetWorldPos().y);
				//}

			}
			else if (player->headCol->Intersect(firstMap->stair[i]))
			{
				//���� ����
				if (player->col->GetWorldPos().x < firstMap->stair[i]->GetWorldPos().x)
				{
					// �� scale *0.5 ..�ε�! �� 24�ĸ� �ִϸ��̼� ������ ����
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
			else if (player->headCol->Intersect(firstMap->floor[i]))
			{
				//���� ����
				if (player->col->GetWorldPos().x < firstMap->floor[i]->GetWorldPos().x)
				{
					// �� scale *0.5 ..�ε�! �� 24�ĸ� �ִϸ��̼� ������ ����
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
				player->offBlock();
			}
		}
		player->Update();
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
	//block->Render();
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
	app.InitWidthHeight(960.0f,540.0f); // �������Ӻ��� (1280.0f,720.0f)
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}