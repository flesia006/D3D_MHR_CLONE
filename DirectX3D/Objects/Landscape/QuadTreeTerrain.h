#pragma once

class QuadTreeTerrain : public GameObject
{
private:
    const float MAX_HEIGHT = 20.0f;
    const UINT MIN_TRIANGLE = 2048;

    typedef VertexUVNormal VertexType;

    struct Node
    {
        //��带 �����ϴ� ��ҵ�
        float x, z, size; //��ġ�� ũ��
        UINT triangleCount = 0; //�ȿ� �ִ� �ﰢ���� ����

        Mesh<VertexType>* mesh = nullptr; //�ش� ��忡�� ���� �ִ� (������, �ɰ���) ���

        Node* children[4] = {}; //��� �ؿ� �ڽ��� �ִٸ� �� �� �ִ���, ��������
    };

public:
    QuadTreeTerrain(wstring heightFile);
    ~QuadTreeTerrain();

    void Render();
    void GUIRender();

private:
    void RenderNode(Node* node);
    void DeleteNode(Node* node);

    // �����ġ ���ϱ�
    void CalcMeshDimensions(UINT vertexCount, float& centerX, float& centerZ, float& size);

    bool IsTriangleContained(UINT index, float x, float z, float size);
    UINT ContainTriangleCount(float x, float z, float size);

    // ��� �����, ����Ʈ���� ����
    void CreateTreeNode(Node* node, float x, float z, float size);

private:
    UINT width, height;
    UINT triangleCount = 0, drawCount = 0;

    TerrainData* terrainData;
    vector<VertexType> vertices;

    Node* root;
};