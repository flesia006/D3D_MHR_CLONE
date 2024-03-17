#include "Framework.h"

Quad::Quad(Vector2 size)
    : GameObject(L"Basic/Texture.hlsl"), size(size)
{
    mesh = new Mesh<VertexType>();
    MakeMesh();
    mesh->CreateMesh();
}

Quad::Quad(wstring file)
    : GameObject(L"Basic/Texture.hlsl")
{
    Texture* texture = Texture::Add(file);
    material->SetDiffuseMap(file);
    size = texture->GetSize();

    mesh = new Mesh<VertexType>();
    MakeMesh();
    mesh->CreateMesh();
    
}

Quad::~Quad()
{    
    delete mesh;
}

void Quad::Render()
{
    if (!Active()) return;

    SetRender();
    mesh->Draw();
}

void Quad::SetRender()
{
    mesh->GetVertexBuffer()->Set();
    mesh->GetIndexBuffer()->Set();

    GameObject::SetRender();
}

void Quad::SetTexture(wstring file)
{
    Texture* texture = Texture::Add(file);
    material->SetDiffuseMap(file);
    size = texture->GetSize();

    mesh = new Mesh<VertexType>();
    MakeMesh();
    mesh->CreateMesh();
}

void Quad::InItPos(Vector3 Pos)
{
    LT = { LT.x + Pos.x , LT.y + Pos.y };
    RB = { RB.x + Pos.x , RB.y + Pos.y };
}

bool Quad::IsOnMouseCursor()
{
    Vector3 pos = mousePos;

    if (LT.x < pos.x && LT.y > pos.y &&
        RB.x > pos.x && RB.y < pos.y)
        return true;

    return false;
}

void Quad::MakeMesh()
{
    float left = -size.x * 0.5f;
    float right = +size.x * 0.5f;
    float top = +size.y * 0.5f;
    float bottom = -size.y * 0.5f;

    vector<VertexType>& vertices = mesh->GetVertices();

    vertices.emplace_back(left, top, 0, 0, 0);
    vertices.emplace_back(right, top, 0, 1, 0);
    vertices.emplace_back(left, bottom, 0, 0, 1);
    vertices.emplace_back(right, bottom, 0, 1, 1);

    vector<UINT>& indices = mesh->GetIndices();
    indices = { 0, 1, 2, 2, 1, 3 };

    LT = { left, top };
    RB = { right, bottom };
}