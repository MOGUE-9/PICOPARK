#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	//룰
	block = new ObRect();
	block->collider = COLLIDER::RECT;
	block->pivot = OFFSET_T;
	block->SetWorldPosY(-50.0f);
	block->color = Color(1.0f, 1.0f, 0.0f, 1.0f);
	block->scale = Vector2(1000.0f, 50.0f);

	player = new PicoCat();
}

void Main::Release()
{

}

void Main::Update()
{
	//ImGuiColorEditFlags
	ImGui::ColorEdit4("d", (float*)&block->color, ImGuiColorEditFlags_PickerHueWheel);

	block->Update();
	player->Update();

	cout << block->GetWorldPos().y << endl;
	cout << player->col->GetWorldPos().y << endl;

}

void Main::LateUpdate()
{
	if (player->col->Intersect(block))
	{
		player->onBlock(block->GetWorldPos().y);

	
		//블럭 밟고 있을 때 돌려줄 값 :: 계속 블럭의 윗쪽에 고정되어 있어야 함

		//if (player->col->GetWorldPos().y < block->GetWorldPos().y)
		//{
		//	player->col->SetWorldPosY(-50.0f);
		//}
	}

	//if (!block->Intersect(player->col->GetWorldPivot()))
	//{
	//	player->offBlock();
	//}

	player->Update();

}

void Main::Render()
{
	block->Render();
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