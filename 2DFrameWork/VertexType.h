#pragma once

struct VertexPC
{
    Vector3 position;
    Color   color;

    VertexPC() { position.z = 0.0f; }

    VertexPC(Vector3 position, Color  color)
        : position(position), color(color)
    {
        this->position.z = 0.0f;
    }
};
   

struct VertexPT
{
    Vector3 position;
    //ÅØ½ºÃÄ ÁÂÇ¥ (0~1)
    Vector2 uv;

    VertexPT() { position.z = 0.0f; }

    VertexPT(Vector3 position, Vector2  uv)
        : position(position), uv(uv)
    {
        this->position.z = 0.0f;
    }
};