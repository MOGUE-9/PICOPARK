#include "Framework.h"

Application	 app;
Scene* Window::main = nullptr;

WPARAM Window::Run(Scene* main)
{
	Window::main = main;
	//Window->D3D->main
	Create(); 
	D3D->Create();
	GameObject::CreateStaticMember();
	ObRect::CreateStaticMember();
	ObLine::CreateStaticMember();
	ObCircle::CreateStaticMember();
	ObStar::CreateStaticMember();
	ObImage::CreateStaticMember();
	main->Init();
	MSG msg = { 0 };
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			TIMER->Chronometry(app.fixFrame);
			INPUT->Update();
			SOUND->Update();
			GUI->Update();
			main->Update();
			main->LateUpdate();
			CAM->Set();
			LIGHT->Set();
			D3D->SetRenderTarget();
			D3D->Clear(app.background);
			{
				main->Render();
				GUI->Render();
			}
			D3D->Present();
		}
	}
	Save();
	GameObject::DeleteStaticMember();
	ObRect::DeleteStaticMember();
	ObLine::DeleteStaticMember();
	ObCircle::DeleteStaticMember();
	ObStar::DeleteStaticMember();
	ObImage::DeleteStaticMember();

	main->Release();
	TIMER->DeleteSingleton();
	INPUT->DeleteSingleton();
	GUI->DeleteSingleton();
	CAM->DeleteSingleton();
	RANDOM->DeleteSingleton();
	SOUND->DeleteSingleton();
	TEXTURE->DeleteSingleton();
	LIGHT->DeleteSingleton();
	SCENE->DeleteSingleton();
	D3D->DeleteSingleton();
	Destroy();

	return msg.wParam;
}

void Window::Create()
{
	WNDCLASSEXW wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hIconSm = wndClass.hIcon;
	wndClass.hInstance = app.instance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = app.appName.c_str();
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEX);

	WORD wHr = RegisterClassExW(&wndClass);
	assert(wHr != 0);

	if (app.fullScreen == true)
	{
		DEVMODE devMode = { 0 };
		devMode.dmSize = sizeof(DEVMODE);
		devMode.dmPelsWidth = (DWORD)app.GetWidth();
		devMode.dmPelsHeight = (DWORD)app.GetHeight();
		devMode.dmBitsPerPel = 32;
		devMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
	}
	app.handle = CreateWindowExW
	(
		WS_EX_APPWINDOW
		, app.appName.c_str()
		, app.appName.c_str()
		, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, NULL
		, (HMENU)NULL
		, app.instance
		, NULL
	);
	assert(app.handle != NULL);

	ShowWindow(app.handle, SW_SHOWNORMAL);
	SetForegroundWindow(app.handle);
	SetFocus(app.handle);

	ShowCursor(true);
	Load();
}


void Window::Load()
{
	ifstream fin;
	string file = "window.ini";
	fin.open(file.c_str(), ios::in);
	string temp;
	if (fin.is_open())
	{
		string temp;
		fin >> temp >> app.x >> app.y;
		fin.close();
	}

	RECT rect = { 0, 0, (LONG)app.GetWidth(), (LONG)app.GetHeight() };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	MoveWindow
	(
		app.handle
		, (LONG)app.x, (LONG)app.y
		, rect.right - rect.left, rect.bottom - rect.top
		, TRUE
	);
}

void Window::Save()
{
	RECT rc;
	GetWindowRect(app.handle, &rc);
	app.x = (float)rc.left;
	app.y = (float)rc.top;
	ofstream fout;
	string file = "window.ini";
	fout.open(file.c_str(), ios::out);
	if (fout.is_open())
	{
		fout << "Pos " << app.x << " " << app.y << endl;
		fout.close();
	}
}



void Window::Destroy()
{

	if (app.fullScreen == true)
		ChangeDisplaySettings(NULL, 0);

	DestroyWindow(app.handle);

	UnregisterClass(app.appName.c_str(), app.instance);
}


LRESULT Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (Gui::MsgProc(handle, message, wParam, lParam))
		return true;

	if (message == WM_MOUSEMOVE)
	{
		INPUT->mouseScreenPos.x = (float)LOWORD(lParam);
		INPUT->mouseScreenPos.y = (float)HIWORD(lParam);
	}

	if (message == WM_SIZE)
	{
		if (D3D->GetCreated())
		{
			float width = (float)LOWORD(lParam);
			float height = (float)HIWORD(lParam);
			D3D->ResizeScreen(width, height);
			CAM->ResizeScreen();
			GUI->ResizeScreen();
			if (main)
				main->ResizeScreen();
		}
	}

	if (message == WM_CLOSE || message == WM_DESTROY)
	{
		PostQuitMessage(0);

		return 0;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}

