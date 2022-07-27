#pragma once
class ObStar : public GameObject
{
private:
    static ID3D11Buffer * fillVertexBuffer;
    static ID3D11Buffer * vertexBuffer;

public:
    static void CreateStaticMember();
    static void DeleteStaticMember();

public:
    void Render()override;
};

