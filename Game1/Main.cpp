#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	block = new ObRect();
	block->scale = Vector2(50.0f, 50.0f);

	player = new PicoCat();
}

void Main::Release()
{

}

void Main::Update()
{
	block->Update();
	player->Update();

}

void Main::LateUpdate()
{
	
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
	app.InitWidthHeight(1400,800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}