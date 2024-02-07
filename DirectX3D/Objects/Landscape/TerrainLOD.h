#pragma once

class TerrainLOD : public GameObject
{
    // LOD : ������ ���� ���� ���� (level of detail)
    // LOD Ŭ���� : LOD�� ������ �����ؼ� ������ �� ����� �δ��� ���߱� ���� Ŭ����

private:
    typedef VertexUV VertexType; // ���� Ÿ��(������ ���ؼ� ��� ������)
    //typedef VertexUVNormalTangent VertexType; //Ÿ���� �̷��� �ٲپ� �� ���� �ִ�

public:
    TerrainLOD(wstring heightFile);
    ~TerrainLOD();

    void Render();
    void GUIRender();

private:
    void MakeMesh();

private:
    // �Ҽ� ����
    FloatValueBuffer* terrainBuffer; // �뵵�� ���� ���۸� ����
    FloatValueBuffer* heightBuffer;  // �ڷ� ������ ������ ���� : 1. �ϰ�ó�� ����
                                     //                         2. �޸տ��� ����

    Mesh<VertexType>* mesh;

    HullShader* hullShader;          // �� ���̴�, �߰� ���� ���̴�
                                     // DX10���� ���������� ���̰� �� �ű��
                                     // ���� ���̴� ��� �� -> ���� ���� ���̿� �����Ͽ�
                                     // ���� �Ϻθ� ���ǿ� ���� �߰� ���̴��� ���� �� �ֵ���
                                     // ������ ���� ó����ġ�� �����ϴ� ���̴� (�ٸ� ��ɵ� ������ ������ ���� �߿�)

    DomainShader* domainShader;      // ������ ���̴�, ���� ���̴�
                                     // -> ������ �ȼ��� �׷��� ó����ġ���� ���հ���ϴ� ���̴�
                                     //    ������Ʈ�� ���̴��� ���� ����� (GPU���� �ϴ� GS��� �����ص� ����)
                                     // -> DS�� Ư¡ : �� ���̴��κ��� �߰������ �޾Ƽ� ó���� ���ش�
                                     //    = ���ǿ� ���� �ٸ� ���� ó�� ����

    Texture* heightMap;

    // ��/������ ���̴� ���꿡 �ʿ��� ���� ���� ����
    UINT cellsPerPatch = 32;    // Ȯ���Ϸ��� ���� ���� ���� �� ���� ���� ����
    float cellSpacing = 5;      // �������� �е�
    Vector2 cellUV;             // �� ������ ����� �� �ؽ�ó���� ������ UV

    UINT width, height;
    UINT patchWidth, patchHeight;
};