#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	titleMap = new Title();
	firstMap = new Map1();

	player = new PicoCat();
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
		CAM->position += RIGHT * 200.0f * DELTA;
	}


	player->Update();

	titleMap->Update();
	firstMap->Update();
}

void Main::LateUpdate()
{
	if (stage==STAGE::TITLE)
	{
		//�÷��̾ �ٴ��� UP���⿡ ���� ���� �浹 :: 
		// �翷���� �ε����� �¿� ��ġ�� �����ǰ��ϱ� -> Title cpp����?
		if (true)
		{

		}
		//�ٴڰ� �浹���� ���� ��� ���� �ֱ�
		if (player->col->Intersect(titleMap->floor))
		{
			player->onBlock(titleMap->floor->GetWorldPos().y);
		}
		else player->offBlock();
		//�׳� ������
		if (player->col->Intersect(titleMap->door))
		{
			if (INPUT->KeyDown(VK_DOWN))
			{
				titleMap->openDoor();
			}
		}
		//�������� �̵�
		else if (player->col->Intersect(titleMap->doorOP))
		{
			if (INPUT->KeyDown(VK_DOWN))
			{
				titleMap->stageClose();
				stage = STAGE::ST_1;
			}
		}
		player->Update();

		titleMap->Update();

	}
	else if (stage == STAGE::ST_1)
	{
		for (int i = 0; i < 2; i++)
		{
			//�� �浹
			if (player->col->Intersect(firstMap->wall[i]))
			{

			}
		}

		for (int i = 0; i < 3; i++)
		{
			//����浹
			if (player->col->Intersect(firstMap->stair[i]))
			{
				player->onBlock(firstMap->stair[i]->GetWorldPos().y);
				break;
			}
			//�ٴ��浹
			else if (player->col->Intersect(firstMap->floor[i]))
			{
				cout << "floor" << endl;
				player->onBlock(firstMap->floor[i]->GetWorldPos().y);
				break;
			}
			else player->offBlock();
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
	app.InitWidthHeight(960.0f,540.0f); // �������Ӻ��� (1280.0f,720.0f)
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}