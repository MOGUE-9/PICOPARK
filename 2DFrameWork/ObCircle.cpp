#include "framework.h"
ID3D11Buffer* ObCircle::fillVertexBuffer = nullptr;
ID3D11Buffer* ObCircle::vertexBuffer = nullptr;

void ObCircle::CreateStaticMember()
{
    VertexPC* Vertex;
    Vertex = new VertexPC[360 * 3];

    Color col1 = Color(0.0f, 0.0f, 0.0f, 1.0f);

    for (UINT i = 0; i < 360; i++)
    {
        Vertex[i * 3].position.x = 0.0f;
        Vertex[i * 3].position.y = 0.0f;
        Vertex[i * 3].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

        //0 1 2 ... 359
        Vertex[i * 3 + 1].position.x = cosf(i * ToRadian) * 0.5f;
        Vertex[i * 3 + 1].position.y = sinf(i * ToRadian) * 0.5f;
        Vertex[i * 3 + 1].color = Color(0.0f, 0.0f, 0.0f, 1.0f);
        //Vertex[i * 3 + 1].color = Color(RANDOM->Float(), RANDOM->Float(), RANDOM->Float(), 1.0f);

        //1 2 3 .. 360
        Vertex[i * 3 + 2].position.x = cosf((i + 1) * ToRadian) * 0.5f;
        Vertex[i * 3 + 2].position.y = sinf((i + 1) * ToRadian) * 0.5f;
        Vertex[i * 3 + 2].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

        //컬러
        //r -> g
        //if (i < 120)
        //{
        //    float color1 = i / 120.0f;
        //    float color2 = (i + 1) / 120.0f;

        //    Vertex[i * 3 + 1].color = Color(1.0f - color1, color1, 0.0f, 1.0f);
        //    Vertex[i * 3 + 2].color = Color(1.0f - color2, color2, 0.0f, 1.0f);
        //}
        ////g -> b
        //else if (i < 240)
        //{
        //    float color1 = (i - 120) / 120.0f;
        //    float color2 = (i - 120 + 1) / 120.0f;

        //    Vertex[i * 3 + 1].color = Color(0.0f, 1.0f - color1, color1, 1.0f);
        //    Vertex[i * 3 + 2].color = Color(0.0f, 1.0f - color2, color2, 1.0f);
        //}
        ////b -> r
        //else
        //{
        //    float color1 = (i - 240) / 120.0f;
        //    float color2 = (i - 240 + 1) / 120.0f;

        //    Vertex[i * 3 + 1].color = Color(color1, 0.0f, 1.0f - color1, 1.0f);
        //    Vertex[i * 3 + 2].color = Color(color2, 0.0f, 1.0f - color2, 1.0f);
        //}
    }
    //정점들이 버퍼로 옮겨지는 코드
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 }; //멤버변수 전부 0으로
        desc.Usage = D3D11_USAGE_DEFAULT;//버퍼를 읽고 쓰는 방법
        desc.ByteWidth = sizeof(VertexPC) * 360 * 3; //버퍼 크기 (바이트)입니다.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//버퍼가 파이프 라인에 바인딩되는 방법을 식별하십시오

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //하위 리소스를 초기화하기위한 데이터를 지정합니다.
        data.pSysMem = Vertex;
        //초기화 데이터의 포인터.

        //버퍼 만들기
        //                                           서술    원본       복사대상   
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &fillVertexBuffer);
        assert(SUCCEEDED(hr));

    }

    delete[] Vertex;

    Vertex = new VertexPC[361];

    //두가지 랜덤한 색 만들기
    for (UINT i = 0; i < 361; i++)
    {
        Vertex[i].color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        Vertex[i].position.x = cosf(i * ToRadian) * 0.5f;
        Vertex[i].position.y = sinf(i * ToRadian) * 0.5f;
    }


    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//버퍼를 읽고 쓰는 방법
        desc.ByteWidth = sizeof(VertexPC) * 361; //버퍼 크기 (바이트)입니다.
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

void ObCircle::DeleteStaticMember()
{
    vertexBuffer->Release();
    fillVertexBuffer->Release();
}

ObCircle::ObCircle()
{
    collider = COLLIDER::CIRCLE;
}

void ObCircle::Render()
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
        D3D->GetDC()->Draw(360 * 3, 0);
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
        D3D->GetDC()->Draw(361, 0);
    }
}

