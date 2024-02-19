#pragma once
class HalfSphere : public GameObject
{
private:
    typedef VertexUVNormalTangent VertexType;

public:
    HalfSphere(float radius = 1.0f, UINT sliceCount = 32, UINT stackCount = 8);
    ~HalfSphere();

    void Render() override;

private:
    void MakeMesh();
    void MakeTangent();

private:
    Mesh<VertexType>* mesh;

    float radius;
    UINT sliceCount, stackCount;
};