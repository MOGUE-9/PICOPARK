#include "framework.h"

Camera::Camera()
{
    //첫 카메라 위치
    position.x = 0.0f;
    position.y = 0.0f;
    //뷰포트
    viewport.width = app.GetWidth();
    viewport.height = app.GetHeight();
    D3D->GetDC()->RSSetViewports(1, viewport.Get11());
}

void Camera::Set()
{
    //뷰행렬 -> 역이동행렬
    V = Matrix::CreateTranslation(-position.x, -position.y, 0.0f);
    //프로젝션 -> 투영행렬
    P = Matrix::CreateOrthographic(app.GetWidth(), app.GetHeight(), 0.0f, 10.0f);

    VP = V * P;
}

void Camera::ResizeScreen()
{
    /*viewport.x = 200.0f;
    viewport.y = 200.0f;*/

    viewport.width = app.GetWidth();
    viewport.height = app.GetHeight();
    D3D->GetDC()->RSSetViewports(1, viewport.Get11());
}
