#include "framework.h"

ID3D11Buffer* ObStar::fillVertexBuffer = nullptr;
ID3D11Buffer* ObStar::vertexBuffer = nullptr;

void ObStar::CreateStaticMember()
{
    VertexPC* Vertex;
    Vertex = new VertexPC[5 * 3];

    Color col1 = Color(0.0f, 0.0f, 0.0f, 1.0f);

    //삼각형의 배수만큼 돌아라
    for (UINT i = 0; i < 5; i++)
    {
        // 0 : 0,1,2
        // 1 : 3,4,5

        Vertex[i * 3].position.x = 0.0f;
        Vertex[i * 3].position.y = 0.0f;

        Vertex[i * 3 + 1].position.x = cosf(i * 144 * ToRadian) * 0.5f;
        Vertex[i * 3 + 1].position.y = sinf(i * 144 * ToRadian) * 0.5f;

        //1,2,3... 360
        Vertex[i * 3 + 2].position.x = cosf((i + 1) * 144 * ToRadian) * 0.5f;
        Vertex[i * 3 + 2].position.y = sinf((i + 1) * 144 * ToRadian) * 0.5f;

        Vertex[i * 3].color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        Vertex[i * 3 + 1].color = Color(0.0f, 0.0f, 0.0f, 1.0f);
        Vertex[i * 3 + 2].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    }
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };//모든멤버를 0으로 초기화
        desc.Usage = D3D11_USAGE_DEFAULT;//버퍼를 읽고 쓰는 방법
        //                     정점크기 *삼각형갯수* 3
        desc.ByteWidth = sizeof(VertexPC) * 5 * 3; //버퍼 크기 (바이트)입니다.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//버퍼가 파이프 라인에 바인딩되는 방법을 식별하십시오

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //하위 리소스를 초기화하기위한 데이터를 지정합니다.
        data.pSysMem = Vertex;
        //초기화 데이터의 포인터.

        //버퍼 만들기
        //                                          서술 , src  , dest
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &fillVertexBuffer);

        assert(SUCCEEDED(hr));

    }

    delete[] Vertex;

    Vertex = new VertexPC[6];

    //두가지 랜덤한 색 만들기
    for (UINT i = 0; i < 6; i++)
    {
        Vertex[i].color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        Vertex[i].position.x = cosf(i * 144 * ToRadian) * 0.5f;
        Vertex[i].position.y = sinf(i * 144 * ToRadian) * 0.5f;
    }

    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//버퍼를 읽고 쓰는 방법
        desc.ByteWidth = sizeof(VertexPC) * 6; //버퍼 크기 (바이트)입니다.
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

void ObStar::DeleteStaticMember()
{
    vertexBuffer->Release();
    fillVertexBuffer->Release();
}

void ObStar::Render()
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
        D3D->GetDC()->IASetPrimitiveTopology
        (D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        D3D->GetDC()->Draw(5 * 3, 0);
    }
    else
    {
        D3D->GetDC()->IASetVertexBuffers(0,//입력슬롯(16~32개까지 설정가능)
            1,//입력슬롯에 붙이고자 하는 버퍼의 갯수
            &vertexBuffer,
            &stride,//정점버퍼의 한 원소의 바이트단위 크기
            &offset);
        D3D->GetDC()->IASetPrimitiveTopology
        (D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
        D3D->GetDC()->Draw(6, 0);
    }
}

