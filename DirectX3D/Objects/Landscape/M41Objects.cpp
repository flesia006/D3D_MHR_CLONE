#include "Framework.h"
#include "M41Objects.h"

M41Objects::M41Objects()
{
    M42A01 = new Model("ground");
    M42A01->Pos() = basicPos;
    M42A01->Rot().y = XM_PI;
    M42A01->UpdateWorld();

    grass = new Model("grass");
    grass->SetShader(L"Basic/Texture2.hlsl");
    grass->Pos() = basicPos;
    grass->Rot().y = XM_PI;
    grass->UpdateWorld();

    sm415_000_01 = new Model("sm415_000_01");
    sm415_000_01->SetTag("sm415_000_01");
    sm415_000_01->Pos() = Vector3(75000, 3000, 3500);
    sm415_000_01->Rot().y = XM_PI;
    sm415_000_01->UpdateWorld();

    sm414_007_00 = new Model("sm414_007_00");
    sm414_007_00->SetTag("sm414_007_00");
    sm414_007_00->Pos() = Vector3(5755, 153.3, 1526.3);
    sm414_007_00->Rot() = Vector3(0, XM_PIDIV2, -0.12);
    sm414_007_00->UpdateWorld();

    sm414_005_04 = new Model("sm414_005_04");
    sm414_005_04->SetTag("sm414_005_04");
    sm414_005_04->Pos() = Vector3(3809, 231.7, 395.1);
    sm414_005_04->Rot() = Vector3(0.034, XM_PI, 0);
    sm414_005_04->UpdateWorld();

    sm414_007_00_2 = new Model("sm414_007_00");
    sm414_007_00_2->SetTag("sm414_007_00_2");
    sm414_007_00_2->Pos() = Vector3(-373.4, 209.3, 2854.1);
    sm414_007_00_2->UpdateWorld();

    sm414_007_00_3 = new Model("sm414_007_00");
    sm414_007_00_3->SetTag("sm414_007_00_3");
    sm414_007_00_3->Pos() = Vector3(7224.8, 195.8, 6966);
    sm414_007_00_3->Rot() = { 15 * unitRad, 44 * unitRad, 0 };
    sm414_007_00_3->UpdateWorld();

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

    sm414_005_02 = new Model("sm414_005_02");
    sm414_005_02->SetTag("sm414_005_02");
    sm414_005_02->Pos() = Vector3(6685.5, 150.1, 6536.2);
    sm414_005_02->Rot() = { 21 * unitRad, 77 * unitRad, 0 };
    sm414_005_02->SetMap(basicTexPath);
    sm414_005_02->UpdateWorld();
}

M41Objects::~M41Objects()
{
}

void M41Objects::Update()
{
    sm414_005_02->UpdateWorld();
}

void M41Objects::Render()
{

    sm415_000_01->Render();
    sm414_007_00->Render();
    sm414_005_04->Render();

    sm414_007_00_2->Render();
    sm414_007_00_3->Render();
    sm414_005_01->Render();
    sm414_005_01_2->Render();
    sm414_005_02->Render();

    M42A01->Render();

    grass->Render();

}

void M41Objects::GUIRender()
{
    //grass->GUIRender();
    //M42A01->GUIRender();
    //sm414_005_01->GUIRender();
    //sm414_005_01_2->GUIRender();
    //sm414_005_05->GUIRender();
    //sm414_007_00->GUIRender();
    //sm414_007_00_3->GUIRender();
    sm414_005_02->GUIRender();
    //    sm415_000_01->GUIRender();
    //ImGui::DragInt("num", &num, 1, 0, M42A01->GetMaterials().size());
}

void M41Objects::SetShader(wstring path)
{
    M42A01->SetShader(path);
    sm415_000_01->SetShader(path);
}
