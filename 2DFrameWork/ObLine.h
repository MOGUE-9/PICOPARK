#pragma once
//¼±
class ObLine : public GameObject
{
private:
    static ID3D11Buffer* vertexBuffer;

public:
    static void CreateStaticMember();
    static void DeleteStaticMember();

public:
    ObLine();
    void Render();
  
};


