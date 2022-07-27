#pragma once
class Shader
{
    ID3D11VertexShader*			vertexShader;
    ID3D11PixelShader*			pixelShader;
    ID3D11InputLayout*			vertexLayout;

public:
    Shader(wstring file);
    ~Shader();
    void Set();
};

