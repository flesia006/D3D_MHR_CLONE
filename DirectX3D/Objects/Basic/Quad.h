#pragma once

class Quad : public GameObject
{
private:
    typedef VertexUV VertexType;

public:
    Quad(Vector2 size);    
    Quad(wstring file);
    ~Quad();

    void Render();
    void SetRender();

    void SetTexture(wstring file);

    void InItPos(Vector3 Pos);
    bool IsOnMouseCursor();

private:
    void MakeMesh();

private:
    Vector2 LT, RB;
    Vector2 size;
    Mesh<VertexType>* mesh;    
};