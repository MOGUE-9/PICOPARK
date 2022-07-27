#include "framework.h"

Utility::RECT::RECT(Vector2 pivot, Vector2 scale)
{
    min.x = pivot.x - scale.x * 0.5f;
    min.y = pivot.y - scale.y * 0.5f;
    max.x = pivot.x + scale.x * 0.5f;
    max.y = pivot.y + scale.y * 0.5f;
}

Utility::CIRCLE::CIRCLE(Vector2 pivot, Vector2 scale)
{
    this->pivot = pivot;
    radius = scale.x * 0.5f;
}

bool Utility::IntersectRectCoord(RECT & rc, Vector2 coord)
{
    if (rc.min.x < coord.x && coord.x < rc.max.x &&
        rc.min.y < coord.y && coord.y < rc.max.y)
    {
        return true;
    }
    return false;
}

bool Utility::IntersectRectRect(RECT & rc1, RECT & rc2)
{
    if (rc1.min.x < rc2.max.x &&
        rc1.max.x > rc2.min.x &&
        rc1.min.y < rc2.max.y &&
        rc1.max.y > rc2.min.y)
    {
        return true;
    }
    return false;
}

bool Utility::IntersectRectRect(GameObject* ob1, GameObject* ob2)
{
    //중심점
    Vector2 rc1Pivot = ob1->GetWorldPivot();
    Vector2 rc2Pivot = ob2->GetWorldPivot();

    //두 중심점간의 차이 벡터
    Vector2 dis = rc1Pivot - rc2Pivot;

    //사각형마다 2개의 절반크기의 벡터
    Vector2 Rc1Up =
        ob1->GetUp() * ob1->scale.y * 0.5f;
    Vector2 Rc1Right =
        ob1->GetRight() * ob1->scale.x * 0.5f;
    
    Vector2 Rc2Up =
        ob2->GetUp() * ob2->scale.y * 0.5f;
    Vector2 Rc2Right =
        ob2->GetRight() * ob2->scale.x * 0.5f;

    //ob1의 right축 비교
    //       절대값(내적 a . b)
    float c = fabs(dis.Dot(ob1->GetRight()));

    //ob2에서 두벡터가 투영된 길이
    float a = fabs(Rc2Up.Dot(ob1->GetRight()))
        + fabs(Rc2Right.Dot(ob1->GetRight()));

    //ob1에서 두벡터가 투영된 길이
    float b = ob1->scale.x * 0.5f;

    if (c > a + b)return false;

    //ob1의 Up축 비교
    //       절대값(내적 a . b)
    c = fabs(dis.Dot(ob1->GetUp()));

    //ob2에서 두벡터가 투영된 길이
    a = fabs(Rc2Up.Dot(ob1->GetUp()))
        + fabs(Rc2Right.Dot(ob1->GetUp()));
    //ob1에서 두벡터가 투영된 길이
    b = ob1->scale.y * 0.5f;

    if (c > a + b)return false;

    //ob2의 Right축 비교
    //       절대값(내적 a . b)
    c = fabs(dis.Dot(ob2->GetRight()));

    //ob1에서 두벡터가 투영된 길이
    a = fabs(Rc1Up.Dot(ob2->GetRight()))
        + fabs(Rc1Right.Dot(ob2->GetRight()));
    //ob2에서 두벡터가 투영된 길이
    b = ob2->scale.x * 0.5f;

    if (c > a + b)return false;

    //ob2의 Up축 비교
    //       절대값(내적 a . b)
    c = fabs(dis.Dot(ob2->GetUp()));

    //ob1에서 두벡터가 투영된 길이
    a = fabs(Rc1Up.Dot(ob2->GetUp()))
        + fabs(Rc1Right.Dot(ob2->GetUp()));
    //ob2에서 두벡터가 투영된 길이
    b = ob2->scale.y * 0.5f;

    if (c > a + b)return false;

    return true;
}

bool Utility::IntersectRectCircle(RECT & rc, CIRCLE & cc)
{
    Vector2 rectPivot = (rc.min + rc.max) * 0.5f;
    Vector2 RectScale = rc.max - rc.min;

    RECT Wrect(rectPivot, RectScale + Vector2(cc.radius * 2.0f, 0.0f));

    if (IntersectRectCoord(Wrect, cc.pivot))
    {
        return true;
    }

    RECT Hrect(rectPivot, RectScale + Vector2(0.0f, cc.radius * 2.0f));
    if (IntersectRectCoord(Hrect, cc.pivot))
    {
        return true;
    }

    Vector2 edge[4];
    edge[0] = rc.min;
    edge[1] = rc.max;
    edge[2] = Vector2(rc.min.x, rc.max.y);
    edge[3] = Vector2(rc.max.x, rc.min.y);

    for (int i = 0; i < 4; i++)
    {
        if (IntersectCircleCoord(cc, edge[i]))
        {
            return true;
        }
    }

    return false;
}

bool Utility::IntersectRectCircle(GameObject * ob1, GameObject * ob2, COLDIR & result)
{
    Vector2 rectPivot = ob1->GetWorldPivot();
    Vector2 rectScale = ob1->scale;

    RECT Wrect(rectPivot, rectScale + Vector2(ob2->scale.x , 0.0f));

    if (IntersectRectCoord(Wrect, ob2->GetWorldPivot()))
    {
        result = COLDIR::LEFTRIGHT;
        return true;
    }

    RECT Hrect(rectPivot, rectScale + Vector2(0.0f, ob2->scale.x));
    if (IntersectRectCoord(Hrect, ob2->GetWorldPivot()))
    {
        result = COLDIR::UPDOWN;
        return true;
    }

    Vector2 edge[4];
    RECT rc = RECT(ob1->GetWorldPivot(), ob1->scale);
    edge[0] = rc.min;
    edge[1] = rc.max;
    edge[2] = Vector2(rc.min.x, rc.max.y);
    edge[3] = Vector2(rc.max.x, rc.min.y);
    
    CIRCLE cc = CIRCLE(ob2->GetWorldPivot(), ob2->scale);
    for (int i = 0; i < 4; i++)
    {
        if (IntersectCircleCoord(cc, edge[i]))
        {
            result = COLDIR::EDGE;
            return true;
        }
    }
    result = COLDIR::NONE;
    return false;
}

bool Utility::IntersectCircleCoord(CIRCLE & cc, Vector2 coord)
{
    Vector2 Distance = cc.pivot - coord;
    if (Distance.Length() < cc.radius)
    {
        return true;
    }
    return false;
}

bool Utility::IntersectCircleCircle(CIRCLE & cc1, CIRCLE & cc2)
{
    Vector2 distance = cc1.pivot - cc2.pivot;
    if (distance.Length() < cc1.radius + cc2.radius)
    {
        return true;
    }

    return false;
}

float Utility::DirToRadian(Vector2 Dir)
{
    //만약 단위벡터가 아니라면
    Dir.Normalize();
    return atan2f(Dir.y, Dir.x);
}
