#include "Framework.h"
#include "M41Objects.h"

M41Objects::M41Objects()
{
    M42A01 = new Model("ground");
    M42A01->GetMaterials()[18]->SetShader(L"Basic/Texture2.hlsl");
    M42A01->Pos() = basicPos;
    M42A01->Rot().y = XM_PI;
    M42A01->UpdateWorld();

    sm415_000_01 = new Model("sm415_000_01");
    sm415_000_01->SetTag("sm415_000_01");
    sm415_000_01->Pos() = Vector3(75000, 3000, 3500);
    sm415_000_01->Rot().y = XM_PI;
    sm415_000_01->UpdateWorld();

    sm414_005_04 = new ModelInstancing("sm414_005_04");  // 법규 벽
    {
        {
            Transform* transform = sm414_005_04->Add();
            transform->Pos() = Vector3(3809, 231.7, 395.1);
            transform->Rot() = Vector3(0.034, XM_PI, 0);
        }
        {
            Transform* transform = sm414_005_04->Add();
            transform->Pos() = Vector3(6940.5, 174.3, 3285.5);
            transform->Rot() = Vector3(57.9 * unitRad, -106 * unitRad, 0);
        }
        {
            Transform* transform = sm414_005_04->Add();
            transform->Pos() = Vector3(1735.7, -303.3, 308.3);
            transform->Rot() = Vector3(0, -12 * unitRad, 0);
        }
        sm414_005_04->Update();
    }

    sm414_007_00 = new ModelInstancing("sm414_007_00");    // 사각 기둥
    {
        {
            Transform* transform = sm414_007_00->Add();
            transform->Pos() = { 5755, 153.3, 1526.3 };
            transform->Rot() = { 0, XM_PIDIV2, -0.12 };
        }
        {
            Transform* transform = sm414_007_00->Add();
            transform->Pos() = { -373.4, 209.3, 2854.1 };
        }
        {
            Transform* transform = sm414_007_00->Add();
            transform->Pos() = { 7224.8, 195.8, 6966 };
            transform->Rot() = { 15 * unitRad, 44 * unitRad, 0 };
        }
        sm414_007_00->Update();
    }

    sm414_005_01 = new Model("sm414_005_01");
    sm414_005_01->SetTag("sm414_005_01");
    sm414_005_01->Pos() = Vector3(5706, 303.2, 2960.1);
    sm414_005_01->Rot().y = 103 * unitRad;
    sm414_005_01->Scale() *= 0.8f;
    sm414_005_01->GetMaterials()[4]->SetShader(L"Basic/Texture2.hlsl");
    sm414_005_01->GetMaterials()[5]->SetShader(L"Basic/Texture2.hlsl");
    sm414_005_01->UpdateWorld();

    sm414_005_01_2 = new Model("sm414_005_01");
    sm414_005_01_2->SetTag("sm414_005_01_2");
    sm414_005_01_2->Pos() = Vector3(6579.5, 260.1, 4586.6);
    sm414_005_01_2->Scale() *= 0.7f;
    sm414_005_01_2->Rot().y = 121 * unitRad;
    sm414_005_01_2->GetMaterials()[4]->SetShader(L"Basic/Texture2.hlsl");
    sm414_005_01_2->GetMaterials()[5]->SetShader(L"Basic/Texture2.hlsl");
    sm414_005_01_2->UpdateWorld();

    sm414_005_02 = new ModelInstancing("sm414_005_02");
    {
        {// 0
            Transform* transform = sm414_005_02->Add();
            transform->Pos() = Vector3(6685.5, 150.1, 6536.2);
            transform->Rot() = { 21 * unitRad, 77 * unitRad, 0 };
        }
        {// 1
            Transform* transform = sm414_005_02->Add();
            transform->Pos() = { 169.6, 159.2, 1195.1 };
            transform->Rot() = { 0, 88 * unitRad, 0 };
            transform->Scale().y *= 1.2;
        }
        {// 2
            Transform* transform = sm414_005_02->Add();
            transform->Pos() = { 5979, 661, 8499 };
            transform->Rot() = { 1 * unitRad, 40 * unitRad, 0 };
            transform->Scale() = { 1.2, 1, 1 };
        }
        {// 3
            Transform* transform = sm414_005_02->Add();
            transform->Pos() = { 5652.3, 493.3, 8275 };
            transform->Rot() = { -53 * unitRad, 37 * unitRad, 0 };
            transform->Scale() = { 1.2, 1, 1 };
        }
        {// 4
            Transform* transform = sm414_005_02->Add();
            transform->Pos() = { 5079.5, 82, 7436.5 };
            transform->Rot() = { 17 * unitRad, 3 * unitRad, 0 };
        }
        {//5
            Transform* transform = sm414_005_02->Add();
            transform->Pos() = { 111.3, 195.8, 6788.7 };
            transform->Rot() = {0, 77 * unitRad, 0 };
        }
        {//6
            Transform* transform = sm414_005_02->Add();
            transform->Pos() = { 2559.4, 114.6, 307 };
            transform->Rot() = { 0, -1 * unitRad, 0 };
        }
        {//7
            Transform* transform = sm414_005_02->Add();
            transform->Pos() = { 8055, 214.8, 2350 };
            transform->Rot() = { 0 * unitRad, 99 * unitRad, 0 };
            transform->Scale() = { 0.8, 1, 1 };
        }
        {//8
            Transform* transform = sm414_005_02->Add();
            transform->Pos() = { 5473.5, 371.6, -512.2 };
            transform->Rot() = { 0 * unitRad, -32 * unitRad, 0 };
        }
        {//9
            Transform* transform = sm414_005_02->Add();
            transform->Pos() = { 1225.2, 243.1, 7917.5 };
            transform->Rot() = { 12 * unitRad, 173* unitRad, 0 };
        }
        {//10
            Transform* transform = sm414_005_02->Add();
            transform->Pos() = { 3294.7, 278.2, 7766.7 };
            transform->Rot() = { -64 * unitRad, 0 * unitRad, 0 };
        }
        sm414_005_02->Update();
    }

    sm414_009_00 = new ModelInstancing("sm414_009_00");
    {     
        FOR(6)
        {
            Transform* transform = sm414_009_00->Add();
            transform->Pos() = Vector3(3000 + 9000 * i, 150.1, -3000);
            transform->Rot() = { 0 * unitRad, 180 * unitRad, 0 };
        }

        FOR(5)
        {
            Transform* transform = sm414_009_00->Add();
            transform->Pos() = Vector3(3000 + 9000 * (i+1), 150.1, -15000);
            transform->Rot() = { 0 * unitRad, 180 * unitRad, 0 };
        }

        FOR(5)
        {
            Transform* transform = sm414_009_00->Add();
            transform->Pos() = Vector3(3000 + 9000 * (i+1), 150.1, 9000);
            transform->Rot() = { 0 * unitRad, 180 * unitRad, 0 };
        }

        FOR(6)
        {
            Transform* transform = sm414_009_00->Add();
            transform->Pos() = Vector3(3000 + 9000 * i, 150.1, 21000);
            transform->Rot() = { 0 * unitRad, 180 * unitRad, 0 };
        }

        FOR(4)
        {
            Transform* transform = sm414_009_00->Add();
            transform->Pos() = Vector3(3000 + 9000 * (i+2), 150.1, 33000);
            transform->Rot() = { 0 * unitRad, 180 * unitRad, 0 };
        }
        sm414_009_00->Update();
    }

    FOR(2) rasterizerState[i] = new RasterizerState();
    rasterizerState[1]->CullMode(D3D11_CULL_NONE);

}

M41Objects::~M41Objects()
{
}

void M41Objects::Update()
{
}

void M41Objects::Render()
{
    rasterizerState[1]->SetState();
    sm415_000_01->Render();
    sm414_007_00->Render();
    sm414_005_04->Render();
    sm414_005_01->Render();
    sm414_005_01_2->Render();
    sm414_005_02->Render();
    sm414_009_00->Render();
    M42A01->Render();
    rasterizerState[0]->SetState();
//    grass->Render();

}

void M41Objects::GUIRender()
{
    //sm414_005_02->GUIRender();
    //sm414_009_00->GUIRender();
    //sm414_005_04->GUIRender();
    //grass->GUIRender();
    //M42A01->GUIRender();
    //sm414_005_01->GUIRender();
    //sm414_005_01_2->GUIRender();
    //sm414_005_05->GUIRender();
    //sm414_007_00->GUIRender();
    //sm414_007_00_3->GUIRender();
    //sm414_005_02->GUIRender();
    //    sm415_000_01->GUIRender();
    //ImGui::DragInt("num", &num, 1, 0, M42A01->GetMaterials().size());
}

void M41Objects::SetShader(wstring path)
{
    M42A01->SetShader(path);
    sm415_000_01->SetShader(path);
}
