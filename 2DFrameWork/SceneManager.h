#pragma once
class SceneManager :public Singleton<SceneManager>
{
private:
    bool                    isChanging = false;
    Scene *                 nextScene = nullptr;
    Scene *                 currentScene = nullptr;
    map<string, Scene*>    scenes;

public:
    ~SceneManager();

    //¾À Ãß°¡
    bool    AddScene(string key, Scene * value);
    //¾À »èÁ¦
    bool    DeleteScene(string key);
    //¾À º¯°æ
    Scene * ChangeScene(string key);
    //¾À °¡Á®¿À±â
    Scene * GetScene(string key);
    //ÇöÀç ¾À °¡Á®¿À±â
    Scene * GetCurrentScene();

    void    Release();
    void    Update();
    void    LateUpdate();
    void    Render();
    void    ResizeScreen();
};

