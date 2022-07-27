#include "framework.h"

Shader::Shader(wstring file)
{
    ID3D10Blob*					VsBlob;
    ID3D10Blob*					PsBlob;

    wstring path = L"../Shaders/" + file + L".hlsl";

    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "VS", "vs_5_0", flags, 0, &VsBlob, nullptr);

    D3D->GetDevice()->CreateVertexShader(VsBlob->GetBufferPointer(), VsBlob->GetBufferSize(),
        nullptr, &vertexShader);

    D3D11_INPUT_ELEMENT_DESC LayoutDesc[2];

    LayoutDesc[0] = { "POSITION",//시멘틱에서 정의한 자료형
    0,//시멘틱에서 정의한 인덱스 0으로 지정했기에 0 사용
    DXGI_FORMAT_R32G32B32_FLOAT,//3개의 32비트 float설정
    0,//0~15사이의 인덱스 지정, 동시에 15개까지 버퍼가 입력슬롯을 가질수있다.
    0,//이 요소가 메모리덩어리 시작지점부터 얼마나 떨어진 위치에 있는가를 알려준다.처음시작0
    D3D11_INPUT_PER_VERTEX_DATA,//넘어가기
    0 };

    if (file == L"1.Basic")
    {
        LayoutDesc[1] = 
        { "COLOR",//시멘틱에서 정의한 자료형
        0,//시멘틱에서 정의한 인덱스 0으로 지정했기에 0 사용
        DXGI_FORMAT_R32G32B32_FLOAT,//3개의 32비트 float설정
        0,//0~15사이의 인덱스 지정, 동시에 15개까지 버퍼가 입력슬롯을 가질수있다.
        12,//포지션 R32G32B32 4 ,4,4 ->12 기준 
        D3D11_INPUT_PER_VERTEX_DATA,//넘어가기
        0 };
    }

    else if (file == L"2.Image")
    {
        LayoutDesc[1] = 
        { "UV",//시멘틱에서 정의한 자료형
        0,//시멘틱에서 정의한 인덱스 0으로 지정했기에 0 사용
        DXGI_FORMAT_R32G32_FLOAT,//2개의 32비트 float설정
        0,//0~15사이의 인덱스 지정, 동시에 15개까지 버퍼가 입력슬롯을 가질수있다.
        12,//포지션 R32G32B32 4 ,4,4 ->12 기준 
        D3D11_INPUT_PER_VERTEX_DATA,//넘어가기
        0 };
    }

    D3D->GetDevice()->CreateInputLayout
    (
        LayoutDesc,//정점구조체배열
        2,//배열원소갯수
        VsBlob->GetBufferPointer(),//정점셰이더 포인터
        VsBlob->GetBufferSize(),//셰이더크기
        &vertexLayout//입력배치를 포인터를 통해 돌려줌
    );

    VsBlob->Release();

    D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "PS", "ps_5_0", flags, 0, &PsBlob, nullptr);

    D3D->GetDevice()->CreatePixelShader(PsBlob->GetBufferPointer(), PsBlob->GetBufferSize(),
        nullptr, &pixelShader);

    PsBlob->Release();
}

Shader::~Shader()
{
    vertexShader->Release();
    pixelShader->Release();
    vertexLayout->Release();
}

void Shader::Set()
{
    //파이프라인에 바인딩
    D3D->GetDC()->VSSetShader(vertexShader, 0,  0);
    D3D->GetDC()->PSSetShader(pixelShader, 0, 0);
    D3D->GetDC()->IASetInputLayout(vertexLayout);
}
