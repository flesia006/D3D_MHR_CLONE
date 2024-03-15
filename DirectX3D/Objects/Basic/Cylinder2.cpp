#include "Framework.h"
#include "Cylinder2.h"

Cylinder2::Cylinder2(float radius, float height, UINT sliceCount)
    : radius(radius), height(height), sliceCount(sliceCount)
{
    tag = "Cylinder2";

    mesh = new Mesh<VertexType>();
    MakeMesh();
    mesh->CreateMesh();
}

Cylinder2::~Cylinder2()
{
    delete mesh;
}

void Cylinder2::Render()
{
    SetRender();

    mesh->Draw();
}

void Cylinder2::MakeMesh()
{
    float thetaStep = XM_2PI / sliceCount;

    vector<VertexType>& vertices = mesh->GetVertices();
    vertices.reserve((sliceCount + 1) * 4);

    //Side
    for (int i = 0; i <= sliceCount; i++)
    {
        float theta = thetaStep * i;

        float x = cos(theta);
        float z = sin(theta);

        VertexType vertex;
        vertex.pos = { x * radius, -height * 0.5f, z * radius };
        vertex.uv = { (float)i / (float)sliceCount, 1.0f };
        vertices.push_back(vertex);

        vertex.pos = { x * radius, +height * 0.5f, z * radius };
        vertex.uv = { (float)i / (float)sliceCount, 0.0f };
        vertices.push_back(vertex);
    }

    //Á¤Á¡ ÀÎµ¦½º
    vector<UINT>& indices = mesh->GetIndices();

    indices.reserve(sliceCount * 6);

    UINT sideIndex = 0;

    for (UINT i = 0; i < sliceCount; i++)
    {
        indices.push_back(sideIndex + i * 2 + 0);//0
        indices.push_back(sideIndex + i * 2 + 1);//1
        indices.push_back(sideIndex + i * 2 + 2);//2        

        indices.push_back(sideIndex + i * 2 + 2);//2
        indices.push_back(sideIndex + i * 2 + 1);//1
        indices.push_back(sideIndex + i * 2 + 3);//3
    }
}

void Cylinder2::MakeNormal()
{
}

void Cylinder2::MakeTangent()
{
}
