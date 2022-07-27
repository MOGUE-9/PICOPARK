#include "framework.h"

ID3D11Buffer* ObImage::vertexBuffer = nullptr;
ID3D11Buffer* ObImage::uvBuffer = nullptr;

void ObImage::CreateStaticMember()
{
    VertexPT* Vertex;

    Vertex = new VertexPT[4];
    //VertexCount = 4;
    //시계방향으로 정점찍기
    Vertex[0].position.x = -0.5f;
    Vertex[0].position.y = -0.5f;
    Vertex[0].uv = Vector2(0.0f, 1.0f);

    Vertex[1].position.x = -0.5f;
    Vertex[1].position.y = 0.5f;
    Vertex[1].uv = Vector2(0.0f, 0.0f);

    Vertex[2].position.x = 0.5f;
    Vertex[2].position.y = -0.5f;
    Vertex[2].uv = Vector2(1.0f, 1.0f);

    Vertex[3].position.x = 0.5f;
    Vertex[3].position.y = 0.5f;
    Vertex[3].uv = Vector2(1.0f, 0.0f);

    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//버퍼를 읽고 쓰는 방법
        desc.ByteWidth = sizeof(VertexPT) * 4; //버퍼 크기 (바이트)입니다.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//버퍼가 파이프 라인에 바인딩되는 방법을 식별하십시오

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //하위 리소스를 초기화하기위한 데이터를 지정합니다.
        data.pSysMem = Vertex;
        //초기화 데이터의 포인터.

        //버퍼 만들기
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
        assert(SUCCEEDED(hr));
    }

    delete[] Vertex;
    //CreateConstantBuffer
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.ByteWidth = sizeof(Vector4);
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &uvBuffer);
        assert(SUCCEEDED(hr));
    }
    D3D->GetDC()->VSSetConstantBuffers(2, 1, &uvBuffer);
}

void ObImage::DeleteStaticMember()
{
    vertexBuffer->Release();
    uvBuffer->Release();
}

void ObImage::PlayAnim()
{
    if (maxFrame.x == 1 && maxFrame.y == 1)
        return;

    if (animState != ANIMSTATE::STOP)
    {
        if (TIMER->GetTick(animTime, animInterval))
        {
            //재생간격이 지났을 때
            if (animXAxis) //가로재생
            {
                if (animState == ANIMSTATE::LOOP)
                {
                    frame.x++;
                    if (frame.x == maxFrame.x)
                    {
                        frame.x = 0;
                    }
                }
                else if (animState == ANIMSTATE::ONCE)
                {
                    frame.x++;
                    if (frame.x == maxFrame.x)
                    {
                        frame.x = maxFrame.x - 1;
                        animState = ANIMSTATE::STOP;
                    }
                }
                else if (animState == ANIMSTATE::REVERSE_LOOP)
                {
                    frame.x--;
                    if (frame.x == -1)
                    {
                        frame.x = maxFrame.x - 1;
                    }
                }
                else //REVERSE_ONCE
                {
                    frame.x--;
                    if (frame.x == -1)
                    {
                        frame.x = 0;
                        animState = ANIMSTATE::STOP;
                    }
                }
            }
            else //세로재생
            {
                if (animState == ANIMSTATE::LOOP)
                {
                    frame.y++;
                    if (frame.y == maxFrame.y)
                    {
                        frame.y = 0;
                    }
                }
                else if (animState == ANIMSTATE::ONCE)
                {
                    frame.y++;
                    if (frame.y == maxFrame.y)
                    {
                        frame.y = maxFrame.y - 1;
                        animState = ANIMSTATE::STOP;
                    }
                }
                else if (animState == ANIMSTATE::REVERSE_LOOP)
                {
                    frame.y--;
                    if (frame.y == -1)
                    {
                        frame.y = maxFrame.y - 1;
                    }
                }
                else //REVERSE_ONCE
                {
                    frame.y--;
                    if (frame.y == -1)
                    {
                        frame.y = 0;
                        animState = ANIMSTATE::STOP;
                    }
                }
            }
        }
    }

    if (maxFrame.x != 1)
    {
        uv.x = frame.x / (float)maxFrame.x;
        uv.z = (frame.x + 1.0f) / (float)maxFrame.x;
    }
    if (maxFrame.y != 1)
    {
        uv.y = frame.y / (float)maxFrame.y;
        uv.w = (frame.y + 1.0f) / (float)maxFrame.y;
    }
}

ObImage::ObImage(wstring file)
{
    //기본 샘플러 값
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;

    samplerDesc.MipLODBias = 0.0f;
    samplerDesc.MaxAnisotropy = 1;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    samplerDesc.MinLOD = -FLT_MAX;
    samplerDesc.MaxLOD = FLT_MAX;

    //하나 이상의 샘플러 만들어 두기
    D3D->GetDevice()->CreateSamplerState(&samplerDesc, &sampler);

    //텍스쳐 로드
    SRV = TEXTURE->LoadTexture(file);

    //           (최소좌표)   (최대좌표)
    uv = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
    animTime = 0.0f;
    animInterval = 0.0f;
    animXAxis = true;
    maxFrame = Int2(1, 1);
    frame = Int2(0, 0);
    reverseLR = false;
}

ObImage::~ObImage()
{
    sampler->Release();
}

void ObImage::Render()
{
    if (!visible)return;

    PlayAnim();
    GameObject::Render();

    imageShader->Set();

    if (reverseLR)
    {
        Vector4 reUv = Vector4(uv.z, uv.y, uv.x, uv.w);
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        D3D->GetDC()->Map(uvBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        memcpy_s(mappedResource.pData, sizeof(Vector4), &reUv, sizeof(Vector4));
        D3D->GetDC()->Unmap(uvBuffer, 0);
    }
    else
    {
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        D3D->GetDC()->Map(uvBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        memcpy_s(mappedResource.pData, sizeof(Vector4), &uv, sizeof(Vector4));
        D3D->GetDC()->Unmap(uvBuffer, 0);
    }

    UINT stride = sizeof(VertexPT);
    UINT offset = 0;

    D3D->GetDC()->PSSetShaderResources(0, 1, &SRV);
    D3D->GetDC()->PSSetSamplers(0, 1, &sampler);
    D3D->GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    D3D->GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    D3D->GetDC()->Draw(4, 0);
}

void ObImage::ChangeAnim(ANIMSTATE anim, float interval, bool xAxis)
{
    animState = anim;
    animInterval = interval;
    animXAxis = xAxis;

    if (animState == ANIMSTATE::ONCE)
    {
        if (xAxis)
            frame.x = 0;
        else
            frame.y = 0;
    }
    else if (animState == ANIMSTATE::REVERSE_ONCE)
    {
        if (xAxis)
            frame.x = maxFrame.x - 1;
        else
            frame.y = maxFrame.y - 1;
    }
    
}

void ObImage::ChangeSampler(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE addressU, D3D11_TEXTURE_ADDRESS_MODE addressV)
{
    SafeRelease(sampler);
    samplerDesc.Filter = filter;
    samplerDesc.AddressU = addressU;
    samplerDesc.AddressV = addressV;
    D3D->GetDevice()->CreateSamplerState(&samplerDesc, &sampler);
}
