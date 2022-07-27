#pragma once
class Light : public Singleton<Light>
{
private:
    struct PointLight
    {
        Vector2 screenPos;      //스크린좌표  //8
        float   radius;         //반지름크기  //12
        float   select;         //조명 선택    //16
        Color   lightColor;     //조명 색     // 16 + 16
        Color   outColor;       //조명 밖 색
    };
    ID3D11Buffer * lightBuffer;

public:
    PointLight light;

    Light();
    ~Light();

    void        Set();
    void        SetLightPos(Vector2 WPos);
};

