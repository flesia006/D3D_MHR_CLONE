#pragma once
class Ring : public GameObject
{
private:
    typedef VertexUVNormalTangent VertexType;

public:
    Ring(float radius = 1.0f, float height = 1.0f, UINT sliceCount = 32);
    ~Ring();

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

