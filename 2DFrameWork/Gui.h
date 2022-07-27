#pragma once
class Gui :public Singleton<Gui>
{
public:
	static LRESULT MsgProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	class GameObject* target;

private:
	UINT fileID;
public:
	Gui();
	~Gui();
	void ResizeScreen();

	void Update();
	void Render();
	bool FileImGui(string button, string name, string fiter, string minPath);
};