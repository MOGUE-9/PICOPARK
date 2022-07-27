#pragma once
//Popup Console
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 

//C
#include <Windows.h>
#include <assert.h>

//C++
#include <string>
#include <vector>
#include <deque>
#include <chrono>
#include <random>
#include <iostream>
using namespace std;

//DirectX d3d 11
#include <d3d11.h>
#include <dxgi1_2.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")

//DirectXTk 
#include "../Libs/DirectXTK/SimpleMath.h"
using namespace DirectX;
using namespace SimpleMath;

//DirectXTex
#include "../Libs/DirectXTex/DirectXTex.h"
#pragma comment(lib, "../Libs/DirectXTex/DirectXTex.lib")

//Fmod
#include "../Libs/Fmod/fmod.hpp"
#pragma comment(lib, "../Libs/Fmod/fmodL_vc.lib")

//Imgui
#include "../Libs/ImGui/imgui.h"
#include "../Libs/ImGui/imgui_internal.h"
#include "../Libs/ImGui/imgui_impl_dx11.h"
#include "../Libs/ImGui/imgui_impl_win32.h"
#pragma comment(lib, "../Libs/ImGui/ImGui.lib")

//Dialog
#include "../Libs/ImGui/dirent.h"
#include "../Libs/ImGui/ImGuiFileDialog.h"
#include "../Libs/ImGui/ImGuiFileDialogConfig.h"

//Macro(Pascal)
#define Check(hr)			{ assert(SUCCEEDED(hr)); }
#define SafeRelease(p)		{ if(p){ (p)->Release(); (p) = nullptr; } }
#define SafeDelete(p)		{ if(p){ delete (p); (p) = nullptr; } }
#define SafeDeleteArray(p)	{ if(p){ delete[] (p); (p) = nullptr; } }
#define	ToRadian			0.0174532f
//Macro(WINAPI Style)
#define	PI					3.1415926f	//180
#define	DIV2PI				1.5707963f	//90
#define	DIV4PI				0.7853981f	//45
#define	UP					Vector2(0.0f,1.0f)
#define	DOWN				Vector2(0.0f,-1.0f)
#define	LEFT				Vector2(-1.0f,0.0f)
#define	RIGHT				Vector2(1.0f,0.0f)
#define OFFSET_N            Vector2(0.0f, 0.0f)
#define OFFSET_L            Vector2(0.5f, 0.0f)
#define OFFSET_R            Vector2(-0.5f, 0.0f)
#define OFFSET_B            Vector2(0.0f, 0.5f)
#define OFFSET_T            Vector2(0.0f, -0.5f)
#define OFFSET_LB           Vector2(0.5f, 0.5f)
#define OFFSET_RB           Vector2(-0.5f, 0.5f)
#define OFFSET_LT           Vector2(0.5f, -0.5f)
#define OFFSET_RT           Vector2(-0.5f, -0.5f)

//2DFramework Header
#include "Types.h"
#include "Window.h"
extern Application app;//Extern Global
#include "Direct3D11.h"
#include "Gui.h"
#include "Input.h"
#include "Timer.h"
#include "Camara.h"
#include "Random.h"
#include "Texture.h"
#include "Sound.h"
#include "Light.h"
#include "SceneManager.h"

#include "VertexType.h"
#include "Shader.h"
#include "GameObject.h"
#include "Utility.h"
#include "ObRect.h"
#include "ObStar.h"
#include "ObCircle.h"
#include "ObLine.h"
#include "ObImage.h"

//Singleton Macro
#define	D3D			Direct3D11::GetInstance()
#define	WIN			Window::GetInstance()
#define	GUI			Gui::GetInstance()
#define CAM         Camera::GetInstance()
#define INPUT		Input::GetInstance()
#define TIMER		Timer::GetInstance()
#define DELTA		Timer::GetInstance()->GetDeltaTime()
#define RANDOM		Random::GetInstance()
#define TEXTURE		Texture::GetInstance()
#define SOUND		Sound::GetInstance()
#define LIGHT		Light::GetInstance()
#define SCENE       SceneManager::GetInstance()