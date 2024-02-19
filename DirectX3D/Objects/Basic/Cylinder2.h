#pragma once
class Cylinder2 : public GameObject
{
private:
    typedef VertexUVNormalTangent VertexType;

public:
    Cylinder2(float radius = 1.0f, float height = 1.0f, UINT sliceCount = 32);
    ~Cylinder2();

    void Render() override;

private:
    void MakeMesh();
    void MakeNormal();
    void MakeTangent();

private:
    Mesh<VertexType>* mesh;

    float radius, height;
    UINT sliceCount;
};