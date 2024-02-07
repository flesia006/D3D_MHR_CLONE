#include "Framework.h"

TerrainLOD::TerrainLOD(wstring heightFile)
{
    material->SetShader(L"TS/TerrainLOD.hlsl");
    material->SetDiffuseMap(L"Textures/Landscape/Dirt2.png");

    hullShader = Shader::AddHS(L"TS/TerrainLOD.hlsl");
    domainShader = Shader::AddDS(L"TS/TerrainLOD.hlsl");

    heightMap = Texture::Add(heightFile);

    terrainBuffer = new FloatValueBuffer();
    heightBuffer = new FloatValueBuffer();

    // �� ���ۿ� �ǹ̸� ��� ��ġ�� �Ҵ�
    terrainBuffer->Get()[0] = 1.0f;         // LOD ���� ���ذŸ�, �ּ�
    terrainBuffer->Get()[1] = 1000.0f;      // LOD ���� ���ذŸ�, �ִ�
            //-> ������ ������ "ī�޶� �ٷ� �տ������� LOD ����, �Ÿ� 1000 �̻��� �ּ� ����
            //   ���ӿ��� ���� �� ���� �������� ���� x, ������ LOD�� �̷��� ������ ���� �ִٴ� ����
    terrainBuffer->Get()[2] = 1.0f;         // LOD ���� ���� ����, �ּ�
    terrainBuffer->Get()[3] = 64.0f;        // LOD ���� ���� ����, �ִ�
            //-> ���� ������ �ǹ̴� ���� ���縦 �ּ� 1/64 ���ر��� ����߸��ڴ�
            //   �������� ���� x, LOD�� �̷��� ������ ���̶�� ����

    // �� LOD ���� ���ۿ���, �������� �����̶��... �ּ� �Ÿ��� ���� �� Ű���,
    // ���� ���� �ּ� ������ ������ ���纸�ٴ� ���� �� ���� ��

    heightBuffer->Get()[0] = 20.0f; // �Ϲ� �ͷ��� Ŭ�������� �����ߴ� �ִ� ����

    mesh = new Mesh<VertexType>();
    MakeMesh();
    mesh->CreateMesh();
}

TerrainLOD::~TerrainLOD()
{
    delete mesh;

    delete terrainBuffer;
    delete heightBuffer;
}

void TerrainLOD::Render()
{
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    // ���� ����
    terrainBuffer->SetHS(10); // 10 : ���̴� �� ���ǹ� Ȱ��ȭ + �ٸ� ���̴� ���ð� �� ��ħ
    heightBuffer->SetDS(10);

    heightMap->DSSet(); // ������ ���̴� �Ҵ�

    //���� �غ�
    material->Set();
    hullShader->Set();
    domainShader->Set();

    //���� �׸��� (���� �� ���)
    mesh->Draw(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
                // ������, Ȥ�� �޽� �ۼ� �߿� ������ patch�� ������ ������ ����
                // -> patch���� �⺻ ���� �ִ� : 6��ü ���� (������ ���� ����)

    //����Ϳ� ���̴� �����ϰ� ���
    DC->HSSetShader(nullptr, nullptr, 0);
    DC->DSSetShader(nullptr, nullptr, 0);
}

void TerrainLOD::GUIRender()
{
    ImGui::Text("TerrainLOD Option");
    ImGui::DragFloat("MinDistance", &terrainBuffer->Get()[0]);
    ImGui::DragFloat("MaxDistance", &terrainBuffer->Get()[1]);
    ImGui::DragFloat("MinQuality", &terrainBuffer->Get()[2]);
    ImGui::DragFloat("MaxQuality", &terrainBuffer->Get()[3]);
    ImGui::DragFloat("HeightScale", &heightBuffer->Get()[0]);
}

void TerrainLOD::MakeMesh()
{
    // LOD �ͷ����� ���� ���а� ���� ���(����) ���Ǳ���

    width = heightMap->GetSize().x;
    height = heightMap->GetSize().y;

    // �� �������� �ؽ�ó ������ ��� �� ���ΰ�
    cellUV = { 1.0f / width, 1.0f / height }; // <- ���� �ܼ�, ����� ���

    // ������ ���¿� �԰��� ����
    patchWidth = ((width - 1) / cellsPerPatch) + 1; // <- �� ���� �ȿ� cellsPerPatch��ŭ�� �ȼ��� �ְڴ�
    patchHeight = ((height - 1) / cellsPerPatch) + 1; // ���� = ��Ʈ(2D�簢�� Ȥ�� ���� xz���� ��� ���̸� �����ϴ� ���Ͱ���)
                                                      // cells�� �ǹ� : ���⼭�� �ؽ�ó�� �ȼ�

    // �� �ڵ忡�� ����� ����, �԰�, cells�� �̿��ؼ� LOD �޽��� ����

    //���� ������
    vector<VertexType>& vertices = mesh->GetVertices();
    vertices.resize(patchWidth * patchHeight);

    // ������ ���� �����͸� �����ؼ� ���� Ž�� ����� �������� �����

    float halfWidth = width * cellSpacing * 0.5f;   // ������ ����ȭ�� �� ���� ���� "���ݰ�"
    float halfHeight = height * cellSpacing * 0.5f; // ��Ʈ�� OBB ���� ���ݰ��� ���� ����

    float tempWidth = width * cellSpacing / patchWidth;      // �԰��� ��ü�� ����� ������ ���� ����
    float tempHeight = height * cellSpacing / patchHeight;   // 

    float du = 1.0f / patchWidth;  // ���� ���� UV (����ȭ�Ǹ� �����ϴ� �ȼ��� �ø��� ����)
    float dv = 1.0f / patchHeight; // 

    for (UINT z = 0; z < patchHeight; z++)
    {
        float tempZ = halfHeight - z * tempHeight; // ��ǥ z ����
        for (UINT x = 0; x < patchWidth; x++)
        {
            float tempX = -halfHeight + x * tempWidth; //��ǥ x ����

            UINT index = patchWidth * z + x;              //������ �ε����� ã�Ƴ���
                                                          //*���⼭ �ε����� ���� ������ ��¿� ����� ������ �ʰ�
                                                          // �ܼ��� ���� ���� ���� ������ ������ ���Ѵ�
            vertices[index].pos = { tempX, 0.0f, tempZ }; //���� ��ġ ����
            vertices[index].uv = { x * du, z * dv };      //���� uv ����

            // -> ������ ������ (�԰ݰ� ���δ����� �ö󰡸� : temp�� ��������)
            //    index�� �����ϰ� �ٲ�� ������ �������� �ϳ��ϳ� ��� ���ư��鼭 �ٲ��
            // -> �ָ� ������ (�԰ݰ� ���δ����� ��������, temp�� ��������)
            //    intdex�� �� �ܰ辿 �ǳʶٸ鼭 �ݺ����� ���� -> ���� �Ϻΰ� ���꿡�� ���� ����
            //    = �� ������ ���ؼ� ����� ���� �Ĳ��ϰ� �������ְ�, �� ���� ������ ���
            //    = �� ������ ���ؼ� ���� ������ �Ϻθ� �����ϰ�, ������ ���ױ׸��� ��� ����ȭ ����

            // -> �� ���� ���� ���� (+����̴� + �����μ��̴�) : LOD ������ �ٽ�
        }
    }

    //���� �ε���
    vector<UINT>& indices = mesh->GetIndices();
    indices.reserve((patchWidth - 1) * (patchHeight - 1) * 4);

    for (UINT z = 0; z < patchHeight - 1; z++)
    {
        for (UINT x = 0; x < patchWidth - 1; x++)
        {
            // ������ �ε��� ������ ���� �ﰢ�� x2 ��� ��Ʈ x1 ��������

            indices.push_back(patchWidth * z + x);
            indices.push_back(patchWidth * z + x + 1);
            indices.push_back(patchWidth * (z + 1) + x);
            indices.push_back(patchWidth * (z + 1) + x + 1);
        }
    }
}

