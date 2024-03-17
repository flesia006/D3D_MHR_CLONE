#include "Framework.h"
#include "M41Objects.h"

M41Objects::M41Objects()
{
    M42A01 = new Model("ground");
    M42A01->Pos() = basicPos;
    M42A01->Rot().y = XM_PI;
//    FOR(M42A01->GetMaterials().size())
//    {
//        if (i == 0 || i == 16 || i == 17)
//            M42A01->GetMaterials()[i]->SetShader(L"Basic/Texture.hlsl");
//    }
    M42A01->UpdateWorld();

    grass = new Model("grass");
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

    sm414_005_01 = new Model("sm414_005_01");
    sm414_005_01->SetTag("sm414_005_01");
    sm414_005_01->SetMap(basicTexPath);
    sm414_005_01->Pos() = Vector3(-373.4, 209.3, 2854.1);
    sm414_005_01->UpdateWorld();

    sm414_005_01_2 = new Model("sm414_005_01");
    sm414_005_01_2->SetTag("sm414_005_01_2");
    sm414_005_01_2->Pos() = Vector3(-373.4, 209.3, 2854.1);
    sm414_005_01_2->UpdateWorld();
}

M41Objects::~M41Objects()
{
}

void M41Objects::Update()
{
    sm414_005_01->UpdateWorld();
    sm414_005_01_2->UpdateWorld();
}

void M41Objects::Render()
{
    //M42A01->SetShader(L"Light/Shadow.hlsl");

    sm415_000_01->Render();
    sm414_007_00->Render();
    sm414_005_04->Render();

    sm414_007_00_2->Render();

    sm414_005_01->Render();
    sm414_005_01_2->Render();

    M42A01->Render();

    grass->SetShader(L"Basic/Texture2.hlsl");
    grass->Render();

}

void M41Objects::GUIRender()
{
    //grass->GUIRender();
    //M42A01->GUIRender();
    sm414_005_01->GUIRender();
    sm414_005_01_2->GUIRender();
        //sm414_007_00->GUIRender();
    //sm414_005_04->GUIRender();
    //    sm415_000_01->GUIRender();
    //ImGui::DragInt("num", &num, 1, 0, M42A01->GetMaterials().size());
}

void M41Objects::SetShader(wstring path)
{
    M42A01->SetShader(path);
    sm415_000_01->SetShader(path);
}
