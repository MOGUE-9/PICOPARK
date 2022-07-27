#include "framework.h"

SceneManager::~SceneManager()
{
    for (auto i = scenes.begin();
        i != scenes.end(); i++)
    {
        SafeDelete(i->second);
    }
    scenes.clear();
}

bool SceneManager::AddScene(string key, Scene * value)
{
    auto iter = scenes.find(key);

    if (iter != scenes.end())
    {
        return false;
    }
    scenes[key] = value;

    return true;
}

bool SceneManager::DeleteScene(string key)
{
    auto iter = scenes.find(key);

    if (iter == scenes.end())
    {
        return false;
    }

    SafeDelete(iter->second);
    scenes.erase(iter);

    return true;
}

Scene * SceneManager::ChangeScene(string key)
{
    Scene * temp = GetScene(key);

    if (temp)
    {
        nextScene = temp;
        isChanging = true;
        //¾À ºÒ·¯¿Ã ¶§ 
        SafeRelease(currentScene);
        //¾À ¹Ù²ð ¶§
        nextScene->Init();
    }
    return temp;
}

Scene * SceneManager::GetScene(string key)
{
    auto iter = scenes.find(key);

    if (iter == scenes.end())
    {
        return nullptr;
    }

    return iter->second;
}

Scene * SceneManager::GetCurrentScene()
{
    return currentScene;
}

void SceneManager::Release()
{
    if (currentScene)currentScene->Release();
}

void SceneManager::Update()
{
    if (isChanging)
    {
        currentScene = nextScene;
        isChanging = false;
    }
    currentScene->Update();
}

void SceneManager::LateUpdate()
{
    if (isChanging)return;
    currentScene->LateUpdate();
}

void SceneManager::Render()
{
    if (isChanging)return;
    currentScene->Render();
}

void SceneManager::ResizeScreen()
{
    if (isChanging || !currentScene)return;
    currentScene->ResizeScreen();
}
