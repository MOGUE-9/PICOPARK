#include "framework.h"

ID3D11Buffer* ObRect::fillVertexBuffer = nullptr;
ID3D11Buffer* ObRect::vertexBuffer = nullptr;

void ObRect::CreateStaticMember()
{
    VertexPC* Vertex;

    Vertex = new VertexPC[4];
    //VertexCount = 4;
    //시계방향으로 정점찍기
    Vertex[0].position.x = -0.5f;
    Vertex[0].position.y = -0.5f;
    //빨간색
    Vertex[0].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    Vertex[1].position.x = -0.5f;
    Vertex[1].position.y = 0.5f;
    //빨간색
    Vertex[1].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    Vertex[2].position.x = 0.5f;
    Vertex[2].position.y = -0.5f;
    //파란색
    Vertex[2].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    Vertex[3].position.x = 0.5f;
    Vertex[3].position.y = 0.5f;
    //파란색
    Vertex[3].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//버퍼를 읽고 쓰는 방법
        desc.ByteWidth = sizeof(VertexPC) * 4; //버퍼 크기 (바이트)입니다.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//버퍼가 파이프 라인에 바인딩되는 방법을 식별하십시오

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //하위 리소스를 초기화하기위한 데이터를 지정합니다.
        data.pSysMem = Vertex;
        //초기화 데이터의 포인터.

        //버퍼 만들기
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &fillVertexBuffer);
        assert(SUCCEEDED(hr));
    }

    delete[] Vertex;

    Vertex = new VertexPC[5];
    //VertexCount = 5;
    Vertex[0].position.x = -0.5f;
    Vertex[0].position.y = -0.5f;
    Vertex[0].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    Vertex[1].position.x = -0.5f;
    Vertex[1].position.y = 0.5f;
    Vertex[1].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    Vertex[2].position.x = 0.5f;
    Vertex[2].position.y = 0.5f;
    Vertex[2].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    Vertex[3].position.x = 0.5f;
    Vertex[3].position.y = -0.5f;
    Vertex[3].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    Vertex[4].position.x = -0.5f;
    Vertex[4].position.y = -0.5f;
    Vertex[4].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//버퍼를 읽고 쓰는 방법
        desc.ByteWidth = sizeof(VertexPC) * 5; //버퍼 크기 (바이트)입니다.
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
}

void ObRect::DeleteStaticMember()
{
    vertexBuffer->Release();
    fillVertexBuffer->Release();
}

ObRect::ObRect()
{
    collider = COLLIDER::RECT;
}

void ObRect::Render()
{
    if (!visible)return;
    GameObject::Render();

    basicShader->Set();

    UINT stride = sizeof(VertexPC);
    UINT offset = 0;

   
    if (isFilled)
    {
        D3D->GetDC()->IASetVertexBuffers(0,
            1,
            &fillVertexBuffer,
            &stride,
            &offset);
        D3D->GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
        D3D->GetDC()->Draw(4, 0);
    }
    else
    {
        D3D->GetDC()->IASetVertexBuffers(0,//입력슬롯(16~32개까지 설정가능)
            1,//입력슬롯에 붙이고자 하는 버퍼의 갯수
            &vertexBuffer,
            &stride,//정점버퍼의 한 원소의 바이트단위 크기
            &offset);
        D3D->GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
        D3D->GetDC()->Draw(5, 0);
    }
}

